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

#ifndef __VolumeEdit_h__
#define __VolumeEdit_h__

#include "ui_VolumeEdit.h"

#include <QtCore/QMap>

class VolumeDevice;

class VolumeEdit : public QWidget
{
	Q_OBJECT

public:
	VolumeEdit(VolumeDevice *device, QWidget *parent = 0);

public slots:
	void accept();
	void apply();

protected:
	Ui::VolumeEdit ui;

	VolumeDevice *mDevice;
};

#endif // __VolumeEdit_h__
