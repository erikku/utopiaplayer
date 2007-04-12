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

#include "APEv2.h"

#include <QtCore/QFile>

namespace MetaData
{

APEv2::APEv2(QObject *parent) : AdvancedTag(parent)
{
	// Code here
};

QFlags<AdvancedTag::TagFeatures> APEv2::features()
{
	QFlags<AdvancedTag::TagFeatures> theFeatures;
	theFeatures |= AdvancedTag::Disc | AdvancedTag::TotalDiscs | AdvancedTag::TotalTracks
			| AdvancedTag::Composer | AdvancedTag::Performer | AdvancedTag::AlbumArtist
			| AdvancedTag::Date | AdvancedTag::ReplayGain | AdvancedTag::EmbeddedCoverArt
			| AdvancedTag::CustomTags | AdvancedTag::MultipleEntries;

	return theFeatures;
};

QStringList APEv2::titles() const
{
	return stringListFromVariantList( tag(QLatin1String("TITLE")) );
};

void APEv2::setTitles(const QStringList& titles)
{
	setTag(QLatin1String("TITLE"), titles);
};

QStringList APEv2::artists() const
{
	return stringListFromVariantList( tag(QLatin1String("ARTIST")) );
};

void APEv2::setArtists(const QStringList& artists)
{
	setTag(QLatin1String("ARTIST"), artists);
};

QStringList APEv2::albums() const
{
	return stringListFromVariantList( tag(QLatin1String("ALBUM")) );
};

void APEv2::setAlbums(const QStringList& albums)
{
	setTag(QLatin1String("ALBUM"), albums);
};

QStringList APEv2::comments() const
{
	return stringListFromVariantList( tag(QLatin1String("COMMENT")) );
};

void APEv2::setComments(const QStringList& comments)
{
	setTag(QLatin1String("COMMENT"), comments);
};

QStringList APEv2::genres() const
{
	return stringListFromVariantList( tag(QLatin1String("GENRE")) );
};

void APEv2::setGenres(const QStringList& genres)
{
	setTag(QLatin1String("GENRE"), genres);
};

int APEv2::year() const
{
	QString theYear = stringFromVariant( tag(QLatin1String("YEAR"), 0) );
	if( theYear.contains(QLatin1Char('-')) )
		return theYear.split(QLatin1Char('-')).first().toInt();

	return theYear.toInt();
};

void APEv2::setYear(int year)
{
	//
};

int APEv2::track() const
{
	QString theTrack = stringFromVariant( tag(QLatin1String("TRACK"), 0) );
	if( theTrack.contains(QLatin1Char('/')) )
		return theTrack.split(QLatin1Char('/')).first().toInt();

	return theTrack.toInt();
};

void APEv2::setTrack(int track)
{
	QString theTrack = stringFromVariant( tag(QLatin1String("TRACK"), 0) );
	if( theTrack.contains(QLatin1Char('/')) )
		theTrack = QString::number(track) + QLatin1Char('/') + theTrack.split(QLatin1Char('/')).at(1);
	else
		theTrack = QString::number(track);

	setTag(QLatin1String("TRACK"), theTrack);
};

QList<QVariant> APEv2::tag(const QString& key) const
{
	if(mTags.contains(key))
		return mTags.value(key).second; // "ALBUMARTIST"

	return QList<QVariant>();
};

QVariant APEv2::tag(const QString& key, int index) const
{
	if(mTags.contains(key))
	{
		QList<QVariant> items = mTags.value(key).second;
		if(items.count() > index)
			return items.at(index);
	}

	return QVariant();
};

void APEv2::setTag(const QString& key, const QString& tag)
{
	TagData data;
	data << tag.toUtf8();

	TagPair pair;
	pair.first = AdvancedTag::String;
	pair.second = data;

	mTags[key] = pair;
};

void APEv2::setTag(const QString& key, const QStringList& tag)
{
	TagData data;
	foreach(QString entry, tag)
		data << entry.toUtf8();

	TagPair pair;
	pair.first = AdvancedTag::String;
	pair.second = data;

	mTags[key] = pair;
};

QString APEv2::stringFromVariant(const QVariant& data) const
{
	return QString::fromUtf8(data.toByteArray().data());
};

QStringList APEv2::stringListFromVariantList(const QList<QVariant>& data) const
{
	QStringList final;

	foreach(QVariant entry, data)
		final << QString::fromUtf8( entry.toByteArray().data() );

	return final;
};

void APEv2::clear()
{
	mTags.clear();
};

bool APEv2::isEmpty()
{
	return mTags.count();
};

/*
typedef struct
{
	char magic[8]; // 'APETAGEX'
	float version; // 1.000 or 2.000
	quint32 tagSize; // Including the footer (if this is the header) and all tag items (excluding this header)
	quint32 itemCount;
	quint32 flags;
	char reserved[8]; // Must be zero
}APEv2Header;
*/
}; // namespace MetaData
/*
using namespace MetaData;

QString APEv2::tagType() const
{
	return "APEv2";
};

bool APEv2::fileContainsAPEv2(const QString& file, APEv2Position pos)
{
	APEv2Header header;

	QFile handle(file);
	if( !handle.open(QIODevice::ReadOnly) || handle.isSequential() || handle.size() < sizeof(APEv2Header) )
		return false;

	if(pos == Header || pos == Both)
	{
		handle.seek(0);

		if( handle.read((char*)&header, sizeof(APEv2Header)) == sizeof(APEv2Header) )
		{
			if( memcmp(header.magic, "APETAGEX", 8) == 0 )
				return true;
		}
	}

	if(pos == Footer || pos == Both)
	{
		handle.seek( handle.size() - sizeof(APEv2Header) );

		if( handle.read((char*)&header, sizeof(APEv2Header)) == sizeof(APEv2Header) )
		{
			if( memcmp(header.magic, "APETAGEX", 8) == 0 )
				return true;
		}
	}

	return false;
};
*/
