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

#include "VolumeDevice.h"
#include "VolumeEdit.h"
#include "Application.h"

#include <QtCore/QFile>
#include <QtCore/QSettings>

#include <QtGui/QIcon>
#include <QtGui/QAction>
#include <QtGui/QTreeWidgetItem>

//#include <kicon.h>
//#include <klocalizedstring.h>

VolumeDevice::VolumeDevice(const QString& path, DeviceInterface *plugin, QObject *parent) : Device(plugin, parent), mPath(path)
{
	loadConfig();

	mBaseItem = new QTreeWidgetItem(QStringList() << mVolumeName);
	mBaseItem->setIcon(0, uApp->icon("devices/hdd_unmount"));

	mMusicItem = new QTreeWidgetItem(QStringList() << tr("Music"));
	mMusicItem->setIcon(0, uApp->icon("filesystems/folder_sound"));
	mBaseItem->addChild( mMusicItem );

	mVideosItem = new QTreeWidgetItem(QStringList() << tr("Videos"));
	mVideosItem->setIcon(0, uApp->icon("filesystems/folder_video"));
	mBaseItem->addChild( mVideosItem );

	mPlaylistsItem = new QTreeWidgetItem(QStringList() << tr("Playlists"));
	mPlaylistsItem->setIcon(0, uApp->icon("filesystems/folder_favorite"));
	mBaseItem->addChild( mPlaylistsItem );

	QAction *action = new QAction(0);
	action->setSeparator(true);
	mVideoActions << action;

	action = new QAction(tr("&Sync"), 0);
	mVideoActions << action;

	mEditAction = new QAction(tr("Edit &Volume..."), 0);
	connect(mEditAction, SIGNAL(triggered(bool)), this, SLOT(showEditDialog()));
};

void VolumeDevice::loadConfig()
{
	QFile configFile( mPath + tr("/.utopiaplayer/volume.ini") );
	if(!configFile.exists())
		return;

	QSettings settings(mPath + tr("/.utopiaplayer/volume.ini"), QSettings::IniFormat);

	QString volumeName;
	if(settings.contains("General/Name"))
		mVolumeName = settings.value("General/Name").toString();
	else
		mVolumeName = tr("Untitled Volume");
};

void VolumeDevice::saveConfig()
{
	QSettings settings(mPath + tr("/.utopiaplayer/volume.ini"), QSettings::IniFormat);

	settings.setValue("General/Name", mVolumeName);
};

QTreeWidgetItem* VolumeDevice::baseItem()
{
	return mBaseItem;
};

QList<QAction*> VolumeDevice::contextMenu(QTreeWidgetItem *item) const
{
	QList<QAction*> list;

	if(item == mVideosItem)
		list << mVideoActions;

	return list;
};

QString VolumeDevice::path() const
{
	return mPath;
};

QString VolumeDevice::name() const
{
	return mVolumeName;
};

QAction* VolumeDevice::editAction()
{
	return mEditAction;
};

void VolumeDevice::showEditDialog()
{
	(new VolumeEdit(this))->show();
};

void VolumeDevice::setName(const QString& name)
{
	mVolumeName = name;
	mBaseItem->setText(0, name);
	emit deviceChanged();
};
