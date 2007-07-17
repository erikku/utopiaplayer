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

#ifndef __DeviceManager_h__
#define __DeviceManager_h__

#include <QtCore/QObject>
#include <QtCore/QMap>

class Device;
class DeviceInterface;
class QTreeWidgetItem;

class DeviceManager : public QObject
{
	Q_OBJECT

public:
	DeviceManager(QObject *parent = 0);
	~DeviceManager();

	void registerPlugin(DeviceInterface* plugin);

	QStringList pluginsList() const;

	QList<QTreeWidgetItem*> deviceItems() const;

	DeviceInterface* devicePluginFromTreeItem(QTreeWidgetItem *item);

signals:
	void deviceAdded(Device *device);
	void deviceRemoved(Device *device);

protected:
	QMap<QString, DeviceInterface*> mDevicePlugins;
};

#endif // __DeviceManager_h__
