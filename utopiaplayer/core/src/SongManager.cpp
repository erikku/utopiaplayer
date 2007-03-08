/******************************************************************************\
*  Utopia Player - A cross-platform, multilingual, tagging media manager       *
*  Copyright (C) 2006-2007 John Eric Martin <john.eric.martin@gmail.com>       *
*                                                                              *
*  This program is free software; you can redistribute it and/or modify        *
*  it under the terms of the GNU General Public License version 2 as           *
*  published by the Free Software Foundation.                                  *
*                                                                              *
*  This program is distributed in the hope that it will be useful,             *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
*  GNU General Public License for more details.                                *
*                                                                              *
*  You should have received a copy of the GNU General Public License           *
*  along with this program; if not, write to the                               *
*  Free Software Foundation, Inc.,                                             *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                   *
\******************************************************************************/

#include "SongManager.h"

Artist SongManager::getArtist(uid id) const
{
	Artist artist;

	artist.setID(id);
	artist.setColor( QColor(0, 255, 255) );
	artist.addArtistName(QString::fromUtf8("Morning Musume"), QString("en"));
	artist.addArtistName(QString::fromUtf8("モーニング娘。"), QString("ja"));

	return artist;
};

/*
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

SongManager::SongManager()
{
	mTablePrefix = QString("un_");
};

Album SongManager::getAlbum(uid id)
{
	QSqlQuery query(mDatabase);
	query.prepare(QString("SELECT * FROM %1 WHERE uid = ? LIMIT 1").arg(mTablePrefix + "albums"));
	query.bindValue(0, QVariant((int)id));
	query.exec();

	if(!query.next())
		return Album(0);

	QSqlRecord rec = query.record();

	Album album(0);
	album.setID(id);
	album.setName( rec.value("name").toString() );
	album.setNativeLang( rec.value("native_lang").toString() );
	album.setLangOverride( rec.value("override_lang").toString() );
	album.setComments( rec.value("comments").toString() );
	album.setReleaseDate( rec.value("release_date").toDate() );
	album.setFormat( rec.value("format").toString() );
	album.setCompilation( rec.value("compilation").toBool() );

	// Fetch the album titles
	query.clear();
	query.prepare(QString("SELECT * FROM %1 WHERE uid = ?").arg(mTablePrefix + "album_titles"));
	query.bindValue(0, QVariant((int)id));
	query.exec();
	while(query.next())
	{
		rec = query.record();
		album.addAlbumTitle( rec.value("name").toString(), rec.value("lang").toString() );
	}

	// Fetch the album variations
	query.clear();
	query.prepare(QString("SELECT * FROM %1 WHERE uid = ?").arg(mTablePrefix + "album_variations"));
	query.bindValue(0, QVariant((int)id));
	query.exec();
	while(query.next())
	{
		rec = query.record();
		album.addAlbumVariation( rec.value("name").toString(), rec.value("lang").toString() );
	}

	// Fetch the album artists
	query.clear();
	query.prepare(QString("SELECT * FROM %1 WHERE uid = ?").arg(mTablePrefix + "album_artist_ids"));
	query.bindValue(0, QVariant((int)id));
	query.exec();
	while(query.next())
	{
		rec = query.record();
		album.addArtist( rec.value("relid").toInt() );
	}

	// Fetch the album publishers
	query.clear();
	query.prepare(QString("SELECT * FROM %1 WHERE uid = ?").arg(mTablePrefix + "album_publisher_ids"));
	query.bindValue(0, QVariant((int)id));
	query.exec();
	while(query.next())
	{
		rec = query.record();
		album.addPublisher( rec.value("relid").toInt() );
	}

	// Fetch the album covers
	query.clear();
	query.prepare(QString("SELECT * FROM %1 WHERE uid = ?").arg(mTablePrefix + "album_covers"));
	query.bindValue(0, QVariant((int)id));
	query.exec();
	while(query.next())
	{
		rec = query.record();
		album.addCover( rec.value("relid").toInt(), rec.value("title").toString() );
	}

	// Fetch the album identifiers
	query.clear();
	query.prepare(QString("SELECT * FROM %1 WHERE uid = ?").arg(mTablePrefix + "album_identifiers"));
	query.bindValue(0, QVariant((int)id));
	query.exec();
	while(query.next())
	{
		rec = query.record();
		album.addIdentifier( rec.value("value").toString(), rec.value("ident").toString() );
	}

	// Fetch the album tracks
	query.clear();
	query.prepare(QString("SELECT * FROM %1 WHERE uid = ?").arg(mTablePrefix + "album_tracks"));
	query.bindValue(0, QVariant((int)id));
	query.exec();
	while(query.next())
	{
		rec = query.record();
		album.addTrack( rec.value("song_id").toInt(), rec.value("track").toInt(), rec.value("disc").toInt() );
	}

	return album;
};

void SongManager::setAlbum(const Album& album)
{
	Album block(album);
	QMap<QString, QVariant> values;
	QMap<QString, QVariant> lookup;

	int id = (int)block.id();
	int tableID = -1;

	// The main albums table
	lookup["uid"] = id;
	tableID = getTableID(mTablePrefix + "albums", lookup, mDatabase);
	values = addUtopiaBlockColumns(values, album);
	values["release_date"] = block.releaseDate();
	values["format"] = block.format();
	values["compilation"] = block.isCompilation();
	updateEntry(mTablePrefix + "albums", values, tableID, mDatabase);

	// The album_titles table
	updateLanguageSet(mTablePrefix + "album_titles", block.albumTitles(), block.id(), mDatabase);

	// The album_variations table
	updateLanguageSet(mTablePrefix + "album_variations", block.albumTitles(), block.id(), mDatabase);

	// The album_artist_ids table
	updateUidSet(mTablePrefix + "album_artist_ids", block.artists(), block.id(), mDatabase);

	// The album_publisher_ids table
	updateUidSet(mTablePrefix + "album_publisher_ids", block.publishers(), block.id(), mDatabase);
};

QSqlError SongManager::updateUidSet(const QString& tableName, const QList<uid>& sets, uid id, QSqlDatabase db)
{
	/// @TODO Remove relids no longer in the list
	/// Let's do this by a removeEntry and a loop,
	/// maybe even throw the combo into a seaparate class?
	/// OR we could clear all relids out and just insert the
	/// used ones back.
	QList<uid> relids = sets;
	QMap<QString, QVariant> values;
	QMap<QString, QVariant> lookup;
	int tableID = -1;

	int numSets = relids.count();
	for(int i = 0; i < numSets; i++)
	{
		lookup.clear();
		lookup["uid"] = (int)id;
		lookup["relid"] = (int)relids.at(i);

		values.clear();
		values["relid"] = (int)relids.at(i);

		tableID = getTableID(tableName, lookup, db);
		updateEntry(tableName, values, tableID, db);
	}

	return QSqlError();
};

QMap<QString, QVariant> SongManager::addUtopiaBlockColumns(const QMap<QString, QVariant>& values, const UtopiaBlock& block)
{
	UtopiaBlock iblock(block);
	QMap<QString, QVariant> ivalues = values;

	ivalues["uid"] = (int)iblock.id();
	ivalues["name"] = iblock.name();
	ivalues["native_lang"] = iblock.nativeLang();
	ivalues["override_lang"] = iblock.langOverride();
	ivalues["comments"] = iblock.comments();

	return ivalues;
};

QSqlError SongManager::updateLanguageSet(const QString& tableName, const QMap<QString, QString>& sets, uid id, QSqlDatabase db)
{
	/// @TODO Remove languages no longer in the list
	QMap<QString, QVariant> values;
	QMap<QString, QVariant> lookup;
	int tableID = -1;

	int numSets = sets.keys().count();
	for(int i = 0; i < numSets; i++)
	{
		lookup.clear();
		lookup["uid"] = (int)id;
		lookup["lang"] = sets.keys().at(i);

		values.clear();
		values["name"] = sets.value( sets.keys().at(i) );

		tableID = getTableID(tableName, lookup, db);
		updateEntry(tableName, values, tableID, db);
	}

	/// @TODO Do better error handling here
	return QSqlError();
};

int SongManager::getTableID(const QString& tableName, const QMap<QString, QVariant>& values, QSqlDatabase db)
{
	QSqlQuery query(db);
	QStringList keys( values.keys() );

	QStringList bindSet;
	for(int i = 0; i < keys.count(); i++)
	{
		bindSet << keys.at(i) + QString(" = :") + keys.at(i);
	}

	query.prepare(QString("SELECT id FROM %1 WHERE %2 LIMIT 1").arg(tableName).arg(bindSet.join(", ")));

	for(int i = 0; i < keys.count(); i++)
	{
		query.bindValue( ":" + keys.at(i), values.value( keys.at(i) ) );
	}
	query.exec();

	if(query.next())
		return query.record().value("id").toInt();

	return -1;
}

// You want to add uid to the values and set id to the internal id for the table entry, tableName should already have the table prefix added.
QSqlError SongManager::updateEntry(const QString& tableName, const QMap<QString, QVariant>& values, int id, QSqlDatabase db)
{
	QSqlQuery check(db), query(db);

	if(id != -1)
	{
		check.prepare(QString("SELECT * FROM %1 WHERE id = ? LIMIT 1").arg(tableName));
		check.bindValue(0, id);
		check.exec();
	}

	// Prepare our list of values
	QStringList keys( values.keys() );
	QStringList bindValues = keys;
	for(int i = 0; i < bindValues.count(); i++)
	{
		bindValues[i] = QString(":") + bindValues.at(i);
	}

	if(check.next())
	{
		// We need to update
		QStringList updateValues = bindValues;
		for(int i = 0; i < updateValues.count(); i++)
		{
			updateValues[i] = keys.at(i) + QString(" = ") + bindValues.at(i);
		}

		query.prepare(QString("UPDATE %1 SET %2 WHERE id = :id").arg(tableName).arg(updateValues.join(", ")));
		query.bindValue(":id", id);
	}
	else
	{
		// We need to insert
		query.prepare(QString("INSERT INTO %1 (%2) VALUES (%3)").arg(tableName).arg(keys.join(", ")).arg(bindValues.join(", ")));
	}

	for(int i = 0; i < keys.count(); i++)
	{
		query.bindValue( bindValues.at(i), values.value( keys.at(i) ) );
	}

	if( query.exec() )
		return QSqlError();
	else
		return query.lastError();
};

/// @TODO Add error checking
void SongManager::createAlbumTables()
{
	QString tableName;
	QStringList columns;

	// Main table
	tableName = mTablePrefix + QString("albums");
	columns << defaultColumns();
	columns << utopiaBlockColumns();
	columns << QString("release_date VARCHAR(10)");
	columns << QString("format VARCHAR(32)");
	columns << QString("compilation TINYINT(1) NOT NULL");
	createTable(tableName, columns, mDatabase);
	columns.clear();

	// Title table
	tableName = mTablePrefix + QString("album_titles");
	columns << defaultColumns();
	columns << languageSet();
	createTable(tableName, columns, mDatabase);
	columns.clear();

	// Variation table
	tableName = mTablePrefix + QString("album_variations");
	columns << defaultColumns();
	columns << languageSet();
	createTable(tableName, columns, mDatabase);
	columns.clear();

	// Artists table
	tableName = mTablePrefix + QString("album_artist_ids");
	columns << defaultColumns();
	columns << uidSet();
	createTable(tableName, columns, mDatabase);
	columns.clear();

	// Publisher table
	tableName = mTablePrefix + QString("album_publisher_ids");
	columns << defaultColumns();
	columns << uidSet();
	createTable(tableName, columns, mDatabase);
	columns.clear();

	// Covers table
	tableName = mTablePrefix + QString("album_covers");
	columns << defaultColumns();
	columns << uidSet();
	columns << QString("title VARCHAR(128)");
	createTable(tableName, columns, mDatabase);
	columns.clear();

	// Identifiers table
	tableName = mTablePrefix + QString("album_identifiers");
	columns << defaultColumns();
	columns << QString("uid INT UNSIGNED NOT NULL");
	columns << QString("ident VARCHAR(32)");
	columns << QString("value VARCHAR(128)");
	createTable(tableName, columns, mDatabase);
	columns.clear();

	// Tracks table
	tableName = mTablePrefix + QString("album_tracks");
	columns << defaultColumns();
	columns << QString("album_id INT UNSIGNED NOT NULL");
	columns << QString("song_id INT UNSIGNED NOT NULL");
	columns << QString("song_edition_id INT UNSIGNED NOT NULL");
	columns << QString("track INT UNSIGNED NOT NULL");
	columns << QString("disc INT UNSIGNED NOT NULL");
	createTable(tableName, columns, mDatabase);
	columns.clear();
};

QStringList SongManager::defaultColumns()
{
	QStringList columns;
	columns << QString("id INT UNSIGNED NOT NULL PRIMARY KEY");
	return columns;
};

QStringList SongManager::languageSet()
{
	QStringList columns;
	columns << QString("uid INT UNSIGNED NOT NULL");
	columns << QString("lang VARCHAR(5)");
	columns << QString("name VARCHAR(256)");
	return columns;
};

QStringList SongManager::uidSet()
{
	QStringList columns;
	columns << QString("uid INT UNSIGNED NOT NULL");
	columns << QString("relid VARCHAR(5)"); // Related ID
	return columns;
};

QStringList SongManager::utopiaBlockColumns()
{
	QStringList columns;
	columns << QString("uid INT UNSIGNED NOT NULL");
	columns << QString("name VARCHAR(128)");
	columns << QString("native_lang VARCHAR(5)");
	columns << QString("override_lang VARCHAR(5)");
	columns << QString("comments VARCHAR(4096)");
	return columns;
};

QSqlError SongManager::createTable(const QString& tableName, const QStringList& columns, QSqlDatabase db)
{
	QSqlQuery query(db);
	query.prepare( QString("CREATE TABLE %1 ( %2 )").arg(tableName).arg(columns.join(QString(", "))) );
	if( query.exec() )
		return QSqlError();
	else
		return query.lastError();
};
*/
