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

#ifndef __SongManager_h__
#define __SongManager_h__

#include <QtCore/QVariant>
#include <QtSql/QSqlDatabase>

#include <utopiadb/artist.h>

using namespace Utopia;

class SongManager : public QObject
{
	Q_OBJECT

public:
	Artist getArtist(uid id) const;
/*
public:
	SongManager();
	Album getAlbum(uid id);

	static QSqlError createTable(const QString& tableName, const QStringList& columns, QSqlDatabase db = QSqlDatabase());
	static QSqlError updateEntry(const QString& tableName, const QMap<QString, QVariant>& values, int id = -1, QSqlDatabase db = QSqlDatabase());
	static QSqlError updateUidSet(const QString& tableName, const QList<uid>& sets, uid id = -1, QSqlDatabase db = QSqlDatabase());
	static QSqlError updateLanguageSet(const QString& tableName, const QMap<QString, QString>& sets, uid id = -1, QSqlDatabase db = QSqlDatabase());
	static int       getTableID (const QString& tableName, const QMap<QString, QVariant>& values, QSqlDatabase db = QSqlDatabase());
	static QMap<QString, QVariant> addUtopiaBlockColumns(const QMap<QString, QVariant>& values, const UtopiaBlock& block);

public slots:
	void setAlbum(const Album& album);

protected:
	void createAlbumTables();

	QStringList defaultColumns();
	QStringList languageSet();
	QStringList uidSet();
	QStringList utopiaBlockColumns();

	QString mTablePrefix;
	QSqlDatabase mDatabase;
*/
};

#endif // __SongManager_h__
