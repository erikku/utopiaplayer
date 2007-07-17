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
 * @file songfile.cpp The SongFile block class implementation
 */

#include "songfile.h"

using namespace Utopia;

SongFile::SongFile() : UtopiaBlock()
{
	d = new SongFileData;
	clear();
};

bool SongFile::operator==(const SongFile& block)
{
	if(d->mSyncDevices != block.d->mSyncDevices || d->mTagIDs != block.d->mTagIDs || d->mPath != block.d->mPath ||
	d->mBitrate != block.d->mBitrate || d->mFreq != block.d->mFreq || d->mFormat != block.d->mFormat)
		return false;

	return UtopiaBlock::operator==(block);
};

bool SongFile::operator!=(const SongFile& block)
{
	return !( SongFile::operator==(block) );
};

QStringList SongFile::syncDevices() const
{
	return d->mSyncDevices;
};

bool SongFile::containsSyncDevice(const QString& device)
{
	return d->mSyncDevices.contains(device);
};

QList<TagID> SongFile::tagIDs() const
{
	return d->mTagIDs;
};

bool SongFile::containsTagID(const TagID& tag)
{
	return d->mTagIDs.contains(tag);
};

QString SongFile::path() const
{
	return d->mPath;
};

int SongFile::bitrate()
{
	return d->mBitrate;
};

int SongFile::freq()
{
	return d->mFreq;
};

const QString& SongFile::format()
{
	return d->mFormat;
};

void SongFile::addSyncDevice(const QString& device)
{
	if( d->mSyncDevices.contains(device) )
		return;

	d->mSyncDevices << device;
};

void SongFile::removeSyncDevice(const QString& device)
{
	int index = d->mSyncDevices.indexOf(device);
	if( index == -1 )
		return;

	d->mSyncDevices.removeAt(index);
};

void SongFile::clearSyncDevices()
{
	d->mSyncDevices.clear();
};

void SongFile::addTagID(const TagID& tagid)
{
	if( d->mTagIDs.contains(tagid) )
		return;

	d->mTagIDs << tagid;
};

void SongFile::removeTagID(const TagID& tagid)
{
	int index = d->mTagIDs.indexOf(tagid);
	if( index == -1 )
		return;

	d->mTagIDs.removeAt(index);
};

void SongFile::clearTagIDs()
{
	d->mTagIDs.clear();
};

void SongFile::setPath(const QString& path)
{
	d->mPath = path;
};

void SongFile::setBitrate(int bitrate)
{
	d->mBitrate = bitrate;
};

void SongFile::setFreq(int freq)
{
	d->mFreq = freq;
};

void SongFile::setFormat(const QString& format)
{
	d->mFormat = format;
};

void SongFile::clear()
{
	d->mSyncDevices.clear();
	d->mTagIDs.clear();
	d->mPath = QString();
	d->mBitrate = 0;
	d->mFreq = 0;
	d->mFormat = "Unknown";

	UtopiaBlock::clear();
};

QString SongFile::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<songfile>\n";

	string += UtopiaBlock::xml(false);

	if(d->mSyncDevices.count())
	{
		string += "  <syncdevices>\n";
		for(int i = 0; i < d->mSyncDevices.count(); i++)
		{
			string += "    <device>" + xmlSafe(d->mSyncDevices.at(i)) + "</device>\n";
		}
		string += "  </syncdevices>\n";
	}

	if(d->mTagIDs.count())
	{
		string += "  <tagids>\n";
		for(int i = 0; i < d->mTagIDs.count(); i++)
		{
			string += d->mTagIDs.at(i).xml();
		}
		string += "  </tagids>\n";
	}

	if(d->mBitrate)
		string += "  <bitrate>" + QString::number(d->mBitrate) + "</bitrate>\n";
	if(d->mFreq)
		string += "  <freq>" + QString::number(d->mFreq) + "</freq>\n";
	if(d->mFormat != "Unknown")
	{
		string += "  <format>" + d->mFormat + "</format>\n";
	}
	if(!d->mPath.isEmpty())
	{
		string += "  <path>" + xmlSafe(d->mPath) + "</path>\n";
	}

	if(encased)
		string += "</songfile>\n";

	return string;
};

bool SongFileParser::startDocument()
{
	delete mBlock;
	mBlock = new SongFile;

	return true;
};

bool SongFileParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
	UtopiaBlockParser::startElement(namespaceURI, localName, qName, atts);

	if(localName == "tagid")
	{
		TagID id;
		id.setSystemID(atts.value("systemid").trimmed());
		id.setSongID(atts.value("songid").trimmed());
		((SongFile*)mBlock)->addTagID(id);
	}

	return true;
};

bool SongFileParser::characters(const QString& ch)
{
	if(mElements.top() == "device")
	{
		if( mElements.at(mElements.count() - 2) == "syncdevices" )
		{
			((SongFile*)mBlock)->addSyncDevice(ch.trimmed());
			return true;
		}
	}
	if(mElements.top() == "syncdevices")
		return true;

	if(mElements.top() == "tagids")
		return true;

	if(mElements.top() == "bitrate")
	{
		((SongFile*)mBlock)->setBitrate(ch.trimmed().toInt());
		return true;
	}
	if(mElements.top() == "freq")
	{
		((SongFile*)mBlock)->setFreq(ch.trimmed().toInt());
		return true;
	}
	if(mElements.top() == "format")
	{
		((SongFile*)mBlock)->setFormat(ch.trimmed());
		return true;
	}
	if(mElements.top() == "path")
	{
		((SongFile*)mBlock)->setPath(ch.trimmed());
		return true;
	}

	return UtopiaBlockParser::characters(ch);
};
