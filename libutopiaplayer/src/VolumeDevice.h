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
 * @file volumedevice.h The base class defining the volume device
 */

#ifndef __VolumeDevice_h__
#define __VolumeDevice_h__

#include "Device.h"

class QAction;
class QTreeWidgetItem;

class VolumeDevice : public Device
{
	Q_OBJECT

public:
	VolumeDevice(const QString& path, DeviceInterface *plugin, QObject *parent = 0);

	virtual QTreeWidgetItem* baseItem();

	QString path() const;
	virtual QString name() const;

	QAction* editAction();
	virtual QList<QAction*> contextMenu(QTreeWidgetItem *item) const;

public slots:
	void loadConfig();
	void saveConfig();
	void showEditDialog();

	void setName(const QString& name);

signals:
	void deviceChanged();

protected:
	QString mPath;
	QString mVolumeName;

	QTreeWidgetItem *mBaseItem;
	QTreeWidgetItem *mMusicItem;
	QTreeWidgetItem *mVideosItem;
	QTreeWidgetItem *mPlaylistsItem;

	QAction *mEditAction;
	QList<QAction*> mVideoActions;
	QList<QTreeWidgetItem*> mPlaylists;
};

#endif // __VolumeDevice_h__
