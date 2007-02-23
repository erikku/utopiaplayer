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

#include "sqlparsers.h"

#include "utopiablock.h"

#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>

using namespace Utopia;

namespace Utopia
{
	static QMap<QString, SqlParser*> gSqlParsers;
};

void SqlParser::initParsers()
{
	addParser("UtopiaBlock", new UtopiaBlockSqlParser);
};

void SqlParser::addParser(const QString& name, SqlParser *parser)
{
	gSqlParsers[name] = parser;
};

void SqlParser::cleanupParsers()
{
	foreach(SqlParser *parser, gSqlParsers)
		delete parser;

	gSqlParsers.clear();
};

void UtopiaBlockSqlParser::createTables(const QSqlDatabase& db)
{
	if( db.tables(QSql::Tables).contains("UtopiaBlock") )
		return;

	QString query = "CREATE TABLE `UtopiaBlock` ("
					"  `id` int(11) NOT NULL default '0',"
					"  `uid` int(11) NOT NULL default '0',"
					"  `name` varchar(255) NOT NULL default '',"
					"  `comments` text NOT NULL default '',"
					"  `nativeLang` varchar(5) NOT NULL default '',"
					"  `langOverride` varchar(5) NOT NULL default '',"
					"  `type` varchar(32) NOT NULL default 'UtopiaBlock',"
					"  PRIMARY KEY  (`id`)"
					");";

	QSqlQuery(query, db);
};

UtopiaBlock UtopiaBlockSqlParser::read(uid id, const QSqlDatabase& db, const QString& prefix) const { return UtopiaBlock(); };
void UtopiaBlockSqlParser::insert(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix) { };
void UtopiaBlockSqlParser::update(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix) { };
void UtopiaBlockSqlParser::remove(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix) { };
