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

#ifndef __InsertAlbum_h__
#define __InsertAlbum_h__

#include "ui_InsertAlbum.h"

class InsertAlbum : public QWidget
{
	Q_OBJECT

public:
	InsertAlbum(QWidget* parent = 0);

private:
	Ui::InsertAlbum ui;

	QString mCoversDirectory;

signals:
	void updateDatabase();

public slots:
	void browse();
	void insert();
	void refreshCover(const QString &);
	void refreshOptions();
};

#endif // __InsertAlbum_h__
