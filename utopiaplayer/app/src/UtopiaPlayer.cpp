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

/**
 * @file UtopiaPlayer.cpp The core UtopiaPlayer file
 */

// Qt includes
#include <QtGui/QMessageBox>

// KDE includes
//#include <kaboutdata.h>
//#include <kcmdlineargs.h>
//#include <klocalizedstring.h>

// UtopiaPlayer includes
#include "UtopiaPlayer.h"
#include "Application.h"

void DisplayError(int argc, char* argv[], QString error)
{
	if(argv)
		QApplication a(argc, argv);

	QMessageBox::critical(0, QObject::tr("Utopia Player"),
		QObject::tr("UtopiaPlayer has encountered the following exception:") + QString("\n\n") + error +
		QString("\n") + QObject::tr("Please report the above error, log files, and a description of how to") +
		QString("\n") + QObject::tr("reproduce the error to the Cinematic eMotion LLC bug tracker.") +
		QString("\n\n") + QObject::tr("For more information on reporting errors, consult the documentation."));
};

int main(int argc, char* argv[])
{
	bool Started = false;

	try
	{
		//KAboutData about("utopiaplayer", QObject::tr("Utopia Player"), UTOPIAPLAYER_VERSION,
			//QObject::tr("A multi-lingual media player."), KAboutData::License_GPL_V2, "© 2006 John Eric Martin", "http://www.emotionalcoder.com/utopiaplayer");

		//about.addAuthor("John Eric Martin", QObject::tr("Author & Maintainer"), "john.eric.martin@gmail.com", "http://www.emotionalcoder.com");
		//about.addCredit("James Harris", QObject::tr("Icons"), "jdmjim@gmail.com");

		//KCmdLineArgs::init(argc, argv, &about);

		//Application::setStyle( new QDarkPlastiqueStyle );
		Application App(argc, argv);

		Started = true;

        // Setup the application
        App.Init();

		return App.exec();
	}
	catch (const std::exception& e)
	{
		// Send error to a message box
		if(!Started)
			DisplayError(argc, argv, e.what());
		else
			DisplayError(argc, NULL, e.what());

		return -1;
	}

	return -1;
};
