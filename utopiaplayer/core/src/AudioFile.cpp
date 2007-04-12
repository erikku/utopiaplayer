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

#include "AudioFile.h"
#include "Tag.h"

#include <QtCore/QFileInfo>

AudioFile::AudioFile(const QString& path)
{
	d = new AudioFileData;
	d->path = path;
};

AudioFile::~AudioFile()
{
};

QList<MetaData::Tag*> AudioFile::tags() const
{
	return d->tags;
};

void AudioFile::addTag(MetaData::Tag *tag)
{
	d->tags << tag;
};

void AudioFile::removeTag(MetaData::Tag *tag)
{
	delete d->tags.takeAt(d->tags.indexOf(tag));
};

QString AudioFile::name() const
{
	return QFileInfo(d->path).fileName();
};

quint64 AudioFile::size() const
{
	return QFileInfo(d->path).size();
};

QString AudioFile::path() const
{
	return d->path;
};

QDateTime AudioFile::created() const
{
	return QFileInfo(d->path).created();
};

QDateTime AudioFile::modified() const
{
	return QFileInfo(d->path).lastModified();
};

quint32 AudioFile::length() const
{
	return d->sampleCount / d->sampleRate;
};

quint32 AudioFile::sampleCount() const
{
	return d->sampleCount;
};

quint32 AudioFile::sampleRate() const
{
	return d->sampleRate;
};

quint8  AudioFile::channels() const
{
	return d->channels;
};

quint8  AudioFile::bitsPerSample() const
{
	return d->bitsPerSample;
};;

quint32 AudioFile::bitrate() const
{
	return d->bitrate;
};

QString AudioFile::codec() const
{
	return d->codec;
};

QString AudioFile::tool() const
{
	return d->tool;
};

QString AudioFile::encoding() const
{
	return d->encoding;
};

bool AudioFile::isReadable() const
{
	return QFileInfo(d->path).isReadable();
};

bool AudioFile::isWritable() const
{
	return QFileInfo(d->path).isWritable();
};

/*int AudioFile::readSamples(float **samples, int count)
{

	// Fill the channel with zero values
	for(int i = 0; i < count; i++)
	{
		samples[i][0] = 0.0f;
		samples[i][1] = 0.0f;
	}

	// Return how many frame/samples we created
	return count;
};*/
