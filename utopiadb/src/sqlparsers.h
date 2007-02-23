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

#ifndef __SqlParsers_h__
#define __SqlParsers_h__

#include <QtCore/QString>
#include <QtSql/QSqlDatabase>

#include "common.h"

namespace Utopia
{

class SqlParser
{
public:
	SqlParser() { };

	virtual void createTables(const QSqlDatabase& db) = 0;
	virtual UtopiaBlock read(uid id, const QSqlDatabase& db, const QString& prefix = QString()) const = 0;
	virtual void insert(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix = QString()) = 0;
	virtual void update(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix = QString()) = 0;
	virtual void remove(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix = QString()) = 0;

	static void initParsers();
	static void addParser(const QString& name, SqlParser *parser);
	static void cleanupParsers();
};

class UtopiaBlockSqlParser : public SqlParser
{
public:
	UtopiaBlockSqlParser() : SqlParser() { };

	virtual void createTables(const QSqlDatabase& db);
	virtual UtopiaBlock read(uid id, const QSqlDatabase& db, const QString& prefix = QString()) const;
	virtual void insert(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix = QString());
	virtual void update(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix = QString());
	virtual void remove(const UtopiaBlock& block, const QSqlDatabase& db, const QString& prefix = QString());
};

}; // namespace Utopia

#endif // __SqlParsers_h__
