/*************************************************************************\
*  UtopiaDB - A multimedia database application and library with a clean  *
*  API and lots of features, including multiple languages per entry.      *
*                                                                         *
*  Copyright (C) 2006-2007 John Eric Martin <john.eric.martin@gmail.com>  *
*                                                                         *
*  This program is free software; you can redistribute it and/or modify   *
*  it under the terms of the GNU General Public License version 2 as      *
*  published by the Free Software Foundation.                             *
*                                                                         *
*  This program is distributed in the hope that it will be useful,        *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with this program; if not, write to the                          *
*  Free Software Foundation, Inc.,                                        *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
\*************************************************************************/

#include "sqlmetabase.h"
#include "blockparser.h"
#include "qgzipfile.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QProcess>

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

#include <iostream>

using namespace Utopia;

SqlMetaBase::SqlMetaBase(const QSqlDatabase& db, const QString& prefix, bool revControl, QObject *parent) : MetaBase(parent)
{
	mValid = false;
	mRevisionControl = revControl;
	mPrefix = prefix;
	mDatabase = db;
	mNextAvailableID = 1;

	if( !mDatabase.isValid() || !mDatabase.isOpen() )
		return;

	if( mDatabase.driverName() != "QMYSQL" && mDatabase.driverName() != "QSQLITE" )
		return;

	if( !mDatabase.tables(QSql::Tables).contains(mPrefix + "settings") )
		createDatabase();
};

void SqlMetaBase::createDatabase()
{
	QSqlQuery query(mDatabase);

	// Drop existing settings table
	if( mDatabase.tables(QSql::Tables).contains(mPrefix + "settings") )
	{
		query.prepare("DROP TABLE " + mPrefix + "settings");
		query.bindValue(":table", mPrefix + "settings");
		if( !query.exec() )
		{
			std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
			return;
		}
	}

	// Create the settings table
	query.prepare("CREATE TABLE " + mPrefix + "settings ( `id` INT UNSIGNED NOT NULL, `key` VARCHAR(32), `value` VARCHAR(256), PRIMARY KEY(`id`) )");
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return;
	}

	// Insert some values into the settings table
	query.prepare("INSERT INTO " + mPrefix + "settings (`id`, `key`, `value`) VALUES (:id, :key, :value)");
	query.bindValue(":id", 0);
	query.bindValue(":key", "version");
	query.bindValue(":value", "0.1.0");
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return;
	}

	query.prepare("INSERT INTO " + mPrefix + "settings (`id`, `key`, `value`) VALUES (:id, :key, :value)");
	query.bindValue(":id", 1);
	query.bindValue(":key", "revision_control");
	query.bindValue(":value", "on");
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return;
	}

	// Create the blocks table
	query.prepare("CREATE TABLE " + mPrefix + "blocks ( `id` INT UNSIGNED NOT NULL, `uid` INT UNSIGNED NOT NULL, `type` VARCHAR(24), "
					"`data` BLOB, `checksum` VARCHAR(20), `date` TIMESTAMP, `rev` INT UNSIGNED, PRIMARY KEY(`id`) )");
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return;
	}

	if(mRevisionControl)
	{
		// Create the revisions table
		query.prepare("CREATE TABLE " + mPrefix + "revisions ( `id` INT UNSIGNED NOT NULL, `uid` INT UNSIGNED NOT NULL, `rev` INT UNSIGNED, `date` TIMESTAMP, "
						"`user` VARCHAR(32), `log` VARCHAR(2048), `data` BLOB, `checksum` VARCHAR(20), PRIMARY KEY(`id`) )");
		if( !query.exec() )
		{
			std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
			return;
		}
	}

	mValid = true;

	UtopiaBlock block1;
	block1.setID(1);
	block1.setName("lol");
	block1.setNativeLang("ja");
	addBlock(block1);
	block1.setName("Test_Block");
	updateBlock(block1);
	block1.setComments("The is a test block for viewing in Utopia Block Browser.");
	updateBlock(block1);
};

QList<UtopiaBlock> SqlMetaBase::blocks(const QString& blockType) const
{
	QList<UtopiaBlock> list;

	QString limit;
	if(!blockType.isEmpty())
		limit = "WHERE `type` = '" + blockType + "' ";

	QSqlQuery query(mDatabase);
	query.prepare("SELECT `data` FROM " + mPrefix + "blocks " + limit + "ORDER BY `uid`");
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return list;
	}

	UtopiaBlock block;
	QString blockXML;
	while(query.next())
	{
		blockXML = QString::fromUtf8( qUncompress(query.record().value("data").toByteArray()) );
		list << BlockParser::blocksFromXML(blockXML);
     }

	return list;
};

QList<Album> SqlMetaBase::albums() const
{
};

QString SqlMetaBase::indexTableName(const QString& blockType, const QString& field) const
{
	return mPrefix + blockType.toLower() + field.toLower();
};

QString SqlMetaBase::indexTableIndexName(const QString& blockType, const QString& field) const
{
	return mPrefix + "idx_" + blockType.toLower() + field.toLower();
};

bool SqlMetaBase::updateIndexTable(const QString& blockType, const QStringList& fields)
{
	/*QString currentFields;
	QSqlRecord record = mDatabase.record(mPrefix + table);
	for(int i = 0; i < record.count(); i++)
		currentFields << record.fieldName(i);*/

	QString tableName;
	QSqlQuery query(mDatabase);

	foreach(QString field, fields)
	{
		tableName = indexTableName(blockType, field);

		if( !mDatabase.tables(QSql::Tables).contains(tableName) )
		{
			query.prepare("CREATE TABLE " + tableName + " ( `id` INT UNSIGNED NOT NULL, `uid` INT UNSIGNED NOT NULL, "
			"`index` BLOB, PRIMARY KEY(`id`) )");
			if( !query.exec() )
			{
				std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
				return false;
			}

			query.prepare("CREATE INDEX " + indexTableIndexName(blockType, field) + " ON " + tableName + "(`index`)");
			if( !query.exec() )
			{
				std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
				return false;
			}
		}
	}

	return true;
};

bool SqlMetaBase::containsAlbumTitle(const QString& title) const
{
};

Album SqlMetaBase::albumFromTitle(const QString& title) const
{
};

QList<Individual> SqlMetaBase::individuals() const
{
};

bool SqlMetaBase::containsIndividualName(const QString& name) const
{
};

Individual SqlMetaBase::individualFromName(const QString& name) const
{
};

QList<Artist> SqlMetaBase::artists() const
{
};

bool SqlMetaBase::containsArtistName(const QString& name) const
{
};

Artist SqlMetaBase::artistFromName(const QString& name) const
{
};

QList<Composer> SqlMetaBase::composers() const
{
};

bool SqlMetaBase::containsComposerName(const QString& name) const
{
};

Composer SqlMetaBase::composerFromName(const QString& name) const
{
};

QList<Publisher> SqlMetaBase::publishers() const
{
};

bool SqlMetaBase::containsPublisherName(const QString& name) const
{
};

Publisher SqlMetaBase::publisherFromName(const QString& name) const
{
};

void SqlMetaBase::addBlock(const UtopiaBlock& block)
{
	updateBlock(block);
};
#include "sha1.h"
QString g_checksum(const QByteArray& data)
{
	uchar digest[20];
	sha1_csum((uchar*)data.data(), data.size(), digest);
	return QByteArray((char*)digest, 20).toBase64();
};

QList<UtopiaBlock> SqlMetaBase::blocks() const
{
	return blocks( QString() );
};

void SqlMetaBase::updateBlock(const UtopiaBlock& block)
{
	QSqlQuery query(mDatabase);
	query.prepare("SELECT `id` FROM " + mPrefix + "blocks WHERE `uid` = :uid ORDER BY `id`");
	query.bindValue(":uid", block.id());
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return;
	}

	QList<uid> ids;
	while(query.next())
		ids << query.record().value("id").toInt();

	int id = -1;
	if(ids.count() > 0)
	{
		if(ids.count() > 1)
			std::cout << "WARNING: Found multiple blocks with the same uid, only the first will be updated!" << std::endl;

		id = ids.first();
	}

	QByteArray data = qCompress(block.xml().toUtf8());
	QString checksum = g_checksum(data);
	QDateTime timestamp = QDateTime::currentDateTime();

	if(id < 0) // Insert
	{
		query.prepare("INSERT INTO " + mPrefix + "blocks (`id`, `uid`, `type`, `data`, `checksum`, `date`, `rev`) VALUES"
			"(:id, :uid, :type, :data, :checksum, :date, :rev)");
		query.bindValue(":id", nextTableID(mPrefix + "blocks"));
		query.bindValue(":uid", block.id());
		query.bindValue(":type", block.type().first());
		query.bindValue(":data", data);
		query.bindValue(":checksum", checksum);
		query.bindValue(":date", timestamp);
		query.bindValue(":rev", 0);
		if( !query.exec() )
		{
			std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
			return;
		}

		if(mRevisionControl)
		{
			query.prepare("INSERT INTO " + mPrefix + "revisions (`id`, `uid`, `rev`, `date`, `user`, `log`, `data`, `checksum`) VALUES"
				"(:id, :uid, :rev, :date, :user, :log, :data, :checksum)");
			query.bindValue(":id", nextTableID(mPrefix + "revisions"));
			query.bindValue(":uid", block.id());
			query.bindValue(":rev", 0);
			query.bindValue(":date", timestamp);
			query.bindValue(":user", "UtopiaDB");
			query.bindValue(":log", "Initial Import.");
			query.bindValue(":data", data);
			query.bindValue(":checksum", checksum);
			
			if( !query.exec() )
			{
				std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
				return;
			}
		}
	}
	else // Update
	{
		QByteArray oldData;
		QString oldChecksum;
		int oldRev;

		query.prepare("SELECT `data`, `checksum`, `rev` FROM " + mPrefix + "blocks WHERE `id` = :id");
		query.bindValue(":id", id);
		if( !query.exec() )
		{
			std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
			return;
		}

		if( !query.next() )
			return;

		oldData = query.record().value("data").toByteArray();
		oldChecksum = query.record().value("checksum").toString();
		oldRev = query.record().value("rev").toInt();

		// Check out data with the checksum
		if(oldChecksum != g_checksum(oldData))
		{
			std::cout << "Checksum failed on block " << block.id() << " @ rev " << oldRev << std::endl;
			return;
		}

		query.prepare("UPDATE " + mPrefix + "blocks SET `uid` = :uid, `type` = :type, `data` = :data, "
			"`checksum` = :checksum, `date` = :date, `rev` = :rev WHERE `id` = :id");
		query.bindValue(":id", id);
		query.bindValue(":uid", block.id());
		query.bindValue(":type", block.type().first());
		query.bindValue(":data", data);
		query.bindValue(":checksum", checksum);
		query.bindValue(":date", timestamp);
		query.bindValue(":rev", oldRev + 1);
		if( !query.exec() )
		{
			std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
			return;
		}

		if(mRevisionControl)
		{
			QString diff = createDiff( QString::fromUtf8( qUncompress(oldData) ), QString::fromUtf8( qUncompress(data) ) );
			if(diff.isEmpty())
			{
				std::cout << "Error creating diff for block " << block.id() << " @ rev " << oldRev << " - " << oldRev + 1 << std::endl;
				return;
			}

			data = qCompress(diff.toUtf8());
			checksum = g_checksum(data);

			query.prepare("INSERT INTO " + mPrefix + "revisions (`id`, `uid`, `rev`, `date`, `user`, `log`, `data`, `checksum`) VALUES"
				"(:id, :uid, :rev, :date, :user, :log, :data, :checksum)");
			query.bindValue(":id", nextTableID(mPrefix + "revisions"));
			query.bindValue(":uid", block.id());
			query.bindValue(":rev", oldRev + 1);
			query.bindValue(":date", timestamp);
			query.bindValue(":user", "UtopiaDB");
			query.bindValue(":log", tr("Automatic update to revision %1.").arg(oldRev + 1));
			query.bindValue(":data", data);
			query.bindValue(":checksum", checksum);
			
			if( !query.exec() )
			{
				std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
				return;
			}
		}
	}
};

int SqlMetaBase::nextTableID(const QString& table)
{
	QSqlQuery query(mDatabase);
	query.prepare("SELECT COUNT(*) FROM " + table);
	if( !query.exec() )
		return -1;

	if(!query.next())
		return -2;

	return query.value(0).toInt();
};

QString SqlMetaBase::patchedBlockData(uid id, int rev) const
{
	QSqlQuery query(mDatabase);
	query.prepare("SELECT `rev` FROM " + mPrefix + "blocks WHERE `uid` = :uid ORDER BY `uid`");
	query.bindValue(":uid", id);
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return QString();
	}

	if(!query.next())
		return QString();

	if(query.record().value("rev").toInt() < rev)
		return QString();

	QString next;
	QString previous = fetchRevisionData(id, 0);
	if( previous.isEmpty() )
		return QString();

	for(int i = 1; i <= rev; i++)
	{
		next = fetchRevisionData(id, i);
		if( next.isEmpty() )
			return QString();

		previous = patchText(previous, next);
		if( previous.isEmpty() )
			return QString();
	}

	return previous;
};

QString SqlMetaBase::fetchRevisionData(uid id, int rev) const
{
	QSqlQuery query(mDatabase);
	query.prepare("SELECT `data` FROM " + mPrefix + "revisions WHERE `uid` = :uid AND `rev` = :rev ORDER BY `uid`");
	query.bindValue(":uid", id);
	query.bindValue(":rev", rev);
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return QString();
	}

	if( !query.next() )
		return QString();

	/// @TODO - Add check for the checksum here

	return QString::fromUtf8( qUncompress(query.record().value("data").toByteArray()) );
};

QString SqlMetaBase::patchText(const QString& text, const QString& patch) const
{
	QString in1, in2;
	in1 = QDir::toNativeSeparators( QDir::temp().filePath("utopiadb_old") );
	in2 = QDir::toNativeSeparators( QDir::temp().filePath("utopiadb_patch") );

	QFile(in1).remove();
	QFile(in2).remove();

	QFile file1(in1), file2(in2);
	if( !file1.open(QIODevice::WriteOnly) )
		return QString();
	if( !file2.open(QIODevice::WriteOnly) )
		return QString();

	file1.write(text.toUtf8());
	file1.close();
	file2.write(patch.toUtf8());
	file2.close();

	QProcess proc;
	proc.setWorkingDirectory( QDir::tempPath() );
	proc.start("/usr/bin/patch", QStringList() << "-u" << "-i" << "utopiadb_old" << "utopiadb_patch");
	if(!proc.waitForStarted())
	{
		// "Failed to start proccess";
		return QString();
	}

	if(!proc.waitForFinished())
	{
		// "Failed to finish proccess";
		return QString();
	}

	QFile final(in1);
	if( !final.open(QIODevice::ReadOnly) )
		return QString();

	return QString::fromUtf8( final.readAll() );
};

QString SqlMetaBase::createDiff(const QString& oldText, const QString& newText) const
{
	if(oldText.isEmpty() || newText.isEmpty())
	{
		std::cout << "ERROR: One of the files involved in the diff is empty!" << std::endl;
		return QString();
	}

	if(oldText == newText)
	{
		std::cout << "ERROR: The two files to diff are the same!" << std::endl;
		return QString();
	}

	QString in1, in2;
	in1 = QDir::toNativeSeparators( QDir::temp().filePath("utopiadb_old") );
	in2 = QDir::toNativeSeparators( QDir::temp().filePath("utopiadb_new") );

	QFile(in1).remove();
	QFile(in2).remove();

	QFile file1(in1), file2(in2);
	if( !file1.open(QIODevice::WriteOnly) )
		return QString();
	if( !file2.open(QIODevice::WriteOnly) )
		return QString();

	file1.write(oldText.toUtf8());
	file1.close();
	file2.write(newText.toUtf8());
	file2.close();

	QProcess proc;
	proc.setWorkingDirectory( QDir::tempPath() );
	proc.start("/usr/bin/diff", QStringList() << "-u" << "utopiadb_old" << "utopiadb_new");
	if(!proc.waitForStarted())
	{
		// "Failed to start proccess";
		return QString();
	}

	if(!proc.waitForFinished())
	{
		// "Failed to finish proccess";
		return QString();
	}

	return QString::fromUtf8( proc.readAll() );
};

uid SqlMetaBase::nextAvailableID()
{
};

bool SqlMetaBase::hasID(uid id)
{
};

QString SqlMetaBase::getSetting(const QString& key) const
{
};

void SqlMetaBase::setSetting(const QString& key, const QString& value)
{
};
