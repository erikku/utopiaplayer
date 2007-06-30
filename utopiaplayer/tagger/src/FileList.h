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

#ifndef __FileList_h__
#define __FileList_h__

#include <QtCore/QMap>
#include <QtGui/QTreeWidget>

class AudioFile;
class FileTypeFactory;

class FileList : public QTreeWidget
{
	Q_OBJECT

public:
	FileList(QWidget *parent = 0);
	~FileList();

	void addFile(const QString& file);

public slots:
	void handleItem(QTreeWidgetItem *item);

protected:
	void dropEvent(QDropEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);

	FileTypeFactory *mFileTypeFactory;

	QMap<QTreeWidgetItem*, AudioFile*> mFiles;
};

#endif // __FileList_h__
