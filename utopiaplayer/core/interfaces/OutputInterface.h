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
 * @file OutputInterface.h The base class defining output engines/plugins
 */

#ifndef __OutputInterface_h__
#define __OutputInterface_h__

#include <QtCore/QUrl>

class OutputInterface
{
public:
	virtual ~OutputInterface() { };

	virtual float volume() const = 0;
	virtual void mute() { setVolume(0.0); };
	virtual void setVolume(float volume = 1.0) = 0;
	virtual bool isMuted() { if(volume() == 0.0) return true; return false; };

    virtual qint64 totalTime() const = 0;
    virtual qint64 currentTime() const = 0;

	virtual QUrl currentUrl() const { return mCurrentFile; };

	virtual void play(const QUrl& url = QUrl()) = 0;
	virtual bool isPlaying() const = 0;

	virtual void pause() = 0;
	virtual void unpause() = 0;
	virtual bool isPaused() const = 0;
	
	virtual void stop() = 0;
    virtual void seek(qint64 ms) = 0;

protected:
	QUrl mCurrentFile;
};

Q_DECLARE_INTERFACE(OutputInterface, "com.emotionalcoder.UtopiaPlayer.OutputInterface/0.1")

#endif // __OutputInterface_h__
