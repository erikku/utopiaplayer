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
 * @file deviceinterface.h The base class defining output engines/plugins
 */

#ifndef __DeviceInterface_h__
#define __DeviceInterface_h__

class QTreeWidgetItem;
class QAction;
class Device;

class DeviceInterface
{
public:
	virtual ~DeviceInterface() { };

	virtual QList<Device*> devices() const = 0;
	virtual QList<QTreeWidgetItem*> deviceItems() const = 0;
	virtual QList<QAction*> contextMenu(QTreeWidgetItem *device, QTreeWidgetItem *item) const = 0;

	virtual QString deviceName() const = 0;
	virtual void refreshDeviceList() = 0;
	/*
	void clickEmiter()
	{
		if(sender()->inherits("QTreeWidgetItem"))
			emit deviceClicked( static_cast<QTreeWidgetItem*>(sender()) );
	};
	void dblClickEmiter()
	{
		if(sender()->inherits("QTreeWidgetItem"))
			emit deviceDoubleClicked( static_cast<QTreeWidgetItem*>(sender()) );
	};
	*/
//signals:
	//void deviceClicked(QTreeWidgetItem *device);
	//void deviceDoubleClicked(QTreeWidgetItem *device);
	//void deviceListChanged();
	//void deviceAdded(Device *device);
	//void deviceRemoved(Device *device);
};

Q_DECLARE_INTERFACE(DeviceInterface, "com.emotionalcoder.UtopiaPlayer.DeviceInterface/0.1")

#endif // __DeviceInterface_h__
