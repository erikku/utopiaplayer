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

#ifndef __AudioFile_h__
#define __AudioFile_h__

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QStringList>
#include <QtCore/QSharedData>
#include <QtCore/QSharedDataPointer>

class Tag { };

class AudioFileData : public QSharedData
{
public:
	quint32 sampleCount;
	quint32 sampleRate;
	quint8  channels;
	quint8  bitsPerSample;
	quint32 bitrate;
	QString codec;
	QString tool;
	QString encoding;

	QString path;

	QList<Tag*> tags;
};

class AudioFile
{
public:
	AudioFile(const QString& path);
	virtual ~AudioFile();

	QList<Tag*> tags() const;

	void addTag(Tag *tag);
	void removeTag(Tag *tag);

	virtual void close() = 0;
	virtual bool load() = 0;
	virtual bool save() = 0;

	virtual bool rewind() = 0;
	virtual bool seek(quint32 sample) = 0;
	virtual int readSamples(float **samples, int count) = 0;

	virtual QString name() const;
	virtual quint64 size() const;
	virtual QString path() const;
	virtual QDateTime created() const;
	virtual QDateTime modified() const;

	virtual quint32 length() const; // In seconds
	virtual quint32 sampleCount() const;
	virtual quint32 sampleRate() const;
	virtual quint8  channels() const;
	virtual quint8  bitsPerSample() const;
	virtual quint32 bitrate() const;

	virtual QString codec() const;
	virtual QString tool() const;
	virtual QString encoding() const;

	virtual bool isOpen() const = 0;
	virtual bool isValid() const = 0;

	virtual bool isReadable() const;
	virtual bool isWritable() const;

	virtual QString type() const = 0;
	virtual QString mimeType() const = 0;
	virtual QStringList extensions() const = 0;

protected:
	QSharedDataPointer<AudioFileData> d;
};

#endif // __AudioFile_h__
