/******************************************************************************\
*  Utopia Player - A cross-platform, multilingual, tagging media manager       *
*  Copyright (C) 2006-2007 John Eric Martin <cpuwhiz105@users.sourceforge.net> *
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

#include "SongListModel.h"
#include "SongList.h"

StringListModel::StringListModel(SongList* list, QObject* parent) : QObject(parent), mSongList(list)
{
};

int StringListModel::rowCount(const QModelIndex& parent) const
{
	if(!mSongList)
		return 0;

	return mSongList->count();
};

int StringListModel::columnCount(const QModelIndex& parent) const
{
	/// @todo Add something more here
	return 0;
};

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	/// @todo Add something more here
	return QVariant(0);
};

bool StringListModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
{
	/// @todo Add something more here
	emit headerDataChanged();

	return false;
};

QVariant StringListModel::data(const QModelIndex& index, int role) const
{
	/// @todo Add something more here
	return QVariant(0);
};

SongList* StringListModel::songList()
{
	return mSongList;
};

void StringListModel::setSongList(SongList* list)
{
	if(list)
	{
		mSongList = list;
		emit songListChanged();
	}
};
