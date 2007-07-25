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

#include "ALSAPlugin.h"

#include "Application.h"
#include "PluginManager.h"

//#include "AudioThread.h"
#include "WavPackFile.h"
#include "OGGFile.h"

//#include <stdio.h>
//#include <stdlib.h>

ALSAPlugin::ALSAPlugin()
{
	mLoaded = false;
	mInterface = 0;
};

ALSAPlugin::~ALSAPlugin()
{
	unload();
};

QString ALSAPlugin::name() const
{
	return "ALSA";
};

QString ALSAPlugin::version() const
{
	return "0.1.0";
};

QStringList ALSAPlugin::authors() const
{
	return QStringList() << "John Eric Martin <john.eric.martin@gmail.com>";
};

QString ALSAPlugin::copyrightNotice() const
{
	return "Copyright (C) 2007 John Eric Martin";
};
	
void ALSAPlugin::load()
{
	//if(mLoaded)
		return;

	mInterface = new ALSAInterface;

	// uApp->pluginManager()->addOutputPlugin(mInterface);
	mLoaded = true;
};

void ALSAPlugin::unload()
{
	if(!mLoaded)
		return;

	delete mInterface;
};

bool ALSAPlugin::isLoaded()
{
	return mLoaded;
};

Q_EXPORT_PLUGIN2(alsaplugin, ALSAPlugin)

void AlsaSndCallback(snd_async_handler_t *callback)
{
	( (ALSAInterface*)snd_async_handler_get_callback_private(callback) )->buffer();
};

void ALSAInterface::buffer()
{
	snd_pcm_sframes_t avail = snd_pcm_avail_update(mPlaybackHandle);
	int err;

	if(avail == -EPIPE)
	{
		uError("ALSAInterface", tr("An xrun occurred!!!"));
		snd_pcm_prepare(mPlaybackHandle);
		return;
	}

	if(mEmptyPeriods >= mPeriodCount) fill();

	while(avail >= mPeriodSizes[mCurrentPeriod] && avail > 0)
	{
		snd_pcm_writen(mPlaybackHandle, (void**)mSampleBuffer[mCurrentPeriod], mPeriodSizes[mCurrentPeriod]);

		// Increment the current period
		mCurrentPeriod++; if(mCurrentPeriod >= mPeriodCount) mCurrentPeriod = 0;
		mEmptyPeriods++;

		if(mEmptyPeriods >= mPeriodCount) fill();

		avail = snd_pcm_avail_update(mPlaybackHandle);
	}
};

void ALSAInterface::fill()
{
	int currentPeriod = mCurrentPeriod - mEmptyPeriods + mPeriodCount;

	// Fill all our empty periods
	for(int i = 0; i < mEmptyPeriods; i++)
	{
		// Fill the period
		mPeriodSizes[currentPeriod] = mAudioFile->readSamples(mSampleBuffer[currentPeriod], mPeriodSize);

		// Increment to the next period to fill
		currentPeriod++; if(currentPeriod >= mPeriodCount) currentPeriod = 0;
	}

	mEmptyPeriods = 0;
};

ALSAInterface::ALSAInterface(QObject *parent) : OutputInterface(parent)
{
	//if(!mThread)
		//return;

	uInfo("ALSAInterface", tr("Loading the ALSA plugin"));

	unsigned int err, periods = 16;
	snd_pcm_hw_params_t *hwparams;

	mRate = 44100;
	mPeriodSize = 8192;

    snd_pcm_hw_params_alloca(&hwparams);

	if( (err = snd_pcm_open(&mPlaybackHandle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0 )
	{
		uError("ALSAInterface", tr("Error opening PCM device %1 (%2)").arg("default").arg(snd_strerror(err)));;
		return;
	}

    if( (err = snd_pcm_hw_params_any(mPlaybackHandle, hwparams)) < 0 )
	{
		uError("ALSAInterface", tr("Can not configure this PCM device. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_hw_params_set_access(mPlaybackHandle, hwparams, SND_PCM_ACCESS_RW_NONINTERLEAVED)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting access. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_hw_params_set_format(mPlaybackHandle, hwparams, SND_PCM_FORMAT_FLOAT_LE)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting format. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_hw_params_set_rate_near(mPlaybackHandle, hwparams, &mRate, 0)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting rate. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_hw_params_set_channels(mPlaybackHandle, hwparams, 2)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting channels. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_hw_params_set_period_size_near(mPlaybackHandle, hwparams, &mPeriodSize, 0)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting period size. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_hw_params_set_periods_near(mPlaybackHandle, hwparams, &periods, 0)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting periods. (%1)").arg(snd_strerror(err)));
		return;
	}

	mBufferSize = (mPeriodSize * periods) >> 2;

	if( (err = snd_pcm_hw_params_set_buffer_size_near(mPlaybackHandle, hwparams, &mBufferSize)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting buffer size. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_hw_params(mPlaybackHandle, hwparams)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting HW params. (%1)").arg(snd_strerror(err)));
		return;
	}

	//snd_pcm_hw_params_free(hwparams);

	snd_pcm_sw_params_t *swparams;

	snd_pcm_sw_params_malloc(&swparams);

	if( (err = snd_pcm_sw_params_current(mPlaybackHandle, swparams)) < 0 )
	{
		uError("ALSAInterface", tr("Can not get software params. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_sw_params_set_start_threshold(mPlaybackHandle, swparams, mBufferSize - mPeriodSize)) < 0 )
	{
		uError("ALSAInterface", tr("Can not set callback threshold. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_sw_params_set_avail_min(mPlaybackHandle, swparams, mPeriodSize)) < 0 )
	{
		uError("ALSAInterface", tr("Can not set callback minimum. (%1)").arg(snd_strerror(err)));
		return;
	}

	if( (err = snd_pcm_sw_params(mPlaybackHandle, swparams)) < 0 )
	{
		uError("ALSAInterface", tr("Error setting SW params. (%1)").arg(snd_strerror(err)));
		return;
	}

	snd_pcm_sw_params_free(swparams);

	// Prepare the device
	snd_pcm_prepare(mPlaybackHandle);

	//////////////////////////////////////////////////////////////////////////////////////////
	// We need to allocate the buffers, fill them, and write mPeriodSize * 2 to the device //
	////////////////////////////////////////////////////////////////////////////////////////
	mPeriodCount = 16; // The buffer will hold up to 16 periods worth of data
	mCurrentPeriod = 0;
	mEmptyPeriods = mPeriodCount;
	mPeriodSizes = new int[mPeriodCount];
	mSampleBuffer = new float**[mPeriodCount];
	for(int i = 0; i < mPeriodCount; i++)
	{
		mSampleBuffer[i] = new float*[2]; // A period
		mSampleBuffer[i][0] = new float[mPeriodSize]; // Left
		mSampleBuffer[i][1] = new float[mPeriodSize]; // Right
	}

	//mAudioFile = new WavPackFile( "/home/erikku/Bokura ga Ikiru MY ASIA/track01.cdda.wv" );
	mAudioFile = new OGGFile( QString::fromUtf8("/media/utopia/Lossless/OGG/愛の第6感.ogg") );
	mAudioFile->load();

	// Fill the audio devive with two periods
	int frames;
	frames = mAudioFile->readSamples(mSampleBuffer[0], mPeriodSize);
	snd_pcm_writen(mPlaybackHandle, (void**)mSampleBuffer[0], frames);
	frames = mAudioFile->readSamples(mSampleBuffer[0], mPeriodSize);
	snd_pcm_writen(mPlaybackHandle, (void**)mSampleBuffer[0], frames);

	fill();

	if( (err = snd_async_add_pcm_handler(&mCallback, mPlaybackHandle, AlsaSndCallback, this)) < 0)
	{
		uError("ALSAInterface", tr("Error creating callback. (%1)").arg(snd_strerror(err)));
		return;
	}

	// Start the device
	snd_pcm_start(mPlaybackHandle);
};

ALSAInterface::~ALSAInterface()
{
	uInfo("ALSAInterface", tr("Unloading the ALSA plugin"));

	snd_pcm_close(mPlaybackHandle);

	// Free our soft buffer
	for(int i = 0; i < mPeriodCount; i++)
	{
		delete[] mSampleBuffer[i][0];
		delete[] mSampleBuffer[i][1];
		delete[] mSampleBuffer[i];
	}
	delete[] mSampleBuffer;
	delete[] mPeriodSizes;

	mSampleBuffer = 0;
};

void ALSAInterface::play(const QUrl& url)
{
	mCurrentFile = url;
};
