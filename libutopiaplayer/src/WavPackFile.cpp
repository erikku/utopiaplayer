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

#include "WavPackFile.h"
#include "Application.h"
#include "APEv2.h"

#include <QtCore/QFile>
#include <QtCore/QObject>

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

WavPackFile::WavPackFile(const QString& path) : AudioFile(path), wvContext(0)//, wvPreviousSamples(0)
{
};

WavPackFile::~WavPackFile() { };

void WavPackFile::close()
{
	if(wvContext)
	{
		WavpackCloseFile(wvContext);

		delete[] wvBuffer;
	}
};

bool WavPackFile::load()
{
	close();

	MetaData::Tag *tag = new MetaData::APEv2(d->path);
	tag->read(d->path);
	addTag(tag);

	return true;

	wvContext = WavpackOpenFileInput(d->path.toLocal8Bit().data(), wvError, OPEN_WVC | OPEN_NORMALIZE, 0);
	if(!wvContext)
	{
		uError("WavPackFile", QObject::tr("Error opening file '%1'").arg(d->path));
		return false;
	}

	d->sampleCount = WavpackGetNumSamples(wvContext);
	d->sampleRate = WavpackGetSampleRate(wvContext);
	d->channels = WavpackGetNumChannels(wvContext);
	if(d->channels != 2) { close(); return false; }
	d->bitsPerSample = WavpackGetBitsPerSample(wvContext);
	d->bitrate = 0;
	d->codec = "WavPack";
	d->tool = QObject::tr("WavPack %1").arg(WavpackGetLibraryVersionString());
	d->encoding = "lossless";

	// Pre-allocate our buffers
	wvBuffer = new int32_t[d->channels * 8192]; // Should be a period size, but whatever

	return true;
};

bool WavPackFile::save()
{
};

bool WavPackFile::rewind()
{
	if(!wvContext)
		return false;

	WavpackSeekSample(wvContext, 0);
};

bool WavPackFile::seek(quint32 sample)
{
	if(!wvContext)
		return false;

	WavpackSeekSample(wvContext, sample);
};

int WavPackFile::readSamples(float **samples, int count)
{
	if(!wvContext)
		return 0;

	uint32_t newCount = WavpackUnpackSamples(wvContext, wvBuffer, count);

	float conversion = pow(2, d->bitsPerSample - 1);

	for(int i = 0; i < d->channels; i++)
	{
		for(int j = 0; j < newCount; j++)
		{
			samples[i][j] = (float)wvBuffer[j * d->channels + i] / conversion;
		}
	}

	return newCount;
};

bool WavPackFile::isOpen() const { };

bool WavPackFile::isValid() const
{
	QFile file(d->path);
	if( !file.open(QIODevice::ReadOnly) || file.isSequential() )
		return false;

	//if( MetaData::APEv2::fileContainsAPEv2(d->path, MetaData::APEv2::Header) )
		//file.seek(32);

	char magic[4];

	if( file.read(magic, 4) == 4 )
	{
		if( memcmp(magic, "wvpk", 4) == 0 )
			return true;
	}

	return false;
};

QString WavPackFile::type() const
{
	return "WavPack";
};

QString WavPackFile::mimeType() const
{
	return "audio/x-wavpack";
};

QStringList WavPackFile::extensions() const
{
	return QStringList() << ".wv";
};
