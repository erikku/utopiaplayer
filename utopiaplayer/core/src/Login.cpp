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

#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtCore/QSettings>

#include "Login.h"
#include "Application.h"
#include "SongListWindow.h"
#include "SplashScreen.h"
#include "MainWindow.h"

Login::Login(QWidget* parent) : QWidget(parent)
{
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Dialog);
	setFixedSize(291, 291);

	ui.setupUi(this);

	SongListWindow::CenterWindow(this);

	QSettings settings;
	ui.LoginTypeCombo->setCurrentIndex(settings.value("Login/UserType").toInt());
	ui.HostEdit->setText(settings.value("Login/Host").toString());
	ui.DatabaseEdit->setText(settings.value("Login/Database").toString());
	ui.UserEdit->setText(settings.value("Login/User").toString());
	ui.PassEdit->setText(settings.value("Login/Pass").toString());
	ui.RememberLogin->setCheckState((Qt::CheckState)settings.value("Login/Remember").toInt());
	ui.LoginAtStart->setCheckState((Qt::CheckState)settings.value("Login/AutoLogin").toInt());

	updateEdits(ui.LoginTypeCombo->currentIndex());

	if(ui.LoginAtStart->checkState() == Qt::Checked)
	{
		login();
	}
	else
	{
		show();
	}

	connect(ui.LoginButton, SIGNAL(clicked()), this, SLOT(login()));
	connect(ui.LoginTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateEdits(int)));
	connect(ui.QuitButton, SIGNAL(clicked()), uApp, SLOT(quit()));
};

void Login::login()
{
	// Connect to our database
	QSqlDatabase Database = QSqlDatabase::addDatabase("QMYSQL");
	Database.setHostName( ui.HostEdit->text() );
    Database.setDatabaseName( ui.DatabaseEdit->text() );
    Database.setUserName( ui.UserEdit->text() );
    Database.setPassword( ui.PassEdit->text() );

	if(!Database.open())
	{
		show();
		QMessageBox::information( this, "UtopiaPlayer - MySQL Error",
			"<b>MySQL returned the following error:</b><br>" + Database.lastError().text() );
		return;
	}

	// Save our settings
	QSettings settings;
	settings.setValue("Login/UserType", ui.LoginTypeCombo->currentIndex());
	settings.setValue("Login/Host", ui.HostEdit->text());
	settings.setValue("Login/Database", ui.DatabaseEdit->text());
	if(ui.RememberLogin->checkState() == Qt::Checked)
	{
		settings.setValue("Login/User", ui.UserEdit->text());
		settings.setValue("Login/Pass", ui.PassEdit->text());
	}
	else
	{
		settings.setValue("Login/User", QString(""));
		settings.setValue("Login/Pass", QString(""));
	}

	settings.setValue("Login/Remember", ui.RememberLogin->checkState());
	settings.setValue("Login/AutoLogin", ui.LoginAtStart->checkState());

	// Create splash screen
	SplashScreen* mSplashScreen = new SplashScreen;
	mSplashScreen->show();

    SongListWindow *mSongListWIndow = new SongListWindow;
    mSongListWIndow->CreateInterface();
	connect(uApp, SIGNAL(lastWindowClosed()), mSongListWIndow, SLOT(saveSettings()));
	connect(uApp, SIGNAL(lastWindowClosed()), mSongListWIndow, SLOT(cleanup()));
	mSongListWIndow->show();
	//MainWindow* mainWindow = new MainWindow;
	//mainWindow->show();

	mSplashScreen->finish(mSongListWIndow);
	delete mSplashScreen;

	close();
};

void Login::updateEdits(int index)
{
	switch(index)
	{
		case 2:
			ui.DatabaseEdit->setEnabled(true);
			ui.UserEdit->setEnabled(true);
			ui.PassEdit->setEnabled(true);
			ui.RememberLogin->setEnabled(true);
			ui.LoginAtStart->setEnabled(true);
			break;
		default:
			ui.DatabaseEdit->setEnabled(true);
			ui.UserEdit->setEnabled(false);
			ui.PassEdit->setEnabled(false);
			ui.RememberLogin->setEnabled(false);
			ui.LoginAtStart->setEnabled(false);
			break;
	}
};
