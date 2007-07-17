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

#ifndef __AddRemoveTestDialog_h__
#define __AddRemoveTestDialog_h__

#include <QtGui/QWidget>

class SearchEdit;
class QPushButton;
class QGridLayout;

class AddRemoveTestDialog : public QWidget
{
	Q_OBJECT

public:
	AddRemoveTestDialog(QWidget *parent = 0);

signals:
	void add(const QString& text);
	void remove(const QString& text);

public slots:
	void sendAdd();
	void sendRemove();

protected:
	SearchEdit *mAddEdit;
	SearchEdit *mRemoveEdit;
	
	QPushButton *mAddButton;
	QPushButton *mRemoveButton;
	
	QGridLayout *mLayout;
};

#endif // __AddRemoveTestDialog_h__
