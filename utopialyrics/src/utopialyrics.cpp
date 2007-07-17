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

/**
 * @file UtopiaLyrics.cpp The core Utopia Lyrics file
 */

// Qt includes
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

// Utopia Player includes
#include "UtopiaPlayer.h"
#include "Application.h"

// Utopia Lyrics includes
#include "mainwindow.h"

void DisplayError(int argc, char* argv[], QString error)
{
	if(argv)
		QApplication a(argc, argv);

	QMessageBox::critical(0, QObject::tr("Utopia Lyrics"),
		QObject::tr("Utopia Lyrics has encountered the following exception:") + QString("\n\n") + error +
		QString("\n") + QObject::tr("Please report the above error, log files, and a description of how to") +
		QString("\n") + QObject::tr("reproduce the error to the bug tracker.") +
		QString("\n\n") + QObject::tr("For more information on reporting errors, consult the documentation."));
};

int main(int argc, char* argv[])
{
	bool Started = false;

	try
	{	
		Application App(argc, argv);
		App.setApplicationName("Utopia Lyrics");

		Started = true;

        App.Init(Minimal);

		MainWindow *mainWindow = new MainWindow;
		mainWindow->show();

		return App.exec();
	}
	catch (const std::exception& e)
	{
		if(!Started)
			DisplayError(argc, argv, e.what());
		else
			DisplayError(argc, NULL, e.what());

		return -1;
	}

	return -1;
};
