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

/**
 * @file outputinterface.h The base class defining output engines/plugins
 */

#ifndef __outputinterface_h__
#define __outputinterface_h__

#include <QtCore/QUrl>

#include "PluginInterface.h"

class AudioThread;

class OutputInterface : public PluginInterface
{
	Q_OBJECT

public:
	OutputInterface(QObject *parent = 0, const QStringList& args = QStringList()) : PluginInterface(parent, args), mThread(0) { };
	virtual ~OutputInterface() {};

	virtual float volume() const = 0;
	virtual bool isMuted() { if(volume() == 0.0) return true; return false; };

    virtual bool isPlaying() const = 0;
    virtual bool isPaused() const = 0;

    virtual qint64 totalTime() const = 0;
    virtual qint64 currentTime() const = 0;

	virtual AudioThread* audioThread() { return mThread; };
	virtual void setAudioThread(AudioThread *thread) { mThread = thread; };

	virtual QUrl currentUrl() const { return mCurrentFile; };

	virtual PluginType pluginType() { return OutputPlugin; };

public slots:
	virtual void play(const QUrl& url = QUrl()) = 0;
	virtual void pause() = 0;
	virtual void unpause() = 0;
	virtual void stop() = 0;

	virtual void mute() { setVolume(0.0); };
	virtual void setVolume(float volume = 1.0) = 0;

    virtual void seek(qint64 ms) = 0;

	virtual qint64 maxSamples() const { return -1; };

	virtual void emitSongFinished() { emit finishedSong(mCurrentFile); };

signals:
	void finishedSong(const QUrl& file);

protected:
	QUrl mCurrentFile;
	AudioThread *mThread;
};

Q_DECLARE_INTERFACE(OutputInterface, "com.emotionalcoder.UtopiaPlayer.OutputInterface/0.1")

#endif // __outputinterface_h__
