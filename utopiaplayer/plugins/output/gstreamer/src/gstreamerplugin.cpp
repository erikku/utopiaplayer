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
 * @file GStreamerPlugin.cpp The gstreamer class implemintation
 */

#include <QtCore/QTimer>
#include <iostream>

#include "Application.h"
#include "gstreamerplugin.h"

Q_EXPORT_PLUGIN2(gstreamerplugin, GStreamerPlugin)

QString GStreamerPlugin::pluginName() const
{
	return tr("GStreamer");
};

void GStreamerPlugin::load()
{
	OutputInterface::load();

	std::cout << "Loading the GStreamer plugin" << std::endl;
	setupPipeline();
};

GStreamerPlugin::~GStreamerPlugin()
{
	if(isLoaded())
		unload();
};

void GStreamerPlugin::unload()
{
	std::cout << "Unloading the GStreamer plugin" << std::endl;
	stop();
	gst_object_unref(GST_OBJECT(mPlayBin));

	OutputInterface::unload();
};

static GstBusSyncReply messageHandler(GstBus*, GstMessage* message, gpointer data)
{
	if(GST_MESSAGE_TYPE(message) == GST_MESSAGE_EOS)
	{
		GStreamerPlugin* player = static_cast<GStreamerPlugin*>(data);
		player->emitSongFinished();
    }

    gst_message_unref(message);
    return GST_BUS_DROP;
}

void GStreamerPlugin::play(const QUrl& url)
{
	if(!url.isValid())
	{
		std::cout << "Invalid URL: " << url.errorString().toLocal8Bit().data() << std::endl;
		return;
	}

	stop();
	g_object_set(G_OBJECT(mPlayBin), "uri", url.toString().toLocal8Bit().data(), static_cast<gpointer>(0));
	mCurrentFile = url;

	std::cout << "Using the GStreamer plugin to play " << url.toString().toLocal8Bit().data() << std::endl;

	gst_element_set_state(mPlayBin, GST_STATE_PLAYING);
};

void GStreamerPlugin::pause()
{
	gst_element_set_state(mPlayBin, GST_STATE_PAUSED);
};

void GStreamerPlugin::unpause()
{
	gst_element_set_state(mPlayBin, GST_STATE_PLAYING);
};

void GStreamerPlugin::stop()
{
	gst_element_set_state(mPlayBin, GST_STATE_NULL);
	mCurrentFile.clear();
};

void GStreamerPlugin::setVolume(float volume)
{
	g_object_set(G_OBJECT(mPlayBin), "volume", volume, static_cast<gpointer>(0));
};

float GStreamerPlugin::volume() const
{
	gdouble value;
	g_object_get(G_OBJECT(mPlayBin), "volume", &value, static_cast<gpointer>(0));

	return (float)value;
};

bool GStreamerPlugin::isPlaying() const
{
	return state() == GST_STATE_PLAYING;
};

bool GStreamerPlugin::isPaused() const
{
	return state() == GST_STATE_PAUSED;
};

qint64 GStreamerPlugin::totalTime() const
{
	return time(TotalLength) / GST_SECOND;
};

qint64 GStreamerPlugin::currentTime() const
{
	return time(CurrentPosition) / GST_SECOND;
};

void GStreamerPlugin::seek(qint64 ms)
{
	gst_element_seek(mPlayBin, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, GST_SEEK_TYPE_SET, ms * GST_SECOND, GST_SEEK_TYPE_END, 0);
};

void GStreamerPlugin::setupPipeline()
{
	static bool initialized = false;
	if(!initialized)
	{
		int argc = uApp->argc();
		char **argv = uApp->argv();
		gst_init(&argc, &argv);
		initialized = true;
	}

	mPlayBin = gst_element_factory_make("playbin", "playbin");
	gst_bus_set_sync_handler(gst_pipeline_get_bus(GST_PIPELINE(mPlayBin)), messageHandler, this);
};

long long GStreamerPlugin::time(TimeQuery type) const
{
	GstQuery *query = (type == CurrentPosition) ? gst_query_new_position(GST_FORMAT_TIME) : gst_query_new_duration(GST_FORMAT_TIME);

	gint64 ns = 0;
	GstFormat format;

	if(gst_element_query(mPlayBin, query))
	{
		if(type == CurrentPosition)
			gst_query_parse_position(query, &format, &ns);
		else
			gst_query_parse_duration(query, &format, &ns);
	}

	gst_query_unref(query);

	return ns;
};

GstState GStreamerPlugin::state() const
{
	GstState state;
	gst_element_get_state(mPlayBin, &state, NULL, GST_CLOCK_TIME_NONE);

	return state;
};
