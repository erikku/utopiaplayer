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

#include "VolumeList.h"
#include "VolumeEdit.h"
#include "VolumeDevice.h"
#include "VolumePlugin.h"

VolumeList::VolumeList(VolumePlugin *plugin, QWidget *parent) : QWidget(parent)
{
	mPlugin = plugin;

	ui.setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Dialog);
	setFixedSize(size());

	QString deviceName;
	QListWidgetItem *item = 0;
	QList<Device*> devices = mPlugin->devices();
	foreach(Device *device, devices)
	{
		deviceName = device->name();
		item = new QListWidgetItem(deviceName);
		ui.mVolumeList->addItem(item);
		mDevices[item] = (VolumeDevice*)device;
		connect(device, SIGNAL(deviceChanged()), this, SLOT(refreshList()));
	}
	ui.mVolumeList->sortItems();

	updateSelection();

	connect(ui.mVolumeList, SIGNAL(itemSelectionChanged()), this, SLOT(updateSelection()));
	connect(ui.mEditButton, SIGNAL(clicked()), this, SLOT(editVolume()));
	connect(ui.mCancelButton, SIGNAL(clicked()), this, SLOT(close()));
};

void VolumeList::editVolume()
{
	VolumeEdit *edit = 0;
	VolumeDevice *device = 0;

	QList<QListWidgetItem*> items = ui.mVolumeList->selectedItems();
	foreach(QListWidgetItem *item, items)
	{
		if( !mDevices.contains(item) )
			continue;

		device = mDevices.value(item);
		edit = new VolumeEdit(device, this);
		edit->show();
	}
};

void VolumeList::refreshList()
{
	foreach(QListWidgetItem *item, mDevices.keys())
	{
		item->setText(mDevices.value(item)->name());
	}
};

void VolumeList::updateSelection()
{
	bool enable = (ui.mVolumeList->selectedItems().count() > 0);

	ui.mEditButton->setEnabled(enable);
	ui.mRemoveButton->setEnabled(enable);	
};
