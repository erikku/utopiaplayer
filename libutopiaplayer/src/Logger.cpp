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

#include "Logger.h"

#include <QtCore/QRegExp>
#include <iostream>

/*
LogWidget::addLogLine(LogLine *line)
{
	QString text;

	if(logline = 

	insertHtml(text);
};
*/

Logger::Logger(QObject *parent) : QObject(parent)
{
	mSourcePath = QString(__FILE__).replace( QRegExp("libutopiaplayer[\\\\\\/]+src[\\\\\\/]+Logger.cpp"), QString() );
};

Logger::~Logger()
{
	foreach(LogLine *line, mLog)
		delete line;
};

void Logger::log(int level, const QString& component, const QString& message, const QString& file, int line)
{
	QDateTime stamp = QDateTime::currentDateTime();
	QString sourceFile = file;
	sourceFile.replace(mSourcePath, QString());

	std::cout << QString("[%1] <%2> %3:%4 : %5").arg( stamp.toString(Qt::ISODate) ).arg(component).arg(sourceFile).arg(line).arg(message).toLocal8Bit().data() << std::endl;

	LogLine *logLine = new LogLine;
	logLine->component = component;
	logLine->message = message;
	logLine->stamp = stamp;
	logLine->file = sourceFile;
	logLine->level = level;
	logLine->line = line;

	mLog << logLine;
};
