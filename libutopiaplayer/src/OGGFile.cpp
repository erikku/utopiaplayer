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

#include "OGGFile.h"

#include <QtCore/QFile>
#include <QtCore/QObject>

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

OGGFile::OGGFile(const QString& path) : AudioFile(path), mFile(0)
{
};

OGGFile::~OGGFile() { };

void OGGFile::close()
{
	if(!mFile)
		return;

	free(mVorbisInfo);
	ov_clear(&mVorbisFile);
	fclose(mFile);
};

bool OGGFile::load()
{
	close();

	mFile = fopen(d->path.toLocal8Bit().data(), "rb");
	if(!mFile)
	{
		fprintf(stderr, "Couldn't open file '%s'\n", d->path.toLocal8Bit().data());
		return false;
    }

	int result;
    if( (result = ov_open(mFile, &mVorbisFile, NULL, 0)) < 0 )
    {
		fprintf(stderr, "Couldn't process '%s'", d->path.toLocal8Bit().data());
        return false;
    }

	mVorbisInfo = ov_info(&mVorbisFile, -1);

	d->sampleCount = ov_pcm_total(&mVorbisFile, -1);
	d->sampleRate = mVorbisInfo->rate;
	d->channels = mVorbisInfo->channels;
	if(d->channels != 2) { close(); return false; }
	d->bitsPerSample = 16;
	d->bitrate = mVorbisInfo->bitrate_nominal;
	d->codec = "OGG";
	d->tool = QObject::tr("OGG");
	d->encoding = "lossful";

	return true;
};

bool OGGFile::save()
{
};

bool OGGFile::rewind()
{
	if(!mFile)
		return false;

	return !ov_pcm_seek(&mVorbisFile, 0);
};

bool OGGFile::seek(quint32 sample)
{
	if(!mFile)
		return false;

	return !ov_pcm_seek(&mVorbisFile, sample);
};

int OGGFile::readSamples(float **samples, int count)
{
	if(!mFile)
		return 0;

	int currentSection;
	float **buffer;

	int new_count = ov_read_float(&mVorbisFile, &buffer, count, &currentSection);

	// Copy the data into the buffer
	for(int i = 0; i < d->channels; i++)
	{
		memcpy(samples[i], buffer[i], sizeof(float)*new_count);
	}

	return new_count;
};

bool OGGFile::isOpen() const { return mFile; };

bool OGGFile::isValid() const
{
	QFile file(d->path);
	if( !file.open(QIODevice::ReadOnly) || file.isSequential() )
		return false;

	char magic[4];

	if( file.read(magic, 4) == 4 )
	{
		if( memcmp(magic, "OggS", 4) == 0 )
			return true;
	}

	return false;
};

QString OGGFile::type() const
{
	return "OGG Vorbis";
};

QString OGGFile::mimeType() const
{
	return "application/ogg";
};

QStringList OGGFile::extensions() const
{
	return QStringList() << ".ogg";
};
