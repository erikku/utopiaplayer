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

#include "UtopiaDBImportOptions.h"
#include "Application.h"

#include <QtGui/QFileDialog>

UtopiaDBImportOptions::UtopiaDBImportOptions()
{
	ui.setupUi(this);

	setFixedSize(size());
	setWindowFlags(Qt::Dialog);
	setWindowModality(Qt::WindowModal);
	setAttribute(Qt::WA_DeleteOnClose);

	ui.FileBrowseButton->setIcon(uApp->icon("actions/fileopen"));

	connect(ui.FilePathEdit, SIGNAL(textChanged(const QString&)), this, SLOT(update()));
	connect(ui.FileBrowseButton, SIGNAL(clicked()), this, SLOT(browse()));
	connect(ui.ButtonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.ButtonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(cancel()));
};

UtopiaDBImportOptions::~UtopiaDBImportOptions()
{
};

void UtopiaDBImportOptions::update()
{
	ui.ButtonBox->button(QDialogButtonBox::Ok)->setEnabled( QFile(ui.FilePathEdit->text()).exists() );
};

void UtopiaDBImportOptions::browse()
{
	QString path = QFileDialog::getOpenFileName(this, tr("UtopiaDB File..."));
	if(!path.isEmpty())
		ui.FilePathEdit->setText(path);
};

void UtopiaDBImportOptions::cancel()
{
	close();
};

void UtopiaDBImportOptions::accept()
{
	close();
};
