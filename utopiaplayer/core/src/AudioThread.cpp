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

#include "AudioThread.h"

#include "AudioFile.h"
#include "OutputInterface.h"

#include "OGGFile.h"
#include "WavPackFile.h"

#include <QtCore/QTimer>

AudioThread::AudioThread()
{
	//AudioFile *file = new WavPackFile("/home/erikku/Bokura ga Ikiru MY ASIA/track01.cdda.wv");
	//AudioFile *file = new OGGFile("/home/eric/src/example.ogg");
	//file->load();
	//mFiles << file;
};

AudioThread::~AudioThread()
{
	mFiles.head()->close();
	delete mFiles.head();
};

void AudioThread::enqueueFile(const QUrl& url)
{
	mMutex.lock();

	mMutex.unlock();
};

// Takes a reference to the buffer pointer and set's it to the new data
int AudioThread::samples(float** buffer, int count)
{
	return mFiles.head()->readSamples(buffer, count);
};

void AudioThread::run()
{
	exec();
};
