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

#include "DeviceManager.h"
#include "DeviceInterface.h"
#include "Application.h"
#include "MainWindow.h"

#include <QtGui/QTreeWidget>

DeviceManager::DeviceManager(QObject *parent) : QObject(parent)
{
	/*
	Solid::DeviceList list = Solid::DeviceManager::self().allDevices();
	for(int i = 0; i < list.count(); i++)
	{
		uDebug("DeviceManager", tr("%1 - %2").arg( list.at(i).vendor() ).arg( list.at(i).product() ));
	}
	*/
};

DeviceManager::~DeviceManager()
{
};

void DeviceManager::registerPlugin(DeviceInterface* plugin)
{
	if(mDevicePlugins.contains(plugin->deviceName()))
		return;

	mDevicePlugins[plugin->deviceName()] = plugin;

	//connect(plugin, SIGNAL(deviceAdded(Device*)), this, SIGNAL(deviceAdded(Device*)));
	//connect(plugin, SIGNAL(deviceRemoved(Device*)), this, SIGNAL(deviceRemoved(Device*)));

	//QList<Device*> devices = plugin->devices();
	//foreach(Device *device, devices)
	//{
		//emit deviceAdded(device);
	//}

	//uApp->mainWindow()->refreshSourceList();
};

QList<QTreeWidgetItem*> DeviceManager::deviceItems() const
{
	QList<QTreeWidgetItem*> list;

	foreach(DeviceInterface* plugin, mDevicePlugins)
		list << plugin->deviceItems();

	return list;
};

QStringList DeviceManager::pluginsList() const
{
	return mDevicePlugins.keys();
};

DeviceInterface* DeviceManager::devicePluginFromTreeItem(QTreeWidgetItem *item)
{
	foreach(DeviceInterface* plugin, mDevicePlugins)
	{
		if(plugin->deviceItems().contains(item))
			return plugin;
	}

	return 0;
};
