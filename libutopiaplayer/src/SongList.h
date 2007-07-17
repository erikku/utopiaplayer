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

/**
 * @file SongList.h Definition of the SongList class.
 */

#ifndef __SongList_h__
#define __SongList_h__

#include "DatabaseList.h"

// Unique ID
// {UtopiaPlayer|DB:0x3A4E7F|ID:0x3F2853}/{UtopiaPlayer|DB:0xC2186B|ID:0xA3D589}

class QSignalMapper;

/**
 * @brief A class derived from DatabaseList to display the songs in the database.
 */
class SongList : public DatabaseList
{
	Q_OBJECT

public:
	SongList(QWidget *parent = 0);

	QList<int> selectedRows() const;
	QString getSongAtRow(int) const;
};

#endif // __SongList_h__
