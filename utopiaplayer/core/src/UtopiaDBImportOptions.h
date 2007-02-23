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

#ifndef __UtopiaDBImportOptions_h__
#define __UtopiaDBImportOptions_h__

#include "ui_UtopiaDBImportOptions.h"

class UtopiaDBImportOptions : public QWidget
{
	Q_OBJECT

public:
	UtopiaDBImportOptions();
	~UtopiaDBImportOptions();

public slots:
	/// Update the OK button if the file exists
	void update();
	/// Show the file selection dialog
	void browse();
	/// User clicked cancel
	void cancel();
	/// User clicked ok
	void accept();

protected:
	Ui::UtopiaDBImportOptions ui;
};

#endif // __UtopiaDBImportOptions_h__
