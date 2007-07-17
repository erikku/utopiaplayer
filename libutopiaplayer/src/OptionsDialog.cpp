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

#include <QtCore/QSettings>
#include <QtGui/QLineEdit>

#include "OptionsDialog.h"
#include "Application.h"
#include "PluginManager.h"

OptionsDialog::OptionsDialog(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.OKButton, SIGNAL(clicked()), this, SLOT(acceptChanges()));
	connect(ui.ApplyButton, SIGNAL(clicked()), this, SLOT(applyChanges()));
	connect(ui.CancelButton, SIGNAL(clicked()), this, SLOT(revertAndClose()));

	QSettings settings;

	mMusicDirectory = settings.value("General/MusicDirectory").toString();
	mLyricsDirectory = settings.value("General/LyricsDirectory").toString();
	mCoversDirectory = settings.value("General/CoversDirectory").toString();
	mLoginAtStart = settings.value("Login/AutoLogin").toInt();
	mUseKanji = settings.value("General/UseKanji").toInt();

	if(settings.contains("General/OutputPlugin"))
		mOutputPlugin = settings.value("General/OutputPlugin").toString();
	else
		mOutputPlugin = tr("Null Output");

	ui.OutputPluginCombo->addItems(uApp->pluginManager()->pluginsList());

	revertChanges();
};

void OptionsDialog::revertChanges()
{
	ui.MusicDirectoryEdit->setText( mMusicDirectory );
	ui.LyricsDirectoryEdit->setText( mLyricsDirectory );
	ui.CoversDirectoryEdit->setText( mCoversDirectory );
	ui.LoginAtStart->setCheckState((Qt::CheckState)mLoginAtStart);
	ui.UseKanji->setCheckState((Qt::CheckState)mUseKanji);

	for(int i = 0; i < ui.OutputPluginCombo->count(); i++)
	{
		if(ui.OutputPluginCombo->itemText(i) == mOutputPlugin)
		{
			ui.OutputPluginCombo->setCurrentIndex(i);
			i = ui.OutputPluginCombo->count();
		}
	}
};

void OptionsDialog::revertAndClose()
{
	revertChanges();
	close();
};

void OptionsDialog::applyChanges()
{
	QSettings settings;

	settings.setValue("General/MusicDirectory", ui.MusicDirectoryEdit->text());
	settings.setValue("General/LyricsDirectory", ui.LyricsDirectoryEdit->text());
	settings.setValue("General/CoversDirectory", ui.CoversDirectoryEdit->text());
	settings.setValue("Login/AutoLogin", ui.LoginAtStart->checkState());
	settings.setValue("General/UseKanji", ui.UseKanji->checkState());

	if(ui.OutputPluginCombo->currentText() != uApp->pluginManager()->currentOutputPlugin())
	{
		uApp->pluginManager()->setCurrentOutputPlugin(ui.OutputPluginCombo->currentText());
	}
	settings.setValue("General/OutputPlugin", ui.OutputPluginCombo->currentText());

	emit optionsChanged();
};

void OptionsDialog::acceptChanges()
{
	applyChanges();
	close();
};
