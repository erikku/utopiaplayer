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

#include "PluginManager.h"
#include "NullOutput.h"

#include "OutputInterface.h"
#include "Application.h"

#include <QtCore/QFile>

#include <iostream>
using namespace std;

PluginManager::PluginManager(QObject* parent) : QObject(parent)
{
	OutputInterface* plugin = new NullOutput;
	std::cout << "Added plugin Null (builtin)" << std::endl;
	addOutputPlugin(plugin);
	mCurrentOutputPlugin = plugin;
	connect(mCurrentOutputPlugin, SIGNAL(finishedSong(const QUrl&)), this, SIGNAL(finishedSong(const QUrl&)));
	setCurrentOutputPlugin(tr("Null Output"));
};

PluginManager::~PluginManager()
{
	QMapIterator<QString, OutputInterface*> i(outputPlugins);
    while(i.hasNext())
	{
		i.next();

		if(i.value()->isLoaded())
			i.value()->unload();

		delete i.value();
	}
};

void PluginManager::addOutputPlugin(OutputInterface* interface)
{
	if(!outputPlugins.contains(interface->pluginName()))
		outputPlugins[interface->pluginName()] = interface;

	interface->setAudioThread(uApp->audioThread());
};

void PluginManager::setCurrentOutputPlugin(const QString& name)
{
	if(!outputPlugins.contains(name))
		return;

	// Unload the previous plugin
	if(mCurrentOutputPlugin->isLoaded())
		mCurrentOutputPlugin->unload();
	disconnect(mCurrentOutputPlugin, SIGNAL(finishedSong(const QUrl&)), this, SIGNAL(finishedSong(const QUrl&)));

	mCurrentOutputPlugin = outputPlugins[name];

	// Load the new plugin
	if(!mCurrentOutputPlugin->isLoaded())
		mCurrentOutputPlugin->load();
	connect(mCurrentOutputPlugin, SIGNAL(finishedSong(const QUrl&)), this, SIGNAL(finishedSong(const QUrl&)));

	/////////////////////////////////////////////////////////////////////////////////
	if(name == "Null Output")
		return;
};
/*
void PluginManager::setCurrentOutputPlugin(OutputInterface* plugin)
{
	// Unload the previous plugin
	if(mCurrentOutputPlugin->isLoaded())
		mCurrentOutputPlugin->unload();
	disconnect(mCurrentOutputPlugin, SIGNAL(finishedSong(const QUrl&)), this, SIGNAL(finishedSong(const QUrl&)));

	mCurrentOutputPlugin = plugin;

	// Load the new plugin
	if(!mCurrentOutputPlugin->isLoaded())
		mCurrentOutputPlugin->load();
	connect(mCurrentOutputPlugin, SIGNAL(finishedSong(const QUrl&)), this, SIGNAL(finishedSong(const QUrl&)));
};
*/
QStringList PluginManager::pluginsList()
{
	return outputPlugins.keys();
};

QString PluginManager::currentOutputPlugin()
{
	Q_ASSERT(mCurrentOutputPlugin);

	return mCurrentOutputPlugin->pluginName();
};

void PluginManager::setVolume(int volume)
{
	if(mCurrentOutputPlugin)
		mCurrentOutputPlugin->setVolume((float)volume/100);
};

qint64 PluginManager::totalTime() const
{
	if(mCurrentOutputPlugin)
		return mCurrentOutputPlugin->totalTime();

	return 0;
};

qint64 PluginManager::currentTime() const
{
	if(mCurrentOutputPlugin)
		return mCurrentOutputPlugin->currentTime();

	return 0;
};

void PluginManager::play(const QUrl& url)
{
	if(mCurrentOutputPlugin)
		mCurrentOutputPlugin->play(url);
};
