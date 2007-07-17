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

#ifndef __DatabaseManager_h__
#define __DatabaseManager_h__

#include <QtCore/QStringList>
#include <QtCore/QString>
#include <QtCore/QObject>

class MetaBase;

class DatabaseManager : QObject
{
public:
	DatabaseManager(QObject *parent = 0) { };

public slots:
	void createDatabase(const QString& name);
	void addDatabase(const QString& name, MetaBase *database);
	void removeDatabase(const QString& name);
	void deleteDatabase(const QString& name);

	void yankDatabase(const QString& name);
	void reinstateDatabase(MetaBase *database);

signals:
	void queryResult(const QString& query, const QString& result, void* caller);

public:
	void databaseCreated(const QString& name);
	void databaseAdded(const QString& name);
	void databaseRemoved(const QString& name);
	void databaseDeleted(const QString& name);

	void databases(const QStringList& databaseList);
	void databaseListChanged(const QStringList& databaseList);

	void databaseYanked(const QString& name, MetaBase *database);
	void databaseReinstated(const QString& name);
};

#endif // __DatabaseManager_h__
