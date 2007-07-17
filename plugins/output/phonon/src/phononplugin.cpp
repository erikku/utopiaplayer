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
 * @file PhononPlugin.cpp The phonon output plugin class implemintation
 */

#include "phononplugin.h"

#include <phonon/audioplayer.h>

K_EXPORT_COMPONENT_FACTORY( utopiaplayer_phonon_plugin, KGenericFactory<PhononPlugin>( "utopiaplayer_phonon_plugin" ) )

PhononPlugin::~PhononPlugin()
{
	if(isLoaded())
		unload();
};

QString PhononPlugin::pluginName() const
{
	return i18n("Phonon");
};

void PhononPlugin::load()
{
	if(isLoaded())
		return;

	mAudioPlayer = new Phonon::AudioPlayer(Phonon::MusicCategory);

	OutputInterface::load();
};

void PhononPlugin::unload()
{
	if(!isLoaded())
		return;

	delete mAudioPlayer;

	OutputInterface::unload();
};

float PhononPlugin::volume() const
{
	return mAudioPlayer->volume();
};

bool PhononPlugin::isPlaying() const
{
	return mAudioPlayer->isPlaying();
};

bool PhononPlugin::isPaused() const
{
	return mAudioPlayer->isPaused();
};

qint64 PhononPlugin::totalTime() const
{
	return mAudioPlayer->totalTime();
};

qint64 PhononPlugin::currentTime() const
{
	return mAudioPlayer->currentTime();
};

void PhononPlugin::play(const KUrl& url)
{
	return mAudioPlayer->play(url);
};

void PhononPlugin::pause()
{
	return mAudioPlayer->pause();
};

void PhononPlugin::unpause()
{
	return mAudioPlayer->play();
};

void PhononPlugin::stop()
{
	return mAudioPlayer->stop();
};

void PhononPlugin::setVolume(float volume)
{
	return mAudioPlayer->setVolume(volume);
};

void PhononPlugin::seek(qint64 ms)
{
	return mAudioPlayer->seek(ms);
};

#include "phononplugin.moc"
