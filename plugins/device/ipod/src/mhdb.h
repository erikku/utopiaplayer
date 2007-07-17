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

#ifndef __mhdb_h__
#define __mhdb_h__

#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtGui/QWidget>

#include "ipodnode.h"
#include "ui_mhdb.h"

extern QStringList listRecursiveDirectoryContents(const QDir& dir, const QStringList& nameFilters = QStringList(), QDir::Filters filters = QDir::NoFilter, QDir::SortFlags sort = QDir::NoSort);

class mhdb : public iPodNode, public QWidget
{
	Q_OBJECT

public:
	mhdb(QWidget *parent = 0);

	virtual quint32 type() const { return 0x6d686264; };
	virtual bool read(QFile* file);

	quint32 headerSize;		// 0x04 - size of the header
	quint32 totalSize;		// 0x08 - size of the header + children (file size)
	quint32 unk1;			// 0x0c - always 1
	quint32 versionNumber;	// 0x10 - version number of the database
	quint32 childCount;		// 0x14 - number of mhsd children
	quint64 id;				// 0x18 - id value for the database
	quint32 unk2;			// 0x20 - always 2
	quint64 unk3;			// 0x24 - who knows

protected:
	Ui::mhdb ui;
};

#endif // __mhdb_h__
