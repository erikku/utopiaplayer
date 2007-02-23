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

#include "VolumeEdit.h"
#include "VolumeDevice.h"
#include "VolumePlugin.h"

VolumeEdit::VolumeEdit(VolumeDevice *device, QWidget *parent) : QWidget(parent)
{
	mDevice = device;

	ui.setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Dialog);
	setFixedSize(size());

	ui.mNameEdit->setText( mDevice->name() );
	ui.mPathEdit->setText( mDevice->path() );

	connect(ui.mOKButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.mApplyButton, SIGNAL(clicked()), this, SLOT(apply()));
	connect(ui.mCancelButton, SIGNAL(clicked()), this, SLOT(close()));
};

void VolumeEdit::accept()
{
	apply();
	close();
};

void VolumeEdit::apply()
{
	mDevice->setName( ui.mNameEdit->text() );
	mDevice->saveConfig();
};
