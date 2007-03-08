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
 * @file volumeplugin.cpp The base class defining the volume device
 */

#include "Application.h"
#include "VolumePlugin.h"
#include "VolumeDevice.h"
#include "VolumeList.h"

#include <QtCore/QFile>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QAction>

VolumePlugin::VolumePlugin(QObject *parent) : QObject(parent), DeviceInterface()
{
	mDevices << new VolumeDevice("/media/utopia/Music", this);
	//emit deviceAdded( mDevices.at(0) );

	QStringList volumePaths;// = UtopiaPlayerSettings::self()->volumePaths();
	for(int i = 0; i < volumePaths.count(); i++)
	{
		QFile configFile(volumePaths.at(i) + ".utopiaplayer/volume.ini");
		if(!configFile.exists())
			continue;

		mDevices << new VolumeDevice(volumePaths.at(i), this);
	}

	foreach(VolumeDevice *device, mDevices)
	{
		//connect(device, SIGNAL(deviceChanged()), (QObject*)uApp->mainWindow(), SLOT(refreshSourceList()));
	}

	QAction *action = new QAction(tr("Manage &Volumes..."), 0);
	//connect(action, SIGNAL(triggered(bool)), this, SLOT(manageVolumes()));
	mDeviceActions << action;
};

VolumePlugin::~VolumePlugin()
{
};

QString VolumePlugin::deviceName() const
{
	return name();
};

QList<QTreeWidgetItem*> VolumePlugin::deviceItems() const
{
	QList<QTreeWidgetItem*> list;

	for(int i = 0; i < mDevices.count(); i++)
	{
		list << mDevices.at(i)->baseItem();
	}

	return list;
};

QList<QAction*> VolumePlugin::contextMenu(QTreeWidgetItem *device, QTreeWidgetItem *item) const
{
	QList<QAction*> list;

	// Find our device
	VolumeDevice *dev = 0;
	for(int i = 0; i < mDevices.count(); i++)
	{
		if(mDevices.at(i)->baseItem() == device)
		{
			dev = (VolumeDevice*)mDevices.at(i);
		}
	}

	if(device == item && dev)
		list << dev->editAction();

	list << mDeviceActions;

	if(dev)
		list << dev->contextMenu(item);

	return list;
};

QString VolumePlugin::name() const
{
	return tr("Volume");
};

void VolumePlugin::refreshDeviceList()
{
};

QList<Device*> VolumePlugin::devices() const
{
	QList<Device*> devices;

	foreach(Device *device, mDevices)
	{
		devices << device;
	}

	return devices;
};

void VolumePlugin::manageVolumes()
{
	VolumeList *list = new VolumeList(this);
	list->show();
};
