/*************************************************************************\
*  UtopiaPlayer - A song manager and icecast streaming agent              *
*  Copyright (C) 2006 John Eric Martin <cpuwhiz105@users.sourceforge.net> *
*                                                                         *
*  This program is free software; you can redistribute it and/or modify   *
*  it under the terms of the GNU General Public License version 2 as      *
*  published by the Free Software Foundation.                             *
*                                                                         *
*  This program is distributed in the hope that it will be useful,        *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with this program; if not, write to the                          *
*  Free Software Foundation, Inc.,                                        *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
\*************************************************************************/

/**
 * @file ipodplugin.h The base class defining the volume device
 */

#ifndef __iPodPlugin_h__
#define __iPodPlugin_h__

#include "DeviceInterface.h"

class iPod;
class QTreeWidgetItem;

class iPodPlugin : public DeviceInterface
{
	Q_OBJECT
	Q_INTERFACES(DeviceInterface)

public:
	iPodPlugin(QObject *parent = 0, const QStringList& args = QStringList());
	virtual ~iPodPlugin();

	virtual QList<Device*> devices() const;
	virtual QList<QTreeWidgetItem*> deviceItems() const;
	virtual QList<QAction*> contextMenu(QTreeWidgetItem *device, QTreeWidgetItem *item) const;

	virtual QString pluginName() const;

public slots:
	void refreshDeviceList();

protected:
	QList<iPod*> mDevices;
};

#endif // __iPodPlugin_h__
