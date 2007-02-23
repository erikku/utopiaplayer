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

#ifndef __ALSAPlugin_h__
#define __ALSAPlugin_h__

#include "OutputInterface.h"

#include <alsa/asoundlib.h>

class AudioFile;

class ALSAPlugin : public OutputInterface
{
	Q_OBJECT
	Q_INTERFACES(OutputInterface)

public:
	ALSAPlugin(QObject *parent = 0, const QStringList &args = QStringList()) : OutputInterface(parent, args), mVolume(1.0f) { };
	virtual ~ALSAPlugin() { };

	virtual float volume() const { return mVolume; };

    virtual bool isPlaying() const { return false; };
    virtual bool isPaused() const { return false; };

    virtual qint64 totalTime() const { return 0; };
    virtual qint64 currentTime() const { return 0; };

	virtual void load();
	virtual void unload();

	QString pluginName() const { return tr("ALSA"); };

	void buffer(); // Send data to the sound card
	void fill(); // Fill the buffer to 100%

public slots:
	virtual void play(const QUrl& url = QUrl());
	virtual void pause() { };
	virtual void unpause() { };
	virtual void stop() { };

	virtual void setVolume(float volume = 1.0) { mVolume = volume; };

    virtual void seek(qint64 ms) { Q_UNUSED(ms) };
    virtual void seekPosition(qint64 position) { Q_UNUSED(position) };

	virtual qint64 maxSamples() const { return 8192; };

protected:
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

#endif // __ALSAPlugin_h__
