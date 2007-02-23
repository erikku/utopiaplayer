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

/**
 * @file volumeplugin.h The base class defining the volume device
 */

#ifndef __VolumePlugin_h__
#define __VolumePlugin_h__

#include "DeviceInterface.h"

class VolumeDevice;
class QTreeWidgetItem;

class VolumePlugin : public DeviceInterface
{
	Q_OBJECT

public:
	VolumePlugin(QObject *parent = 0, const QStringList& args = QStringList());
	virtual ~VolumePlugin();

	virtual QList<Device*> devices() const;
	virtual QList<QTreeWidgetItem*> deviceItems() const;
	virtual QList<QAction*> contextMenu(QTreeWidgetItem *device, QTreeWidgetItem *item) const;

	virtual QString pluginName() const;

public slots:
	void manageVolumes();
	void refreshDeviceList();

protected:
	QList<QAction*> mDeviceActions;
	QList<VolumeDevice*> mDevices;
};

#endif // __VolumePlugin_h__
