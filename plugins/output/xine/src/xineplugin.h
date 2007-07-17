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
 * @file XinePlugin.h The XinePlugin class defining an output plugins
 */

#ifndef __XinePlugin_h__
#define __XinePlugin_h__

#include <xine.h>

#include "PluginInterface.h"
#include "OutputInterface.h"

class XinePlugin : public QObject, public PluginInterface, public OutputInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface OutputInterface)

public:
	XinePlugin(QObject *parent = 0) : QObject(parent), OutputInterface() { };
	virtual ~XinePlugin();

	virtual float volume() const;

    virtual bool isPlaying() const;
    virtual bool isPaused() const;

    virtual qint64 totalTime() const;
    virtual qint64 currentTime() const;

	virtual bool isMuted();

	virtual QString name() const;

	virtual void play(const QUrl& url = QUrl());
	virtual void pause();
	virtual void unpause();
	virtual void stop();

	virtual void setVolume(float volume = 1.0);

	virtual void mute();

    virtual void seek(qint64 ms);

	virtual void load();
	virtual void unload();

private:
	xine_t *xine;
	xine_stream_t *stream;
	xine_video_port_t *vo_port;
	xine_audio_port_t *ao_port;
	xine_event_queue_t *event_queue;
};

#endif // __XinePlugin_h__
