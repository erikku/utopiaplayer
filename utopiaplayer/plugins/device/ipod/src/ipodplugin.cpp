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

#include "ipodplugin.h"
#include "ipod.h"

#include <QtGui/QAction>

Q_EXPORT_PLUGIN2(ipodplugin, iPodPlugin)

iPodPlugin::iPodPlugin(QObject *parent) : QObject(parent), DeviceInterface()
{
	//mDevices << new iPod("/home/eric/ipod/image", this);
};

iPodPlugin::~iPodPlugin()
{
};

void iPodPlugin::load()
{
	mDevices << new iPod("/media/utopia/Music", this);
	//emit deviceAdded( mDevices.at(0) );
	
	PluginInterface::load();
};

QList<QTreeWidgetItem*> iPodPlugin::deviceItems() const
{
	QList<QTreeWidgetItem*> list;

	for(int i = 0; i < mDevices.count(); i++)
	{
		list << mDevices.at(i)->baseItem();
	}

	return list;
};

QList<QAction*> iPodPlugin::contextMenu(QTreeWidgetItem *device, QTreeWidgetItem *item) const
{
	QList<QAction*> list;

	Device *dev = 0;
	for(int i = 0; i < mDevices.count(); i++)
	{
		if(mDevices.at(i)->baseItem() == device)
		{
			dev = mDevices.at(i);
		}
	}

	if(dev)
		list << dev->contextMenu(item);

	return list;
};

QString iPodPlugin::name() const
{
	return tr("iPod");
};

QString iPodPlugin::deviceName() const
{
	return name();
};

QList<Device*> iPodPlugin::devices() const
{
	QList<Device*> devices;

	foreach(Device *device, mDevices)
	{
		devices << device;
	}

	return devices;
};

void iPodPlugin::refreshDeviceList()
{
};
