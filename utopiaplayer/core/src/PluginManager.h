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

#ifndef __PluginManager_h__
#define __PluginManager_h__

#include <QtCore/QUrl>
#include <QtCore/QMap>
#include <QtCore/QStringList>

class AudioThread;
class OutputInterface;

class PluginManager : public QObject
{
	Q_OBJECT

public:
	PluginManager(QObject* = 0);
	~PluginManager();

	void addOutputPlugin(OutputInterface*);

	void setCurrentOutputPlugin(const QString&);
	//void setCurrentOutputPlugin(OutputInterface*);
	QString currentOutputPlugin();

	QStringList pluginsList();

	qint64 totalTime() const;
    qint64 currentTime() const;

public slots:
	void setVolume(int volume);

signals:
	void finishedSong(const QUrl& file);

private:
	OutputInterface* mCurrentOutputPlugin;
	QMap<QString, OutputInterface*> outputPlugins;
};

#endif // __PluginManager_h__
