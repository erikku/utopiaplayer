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

#ifndef __Logger_h__
#define __Logger_h__

/*
 * 0 - Debug
 * 1 - Info
 * 2 - Warning
 * 3 - Error
 * 4-  Critical
 * 5 - Fatal
 */

#include <QtCore/QDateTime>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QList>

//#include <QtGui/QTextBrowser>

class LogLine
{
public:
	QString component;
	QString message;
	QDateTime stamp;
	QString file;
	int level;
	int line;
};

/*
class LogWidget : public QWidget
{
	Q_OBJECT

public:
	LogWidget(QWidget *widget);

public slots:
	addLogLine(LogLine *line);
};
*/

class Logger : public QObject
{
	Q_OBJECT

public:
	Logger(QObject *parent = 0);
	~Logger();

	int messageCount();
	LogLine* message(int index);

public slots:
	void log(int level, const QString& component, const QString& message, const QString& file, int line);

signals:
	void logMessage(const LogLine *line);

protected:
	QString mSourcePath;
	QList<LogLine*> mLog;
};

#endif // __Logger_h__
