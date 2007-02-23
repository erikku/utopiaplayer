/*************************************************************************\
*  UtopiaPlayer - A song manager and icecast streaming agent              *
*  Copyright (C) 2006 John Eric Martin <cpuwhiz105@users.sourceforge.net> *
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

/**
 * @file ipod.h The base class defining the iPod device
 */

#ifndef __iPod_h__
#define __iPod_h__

#include "Device.h"

#include <QtCore/QMap>

class iPodNotes;

class QAction;
class QTreeWidgetItem;

class iPod : public Device
{
	Q_OBJECT

public:
	iPod(const QString& path, DeviceInterface *plugin, QObject *parent = 0);

	virtual QTreeWidgetItem* baseItem();

	virtual QList<QAction*> contextMenu(QTreeWidgetItem *item) const;

	virtual QString name() const;

public slots:
	void closeTab();
	void loadConfig();
	void saveConfig();
	void showNoteEditor();
	void addNoteDirectory(const QString& dir);
	void addNoteFile(const QString& file);

	void newNote();
	void newNoteFolder();

public:
	QString pathFromNode(QTreeWidgetItem *node) const;
	void sortNotesDirectory(QTreeWidgetItem *node);

	QMap<QTreeWidgetItem*, QString> mNotesMap; // item, path

	QList<iPodNotes*> mNoteTabs;

	QList<QAction*> mNoteFileActions;
	QList<QAction*> mNoteFolderActions;

	QString mPath;
	QString mNotesPath;

	QByteArray mDeviceInfo; // iPod_Control/iTunes/DeviceInfo

	QTreeWidgetItem *mBaseItem;
	QTreeWidgetItem *mMusicItem;
	QTreeWidgetItem *mVideosItem;
	QTreeWidgetItem *mNotesItem;
	QTreeWidgetItem *mImagesItem;
	QTreeWidgetItem *mPlaylistsItem;
};

#endif // __iPod_h__
