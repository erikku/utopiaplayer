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

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

using namespace Utopia;

SqlMetaBase::SqlMetaBase(const QSqlDatabase& db, const QString& prefix, QObject *parent) : MetaBase(parent)
{
	mPrefix = prefix;
	mDatabase = db;
	mNextAvailableID = 1;
};

QList<UtopiaBlock> SqlMetaBase::blocks() const
{
	QList<UtopiaBlock> list;

	QSqlQuery query(mDatabase);
	query.prepare("SELECT :uid FROM :table");
	query.bindValue(":uid", "uid");
	query.bindValue(":table", "UtopiaBlock");
	query.exec();

	UtopiaBlock block;
	QSqlRecord record;
	while(query.next())
	{
		record = query.record();
		block.setID( record.value("uid").toInt() );
		list << block;
     }
};

QList<Album> SqlMetaBase::albums() const
{
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

void SqlMetaBase::updateBlock(const UtopiaBlock& block)
{
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
