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

#ifndef __SaveTagsThread_h__
#define __SaveTagsThread_h__

#include <QtCore/QThread>
#include <QtCore/QSettings>
#include <QtCore/QVariant>
#include <QtCore/QDate>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
//#include <taglib.h>
//#include <fileref.h>
//#include <tstring.h>
//#include <tag.h>

class SaveTagsThread : public QThread
{
	Q_OBJECT
			
public:
	SaveTagsThread(QSqlDatabase db);

	void run();

signals:
	void valueChanged(int i);
	void finished();
	
protected:
	QSqlDatabase database;
};

#endif // __SaveTagsThread_h__
