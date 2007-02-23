/*************************************************************************\
*  UtopiaDB - A multimedia database application and library with a clean  *
*  API and lots of features, including multiple languages per entry.      *
*                                                                         *
*  Copyright (C) 2006-2007 John Eric Martin <john.eric.martin@gmail.com>  *
*                                                                         *
*  This program is free software; you can redistribute it and/or modify   *
*  it under the terms of the GNU General Public License version 2 as      *
*  published by the Free Software Foundation.                             *
*                                                                         *
*  This program is distributed in the hope that it will be useful,        *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with this program; if not, write to the                          *
*  Free Software Foundation, Inc.,                                        *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
\*************************************************************************/

/**
 * @file songfile.h The SongFile block class definition
 */

#ifndef __SongFile_h__
#define __SongFile_h__

#include <QtCore/QStringList>
#include <QtCore/QList>

#include "utopiablock.h"
#include "tagid.h"

namespace Utopia
{

class SongFileData : public QSharedData
{
public:
	// List of devices to keep this song synced with
	QStringList mSyncDevices;
	QList<TagID> mTagIDs;

	QString mPath;

	int mBitrate;
	int mFreq;

	QString mFormat;
};

// For the song path, we look up the song in a list of files by it's SongFile ID
class SongFile : public UtopiaBlock
{
public:
	SongFile();

	bool operator==(const SongFile& block);
	bool operator!=(const SongFile& block);

	QStringList syncDevices() const;
	bool containsSyncDevice(const QString& device);

	QList<TagID> tagIDs() const;
	bool containsTagID(const TagID& tag);

	QString path() const;

	int bitrate();
	int freq();

	const QString& format();

	virtual QStringList type() const { return QStringList() << "SongFile" << UtopiaBlock::type(); };

	void addSyncDevice(const QString& device);
	void removeSyncDevice(const QString& device);
	void clearSyncDevices();

	void addTagID(const TagID& tagid);
	void removeTagID(const TagID& tagid);
	void clearTagIDs();

	void setPath(const QString& path);

	void setBitrate(int bitrate);
	void setFreq(int freq);

	void setFormat(const QString& format);

	virtual void clear();

	virtual QString xml(bool encased = true) const;

private:
	QSharedDataPointer<SongFileData> d;
};

class SongFileParser : public UtopiaBlockParser
{
public:
	SongFileParser() : UtopiaBlockParser() { };

	virtual bool startDocument();
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __SongFile_h__
