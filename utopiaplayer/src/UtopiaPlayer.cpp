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
 * @file UtopiaPlayer.cpp The core UtopiaPlayer file
 */

// Qt includes
#include <QtCore>
#include <QtGui/QMessageBox>

// UtopiaPlayer includes
#include "UtopiaPlayer.h"
#include "Application.h"

#include <utopiadb/sqlmetabase.h>

/**
 * @todo We need to move this to a StatucPlugins.cpp.in or something,
 * because moc will still try to include it even if you use the #if macro.
 */
#if (IPOD_PLUGIN_STATIC == ON)
//Q_IMPORT_PLUGIN(ipodplugin)
#endif

void DisplayError(int argc, char* argv[], QString error)
{
	if(argv)
		QApplication a(argc, argv);

	QMessageBox::critical(0, QObject::tr("Utopia Player"),
		QObject::tr("UtopiaPlayer has encountered the following exception:") + QString("\n\n") + error +
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

		Started = true;

        App.Init();

		/*
		QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName("test.db");
		if( !db.open() )
		{
			QMessageBox::critical(0, qApp->tr("Cannot open database"),
				App.tr("Unable to establish a database connection.\n"
				"This example needs SQLite support. Please read "
				"the Qt SQL driver documentation for information how "
				"to build it.\n\n"
				"Click Cancel to exit."), QMessageBox::Cancel);
		}
		else
		{
			Utopia::SqlMetaBase base(db, "utopia_");

			Utopia::UtopiaBlock block;
			block.setID(10);
			block.setNativeLang("en");
			base.addBlock(block);

			block.setID(35);
			block.setNativeLang("ja");
			base.addBlock(block);

			block.setNativeLang("en");
			base.updateBlock(block);
		}
		*/

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
