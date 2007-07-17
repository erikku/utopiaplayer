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
 * @file GStreamerPlugin.h The gstreamer class defining an output plugins
 */

#ifndef __GStreamerPlugin_h__
#define __GStreamerPlugin_h__

#include <gst/gst.h>

#include "OutputInterface.h"
#include "PluginInterface.h"

class GStreamerPlugin : public QObject, public PluginInterface, public OutputInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface OutputInterface)

public:
	GStreamerPlugin() : OutputInterface(), mPlayBin(0) { };
	virtual ~GStreamerPlugin();

	virtual float volume() const;

    virtual bool isPlaying() const;
    virtual bool isPaused() const;

    virtual qint64 totalTime() const;
    virtual qint64 currentTime() const;

	virtual QString name() const { return pluginName(); };
	virtual QString pluginName() const;

//public slots:
	virtual void play(const QUrl& url = QUrl());
	virtual void pause();
	virtual void unpause();
	virtual void stop();

	virtual void setVolume(float volume = 1.0);

    virtual void seek(qint64 ms);

	virtual void load();
	virtual void unload();

private:
	void setupPipeline();

	enum TimeQuery
	{
		CurrentPosition,
		TotalLength
	};

    long long time(TimeQuery type) const;

    GstState state() const;
    GstElement* mPlayBin;
};

#endif // __GStreamerPlugin_h__
