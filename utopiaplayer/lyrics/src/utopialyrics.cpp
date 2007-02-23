/*************************************************************************\
*  UtopiaPlayer - A song manager and icecast streaming agent              *
*  Copyright (C) 2006 John Eric Martin <cpuwhiz105@users.sourceforge.net> *
*                                                                         *
*  This program is free software; you can redistribute it and/or modify   *
*  it under the terms of the GNU General Public License version 2 as      *
*  published by the Free Software Foundation.                             *
*                                                                         *
*  This program is distributed in the hope that it will be useful,        *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with this program; if not, write to the                          *
*  Free Software Foundation, Inc.,                                        *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
\*************************************************************************/

/**
 * @file UtopiaLyrics.cpp The core Utopia Lyrics file
 */

// KDE includes
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocalizedstring.h>

// Utopia Player includes
#include "utopiaplayer.h"

// Utopia Lyrics includes
#include "mainwindow.h"

int main(int argc, char* argv[])
{
	KAboutData about("utopialyrics", I18N_NOOP("Utopia Lyrics"), UTOPIAPLAYER_VERSION,
		I18N_NOOP("A lyrics file editor for use with Utopia Player."),
		KAboutData::License_GPL_V2, "© 2006 John Eric Martin", "http://www.emotionalcoder.com/utopiaplayer");

	about.addAuthor("John Eric Martin", I18N_NOOP("Author & Maintainer"), "john.eric.martin@gmail.com", "http://www.emotionalcoder.com");
	about.addCredit("マリウス", I18N_NOOP("Usability & Betatesting"), "marvin_theandroid@hotmail.com");
	about.addCredit("James Harris", I18N_NOOP("Icons"), "jdmjim@gmail.com");

	KCmdLineArgs::init(argc, argv, &about);

	KApplication *app = new KApplication;

	MainWindow *mainWindow = new MainWindow;
	mainWindow->show();

	return app->exec();
};
