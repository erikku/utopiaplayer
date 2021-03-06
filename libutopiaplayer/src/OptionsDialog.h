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

#ifndef __OptionsDialog_h__
#define __OptionsDialog_h__

#include "ui_OptionsDialog.h"

class QLineEdit;

class OptionsDialog : public QWidget
{
	Q_OBJECT

public:
        OptionsDialog(QWidget* parent = 0);

private:
	Ui::OptionsDialog ui;

	QString mMusicDirectory;
	QString mLyricsDirectory;
	QString mCoversDirectory;
	QString mOutputPlugin;
	int mLoginAtStart;
	int mUseKanji;

	void revertChanges();

signals:
	void optionsChanged();

public slots:
	void revertAndClose();
	void applyChanges();
	void acceptChanges();
};

#endif // __OptionsDialog_h__
