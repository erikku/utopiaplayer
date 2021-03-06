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
 * @file volumeplugin.h The base class defining the volume device
 */

#ifndef __VolumePlugin_h__
#define __VolumePlugin_h__

#include "PluginInterface.h"
#include "DeviceInterface.h"

#include <QtCore/QObject>

class VolumeDevice;
class QTreeWidgetItem;

class VolumePlugin : public QObject, public PluginInterface, public DeviceInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface DeviceInterface)

public:
	VolumePlugin(QObject *parent = 0);
	virtual ~VolumePlugin();

	virtual QList<Device*> devices() const;
	virtual QList<QTreeWidgetItem*> deviceItems() const;
	virtual QList<QAction*> contextMenu(QTreeWidgetItem *device, QTreeWidgetItem *item) const;

	virtual QString name() const;
	virtual QString deviceName() const;

	void manageVolumes();
	void refreshDeviceList();

protected:
	QList<QAction*> mDeviceActions;
	QList<VolumeDevice*> mDevices;
};

#endif // __VolumePlugin_h__
