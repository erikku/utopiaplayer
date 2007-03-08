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

#ifndef __songlistmodel_h__
#define __songlistmodel_h__

#include <QtCore/QAbstractTableModel>

class SongList;

/**
 * We are making this model read only for the time being, we don't really
 * have to make it editable, we can use the database classes with a uid
 * gleened from the model.
 *
 * @todo CORRECTION - we need to make the editable so we can add and remove items
 * to a song list, yes, we can do this be editing the list directly, but lets
 * be nice and let them do it here to if they want to.
 * @todo Implement sort()
 */
class StringListModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	StringListModel(SongList* = 0, QObject* = 0);

	int rowCount(const QModelIndex& = QModelIndex()) const;
	int columnCount(const QModelIndex& = QModelIndex()) const;

	QVariant headerData(int, Qt::Orientation, int) const;
	bool setHeaderData(int, Qt::Orientation, const QVariant&, int);

	QVariant data(const QModelIndex&, int) const;

	SongList* songList();

public slots:
	void setSongList(SongList*);

signals:
	void songListChanged();

protected:
	SongList* mSongList;
};

#endif // __songlistmodel_h__
