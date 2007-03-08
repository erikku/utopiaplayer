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
 * @file XinePlugin.cpp The XinePlugin class implemintation
 */

#include <xine/xineutils.h>
#include <iostream>

#include "Application.h"
#include "xineplugin.h"

Q_EXPORT_PLUGIN2(xineplugin, XinePlugin)

static void XinePluginEventListener(void *xineplugin, const xine_event_t *event);

QString XinePlugin::name() const
{
	return tr("Xine");
};

void XinePlugin::load()
{
	PluginInterface::load();

	std::cout << "Loading the Xine plugin" << std::endl;
	xine = xine_new();
	QString configfile = xine_get_homedir() + QString("/.xine/config");
	xine_config_load(xine, configfile.toLocal8Bit().data());
	xine_init(xine);
	vo_port = xine_open_video_driver(xine, "null", XINE_VISUAL_TYPE_NONE, NULL);
	ao_port = xine_open_audio_driver(xine , "alsa", NULL);
	stream = xine_stream_new(xine, ao_port, vo_port);
	event_queue = xine_event_new_queue(stream);
	xine_event_create_listener_thread(event_queue, XinePluginEventListener, this);
};

XinePlugin::~XinePlugin()
{
	if(isLoaded())
		unload();
};

void XinePlugin::unload()
{
	std::cout << "Unloading the Xine plugin" << std::endl;
	stop();

	xine_close(stream);
	xine_event_dispose_queue(event_queue);
	xine_dispose(stream);
	xine_close_audio_driver(xine, ao_port);  
	xine_close_video_driver(xine, vo_port);  
	xine_exit(xine);

	PluginInterface::unload();
};

static void XinePluginEventListener(void *xineplugin, const xine_event_t *event)
{
	XinePlugin *plugin = (XinePlugin*)xineplugin;
	switch(event->type)
	{ 
		case XINE_EVENT_UI_PLAYBACK_FINISHED:
			//plugin->emitSongFinished();
			break;
	}
};

void XinePlugin::play(const QUrl& url)
{
	if(url.isEmpty())
		return;

	/*if(!url.isLocalFile())
	{
		KMessageBox::information(0, tr("UtopiaPlayer"), tr("The output plugin only supports local files!"));
		return;
	}*/

	stop();
	xine_open(stream, url.toString().toUtf8().data());
	mCurrentFile = url;

	std::cout << "Using the Xine plugin to play " << url.toString().toUtf8().data() << std::endl;

	xine_play(stream, 0, 0);
};

void XinePlugin::pause()
{
	xine_set_param(stream, XINE_PARAM_SPEED, XINE_SPEED_PAUSE);
};

void XinePlugin::unpause()
{
	xine_set_param(stream, XINE_PARAM_SPEED, XINE_SPEED_NORMAL);
};

void XinePlugin::stop()
{
	xine_stop(stream);
	if(!mCurrentFile.isEmpty())
	{
		mCurrentFile.clear();
	}
};

void XinePlugin::setVolume(float volume)
{
	xine_set_param(stream, XINE_PARAM_AUDIO_MUTE, 0);
	xine_set_param(stream, XINE_PARAM_AUDIO_VOLUME, (int)(volume * 100));
};

float XinePlugin::volume() const
{
	float vol = xine_get_param(stream, XINE_PARAM_AUDIO_VOLUME); 
	return vol / 100;
};

void XinePlugin::mute()
{
	xine_set_param(stream, XINE_PARAM_AUDIO_MUTE, 1);
};

bool XinePlugin::isMuted()
{
	return (bool)xine_get_param(stream, XINE_PARAM_AUDIO_MUTE);
};

bool XinePlugin::isPlaying() const
{
	return xine_get_param(stream, XINE_PARAM_SPEED) == XINE_SPEED_NORMAL ? true : false;
};

bool XinePlugin::isPaused() const
{
	return xine_get_param(stream, XINE_PARAM_SPEED) == XINE_SPEED_PAUSE ? true : false;
};

qint64 XinePlugin::totalTime() const
{
	int pos, time, length;
	xine_get_pos_length(stream, &pos, &time, &length);

	return length / 1000;
};

qint64 XinePlugin::currentTime() const
{
	int pos, time, length;
	xine_get_pos_length(stream, &pos, &time, &length);

	return time / 1000;
};

void XinePlugin::seek(qint64 seekTime)
{
	Q_UNUSED(seekTime);
};
