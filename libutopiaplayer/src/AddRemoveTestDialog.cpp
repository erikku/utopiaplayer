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

#include "AddRemoveTestDialog.h"
#include "SearchEdit.h"

#include <QtGui/QPushButton>
#include <QtGui/QGridLayout>

AddRemoveTestDialog::AddRemoveTestDialog(QWidget *parent) : QWidget(parent)
{
	mAddButton = new QPushButton( tr("&Add") );
	mRemoveButton = new QPushButton( tr("&Remove") );
	
	mAddEdit = new SearchEdit( tr("Enter the path to add here.") );
	mAddEdit->setAcceptDrops(true);
	mRemoveEdit = new SearchEdit( tr("Enter the path to remove here.") );
	mRemoveEdit->setAcceptDrops(true);
	
	mLayout = new QGridLayout;
	mLayout->addWidget(mAddEdit, 0, 0);
	mLayout->addWidget(mAddButton, 0, 1);
	mLayout->addWidget(mRemoveEdit, 1, 0);
	mLayout->addWidget(mRemoveButton, 1, 1);

	connect(mAddButton, SIGNAL(clicked(bool)), this, SLOT(sendAdd()));
	connect(mAddEdit, SIGNAL(returnPressed()), this, SLOT(sendAdd()));
	connect(mRemoveButton, SIGNAL(clicked(bool)), this, SLOT(sendRemove()));
	connect(mRemoveEdit, SIGNAL(returnPressed()), this, SLOT(sendRemove()));
	
	setLayout(mLayout);
};

void AddRemoveTestDialog::sendAdd()
{
	if(!mAddEdit->text().isEmpty())
	{
		QStringList elements = mAddEdit->text().split(";");
		foreach(QString element, elements)
			emit add(element);

		mAddEdit->clear();
	}
};

void AddRemoveTestDialog::sendRemove()
{
	if(!mRemoveEdit->text().isEmpty())
	{
		QStringList elements = mRemoveEdit->text().split(";");
		foreach(QString element, elements)
			emit remove(element);

		mRemoveEdit->clear();
	}
};
