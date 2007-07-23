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

#ifndef __AlsaInterface_h__
#define __AlsaInterface_h__

#include "PluginInterface.h"
#include "OutputInterface.h"

#include <alsa/asoundlib.h>

class AudioFile;

class ALSAInterface : public OutputInterface
{
	Q_OBJECT

public:
	ALSAInterface(QObject *parent = 0);
	virtual ~ALSAInterface();

	virtual float volume() const { return mVolume; };
	//virtual bool isMuted() { if(volume() == 0.0) return true; return false; };

    virtual qint64 totalTime() const { return 10; };
    virtual qint64 currentTime() const { return 5; };

	virtual QString name() const { return "ALSA"; };

	//virtual QUrl currentUrl() const { return mCurrentFile; };

	virtual bool isPlaying() const { return true; };
	virtual bool isPaused() const { return false; };

	virtual bool hasAudio() const { return true; };
	virtual QStringList audioFormats() const { return QStringList() << "WavePack"; };

	virtual bool hasVideo() const { return false; };
	virtual QStringList videoFormats() const { return QStringList(); };
	void buffer();

public slots:
	//virtual void mute() { setVolume(0.0); };
	virtual void setVolume(float volume = 1.0) { mVolume = volume; };

	virtual void play(const QUrl& url = QUrl());
	virtual void pause() { };
	virtual void unpause() { };
	virtual void stop() { };
    virtual void seek(qint64 ms) { Q_UNUSED(ms); };

protected:
	void fill();

	AudioFile *mAudioFile;

	int mPeriodCount;
	int mEmptyPeriods;
	int mCurrentPeriod;

	int *mPeriodSizes;
	float ***mSampleBuffer;

	float mVolume;
	unsigned int mRate;
	snd_pcm_t *mPlaybackHandle;
	snd_pcm_uframes_t mPeriodSize;
	snd_pcm_uframes_t mBufferSize;
	snd_async_handler_t *mCallback;
};

class ALSAPlugin : public QObject, public PluginInterface
{
	Q_OBJECT
	Q_INTERFACES(PluginInterface)

public:
	ALSAPlugin();
	virtual ~ALSAPlugin();

	virtual QString name() const;
	virtual QString version() const;
	virtual QStringList authors() const;
	virtual QString copyrightNotice() const;
	
	virtual void load();
	virtual void unload();
	virtual bool isLoaded();

private:
	bool mLoaded;

	ALSAInterface *mInterface;
};

#endif // __AlsaInterface_h__
