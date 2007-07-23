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

#ifndef __nulloutput_h__
#define __nulloutput_h__

#include "PluginInterface.h"
#include "OutputInterface.h"

class NullOutput : public OutputInterface
{
	Q_OBJECT

public:
	NullOutput(QObject *parent = 0) : OutputInterface(parent), mVolume(1.0f), mPaused(false), mPlaying(false) { };
	virtual ~NullOutput() { };

	virtual float volume() const { return mVolume; };

    virtual qint64 totalTime() const { return 10; };
    virtual qint64 currentTime() const { return 0; };

	virtual QString name() const { return "Null"; };

	virtual QUrl currentUrl() const { return QUrl(); };

	virtual bool isPlaying() const { return mPlaying; };
	virtual bool isPaused() const { return mPaused; };

	virtual bool hasAudio() const { return false; };
	virtual QStringList audioFormats() const { return QStringList(); };

	virtual bool hasVideo() const { return false; };
	virtual QStringList videoFormats() const { return QStringList(); };

public slots:
	virtual void setVolume(float volume = 1.0) { mVolume = volume; };

	virtual void play(const QUrl& url = QUrl()) { Q_UNUSED(url); mPlaying = true; mPaused = false; };
	virtual void pause() { mPaused = true; };
	virtual void unpause() { mPaused = false; };
	virtual void stop() { mPlaying = false; mPaused = false; };
    virtual void seek(qint64 ms) { Q_UNUSED(ms); };

protected:
	bool mPaused;
	bool mPlaying;
	float mVolume;
};

#endif // __nulloutput_h__
