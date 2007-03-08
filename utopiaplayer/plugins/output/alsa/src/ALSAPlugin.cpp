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

#include "AudioThread.h"
#include "WavPackFile.h"
#include "OGGFile.h"

#include <stdio.h>
#include <stdlib.h>

Q_EXPORT_PLUGIN2(alsaplugin, ALSAPlugin)

void AlsaSndCallback(snd_async_handler_t *callback)
{
	( (ALSAPlugin*)snd_async_handler_get_callback_private(callback) )->buffer();
};

void ALSAPlugin::buffer()
{
	snd_pcm_sframes_t avail = snd_pcm_avail_update(mPlaybackHandle);
	int err;

	if(avail == -EPIPE)
	{
		fprintf(stderr, "An xrun occurred!!!\n");
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

void ALSAPlugin::fill()
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

void ALSAPlugin::load()
{
	if(!mThread)
		return;

	fprintf(stderr, "Loading the ALSA plugin\n");

	unsigned int err, periods = 16;
	snd_pcm_hw_params_t *hwparams;

	mRate = 44100;
	mPeriodSize = 8192;

    snd_pcm_hw_params_alloca(&hwparams);

	if( (err = snd_pcm_open(&mPlaybackHandle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0 )
	{
		fprintf(stderr, "Error opening PCM device %s (%s)\n", "default", snd_strerror(err));
		return;
	}

    if( (err = snd_pcm_hw_params_any(mPlaybackHandle, hwparams)) < 0 )
	{
		fprintf(stderr, "Can not configure this PCM device. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_hw_params_set_access(mPlaybackHandle, hwparams, SND_PCM_ACCESS_RW_NONINTERLEAVED)) < 0 )
	{
		fprintf(stderr, "Error setting access. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_hw_params_set_format(mPlaybackHandle, hwparams, SND_PCM_FORMAT_FLOAT_LE)) < 0 )
	{
		fprintf(stderr, "Error setting format. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_hw_params_set_rate_near(mPlaybackHandle, hwparams, &mRate, 0)) < 0 )
	{
		fprintf(stderr, "Error setting mRate. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_hw_params_set_channels(mPlaybackHandle, hwparams, 2)) < 0 )
	{
		fprintf(stderr, "Error setting channels. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_hw_params_set_period_size_near(mPlaybackHandle, hwparams, &mPeriodSize, 0)) < 0 )
	{
		fprintf(stderr, "Error setting period size. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_hw_params_set_periods_near(mPlaybackHandle, hwparams, &periods, 0)) < 0 )
	{
		fprintf(stderr, "Error setting periods. (%s)\n", snd_strerror(err));
		return;
	}

	mBufferSize = (mPeriodSize * periods) >> 2;

	if( (err = snd_pcm_hw_params_set_buffer_size_near(mPlaybackHandle, hwparams, &mBufferSize)) < 0 )
	{
		fprintf(stderr, "Error setting mBufferSize. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_hw_params(mPlaybackHandle, hwparams)) < 0 )
	{
		fprintf(stderr, "Error setting HW params. (%s)\n", snd_strerror(err));
		return;
	}

	//snd_pcm_hw_params_free(hwparams);

	snd_pcm_sw_params_t *swparams;

	snd_pcm_sw_params_malloc(&swparams);

	if( (err = snd_pcm_sw_params_current(mPlaybackHandle, swparams)) < 0 )
	{
		fprintf(stderr, "Can not get software params. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_sw_params_set_start_threshold(mPlaybackHandle, swparams, mBufferSize - mPeriodSize)) < 0 )
	{
		fprintf(stderr, "Can not set callback threshold. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_sw_params_set_avail_min(mPlaybackHandle, swparams, mPeriodSize)) < 0 )
	{
		fprintf(stderr, "Can not set callback minimum. (%s)\n", snd_strerror(err));
		return;
	}

	if( (err = snd_pcm_sw_params(mPlaybackHandle, swparams)) < 0 )
	{
		fprintf(stderr, "Error setting SW params. (%s)\n", snd_strerror(err));
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
	mAudioFile = new OGGFile( "/home/erikku/Bokura ga Ikiru MY ASIA/track01.cdda.ogg" );
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
		fprintf(stderr, "Error creating callback. (%s)\n", snd_strerror(err));
		return;
	}

	// Start the device
	snd_pcm_start(mPlaybackHandle);

	OutputInterface::load();
};

void ALSAPlugin::unload()
{
	fprintf(stderr, "Unloading the ALSA plugin\n");

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

	OutputInterface::unload();
};

void ALSAPlugin::play(const QUrl& url)
{
	mCurrentFile = url;
};
