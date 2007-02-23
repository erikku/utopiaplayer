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

#ifndef __Device_h__
#define __Device_h__

#include <QtCore/QObject>

class QAction;
class QTreeWidgetItem;

class DeviceInterface;

class Device : public QObject
{
	Q_OBJECT

public:
	Device(DeviceInterface *plugin, QObject *parent = 0) : QObject(parent), mDevicePlugin(plugin) { };

	virtual DeviceInterface* plugin() { return mDevicePlugin; };

	virtual QTreeWidgetItem* baseItem() = 0;
	virtual QList<QAction*> contextMenu(QTreeWidgetItem *item) const = 0;

	virtual QString name() const = 0;

protected:
	DeviceInterface *mDevicePlugin;
};

#endif // __Device_h__
