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
	NullOutput(QObject *parent = 0) : OutputInterface(parent), mVolume(1.0f) { };

	virtual float volume() const { return mVolume; };

    virtual bool isPlaying() const { return false; };
    virtual bool isPaused() const { return false; };

    virtual qint64 totalTime() const { return 0; };
    virtual qint64 currentTime() const { return 0; };

	QString name() const { return tr("Null"); }; 

	virtual void play(const QUrl& url = QUrl()) { Q_UNUSED(url) };
	virtual void pause() { };
	virtual void unpause() { };
	virtual void stop() { };

	virtual void setVolume(float volume = 1.0) { mVolume = volume; };

    virtual void seek(qint64 ms) { Q_UNUSED(ms) };
    virtual void seekPosition(qint64 position) { Q_UNUSED(position) };

	virtual bool hasAudio() const { return true; };
	virtual QStringList audioFormats() const { return QStringList() << "*.mp3" << "*.ogg" << "*.wv"; };

	virtual bool hasVideo() const { return true; };
	virtual QStringList videoFormats() const { return QStringList() << "*.avi"; };

protected:
	float mVolume;
};

#endif // __nulloutput_h__
