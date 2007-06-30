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

#include "MP3File.h"
#include "ID3v1.h"

#include <QtCore/QFile>
#include <QtCore/QObject>

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

MP3File::MP3File(const QString& path) : AudioFile(path), mOpen(false)
{
};

MP3File::~MP3File() { };

void MP3File::close()
{
};

bool MP3File::load()
{
	MetaData::Tag *tag = new MetaData::ID3v1(d->path);
	tag->read(d->path, "SJIS");
	addTag(tag);
	mOpen = true;
};

bool MP3File::save()
{
};

bool MP3File::rewind()
{
};

bool MP3File::seek(quint32 sample)
{
};

int MP3File::readSamples(float **samples, int count)
{
};

bool MP3File::isOpen() const
{
	return mOpen;
};

bool MP3File::isValid() const
{
	return true;
};

QString MP3File::type() const
{
	return "MPEG 1 Layer 3";
};

QString MP3File::mimeType() const
{
	return "audio/x-mp3";
};

QStringList MP3File::extensions() const
{
	return QStringList() << ".mp3";
};
