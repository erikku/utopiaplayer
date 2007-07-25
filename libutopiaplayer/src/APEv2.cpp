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
#include "Cuesheet.h"
#include "Application.h"

#include <QtCore/QFile>

namespace MetaData
{

static QStringList properAPEv2KeyNames;

typedef struct
{
	char magic[8]; // 'APETAGEX'
	quint32 version; // 1000 or 2000
	quint32 tagSize; // Including the footer (if this is the header) and all tag items (excluding this header)
	quint32 itemCount;
	quint32 flags;
	char reserved[8]; // Must be zero
}APEv2Header;

typedef struct
{
	quint32 valueSize;
	quint32 flags;
}APEv2Item;

}; // namespace MetaData

using namespace MetaData;

APEv2::APEv2(QObject *parent) : AdvancedTag(parent), mCuesheet(0)
{
	mCurrentEncoding = defaultEncoding();
	setupKeyNames();
};

APEv2::APEv2(const QString& path) : AdvancedTag(0), mCuesheet(0)
{
	mCurrentEncoding = defaultEncoding();
	setupKeyNames();
	read(path);
};

void APEv2::setupKeyNames()
{
	if( properAPEv2KeyNames.count() )
		return;

	properAPEv2KeyNames << "Title" << "Subtitle" << "Artist" << "Album" << "Debut album" << "Publisher"
		<< "Conductor" << "Track" << "Composer" << "Comment" << "Copyright" << "Publicationright" << "File"
		<< "EAN" << "UPC" << "ISBN" << "Catalog" << "LC" << "Year" << "Record Date" << "Record Location"
		<< "Genre" << "Media" << "Index" << "Related" << "ISRC" << "Abstract" << "Language"
		<< "Bibliography" << "Introplay" << "Dummy" << "Cuesheet" << "Album Artist";
};

QFlags<AdvancedTag::TagFeatures> APEv2::features()
{
	QFlags<AdvancedTag::TagFeatures> theFeatures;
	theFeatures |= AdvancedTag::Disc | AdvancedTag::TotalDiscs | AdvancedTag::TotalTracks
			| AdvancedTag::Composer | AdvancedTag::Performer | AdvancedTag::AlbumArtist
			| AdvancedTag::Date | AdvancedTag::ReplayGain | AdvancedTag::EmbeddedCoverArt
			| AdvancedTag::CustomTags | AdvancedTag::MultipleEntries | AdvancedTag::CuesheetTag;

	return theFeatures;
};

QStringList APEv2::titles() const
{
	return stringListFromVariantList( tag(QLatin1String("Title")) );
};

void APEv2::setTitles(const QStringList& titles)
{
	AdvancedTag::setTag(QLatin1String("Title"), titles);
};

QStringList APEv2::artists() const
{
	return stringListFromVariantList( tag(QLatin1String("Artist")) );
};

void APEv2::setArtists(const QStringList& artists)
{
	AdvancedTag::setTag(QLatin1String("Artist"), artists);
};

QStringList APEv2::albums() const
{
	return stringListFromVariantList( tag(QLatin1String("Album")) );
};

void APEv2::setAlbums(const QStringList& albums)
{
	AdvancedTag::setTag(QLatin1String("Album"), albums);
};

QStringList APEv2::comments() const
{
	return stringListFromVariantList( tag(QLatin1String("Comment")) );
};

void APEv2::setComments(const QStringList& comments)
{
	AdvancedTag::setTag(QLatin1String("Comment"), comments);
};

QStringList APEv2::genres() const
{
	return stringListFromVariantList( tag(QLatin1String("Genre")) );
};

void APEv2::setGenres(const QStringList& genres)
{
	AdvancedTag::setTag(QLatin1String("Genre"), genres);
};

int APEv2::year() const
{
	QString theYear = stringFromVariant( tag(QLatin1String("Year"), 0) );
	if( theYear.contains(QLatin1Char('-')) )
		return theYear.split(QLatin1Char('-')).first().toInt();

	return theYear.toInt();
};

void APEv2::setYear(int year)
{
	QString theYear = stringFromVariant( tag(QLatin1String("Year"), 0) );
	if( theYear.contains(QLatin1Char('-')) )
	{
		QStringList yearList = theYear.split(QLatin1Char('-'));
		yearList.takeFirst();
		yearList = QStringList() << QString::number(year) << yearList;
		theYear = yearList.join("-");
	}
	else
	{
		theYear = QString::number(year);
	}

	AdvancedTag::setTag(QLatin1String("Year"), theYear);
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

	AdvancedTag::setTag(QLatin1String("TRACK"), theTrack);
};

void APEv2::clear()
{
	mTags.clear();
};

bool APEv2::isEmpty()
{
	return mTags.count();
};

QString APEv2::encoding() const
{
	return mCurrentEncoding;
};

QString APEv2::defaultEncoding() const
{
	return "UTF-8";
};

Tag* APEv2::duplicate()
{
	APEv2 *tag = new APEv2;
	tag->mTags = mTags;
};

qint64 APEv2::size()
{
	return 0;
};

QByteArray APEv2::tagData() const
{
	return QByteArray();
};

void APEv2::removeTag(const QString& path)
{
	Q_UNUSED(path);
};

qint64 APEv2::position(const QString& path)
{
	QFile file(path);

	// Open the file for reading
	if(!file.open(QIODevice::ReadOnly))
		return -1;

	// Make sure the file is big enough to hold a APEv2 tag
	if(file.size() < sizeof(APEv2Header))
	{
		file.close();
		return -1;
	}

	{
		APEv2Header header;

		// Read in the tag header
		file.read((char*)&header, sizeof(APEv2Header));

		// Check for a header
		if(memcmp(header.magic, "APETAGEX", 8) == 0)
		{
			file.close();
			return 0;
		}

		// Seek to the right place in the file
		file.seek(file.size() - sizeof(APEv2Header));

		// Read in the tag footer
		file.read((char*)&header, sizeof(APEv2Header));

		// Check for a footer
		if(memcmp(header.magic, "APETAGEX", 8) == 0)
		{
			file.close();
			return file.size() - sizeof(APEv2Header) - header.tagSize;
		}

		// Make sure the file is big enough to hold a ID3v1 and APEv2 tag
		if(file.size() < (sizeof(APEv2Header) + 128))
		{
			file.close();
			return -1;
		}

		// Seek to the right place in the file
		file.seek(file.size() - sizeof(APEv2Header) - 128);

		// Read in the tag footer
		file.read((char*)&header, sizeof(APEv2Header));

		// Last ditch check for a ID3v1 in the way
		if(memcmp(header.magic, "APETAGEX", 8) == 0)
		{
			file.close();
			return file.size() - sizeof(APEv2Header) - header.tagSize;
		}
	}

	return -1;
};

bool APEv2::fileContainsTag(const QString& path)
{
	return (position(path) >= 0);
};

bool APEv2::conformsToSpec(const QString& path)
{
	return (!path.isEmpty());
};

bool APEv2::read(const QString& path, const QString& encoding)
{
	qint64 pos = position(path);
	if(pos < 0)
		return false;

	QFile file(path);

	// Open the file for reading
	if(!file.open(QIODevice::ReadOnly))
		return false;

	mCurrentEncoding = encoding.isEmpty() ? defaultEncoding() : encoding;

	int size = 0, count = 0;

	{
		APEv2Header header;

		// Seek to the right place in the file
		file.seek(pos);

		// Read in the tag header
		file.read((char*)&header, sizeof(APEv2Header));

		size = header.tagSize;
		count = header.itemCount;
	}

	APEv2Item item;
	char keyBuffer;
	int type;

	AdvancedTag::TagType tagType;

	QString key;
	QByteArray value;

	uDebug( "APEv2", tr("Header size: %1").arg(sizeof(APEv2Header)) );
	uDebug( "APEv2", tr("Position: %1").arg(pos) );
	uDebug( "APEv2", tr("Size: %1").arg(size) );
	uDebug( "APEv2", tr("Reading in %1 tags").arg(count) );

	// Read in each tag item
	for(int i = 0; i < count; i++)
	{
		// Read in the first part of the item
		file.read((char*)&item, sizeof(APEv2Item));

		key.clear();

		// Read the key
		file.read(&keyBuffer, 1);
		while(keyBuffer != 0x00)
		{
			key.append(keyBuffer);
			file.read(&keyBuffer, 1);
		}

		uDebug( "APEv2", tr("Key: %1").arg(key) );
		uDebug( "APEv2", tr("Tag value size: %1").arg(item.valueSize) );

		type = (item.flags && 0x06) >> 1;
		switch(type)
		{
			case 0:
				tagType = String;
				break;
			case 1:
				tagType = Binary;
				break;
			case 2:
				tagType = URL;
				break;
			default:
				tagType = Unknown;
				break;
		}

		uDebug( "APEv2", tr("Tag type: %1").arg(type) );

		// Read in the tag value
		QByteArray data = file.read(item.valueSize);

		TagPair pair;
		pair.first = tagType;

		if(tagType == String || tagType == URL)
		{
			TagData list;
			foreach(QByteArray array, data.split(0x00))
			{
				uDebug( "APEv2", tr("Value: %1").arg( QString::fromUtf8( array.data() ) ) );
				list << array;
			}

			pair.second = list;
		}
		else
			pair.second = TagData() << data;

		mTags[ key.toUpper() ] = pair;
	}

	file.close();

	return true;
};

bool APEv2::write(const QString& path, const QString& encoding)
{
	Q_UNUSED(path);
	Q_UNUSED(encoding);

	return false;
};

int APEv2::totalTracks() const
{
	QString total = tag(QLatin1String("Track")).first().toString();
	if( total.contains('/') )
		return total.split('/').last().toInt();

	return 0;
};

void APEv2::setTotalTracks(int total)
{
	QString first = tag(QLatin1String("Track")).first().toString();
	if( first.contains('/') )
		first = first.split('/').first();

	AdvancedTag::setTag(QLatin1String("Track"), first + '/' + total);
};

int APEv2::disc() const
{
	return 0;
};

void APEv2::setDisc(int disc)
{
};

int APEv2::totalDiscs() const
{
	return 0;
};

void APEv2::setTotalDiscs(int total)
{
};

QString APEv2::composer() const
{
	return QString();
};

void APEv2::setComposer(const QString& composer)
{
};

QStringList APEv2::composers() const
{
	return QStringList();
};

void APEv2::setComposers(const QStringList& composers)
{
};

QString APEv2::performer() const
{
	return QString();
};

void APEv2::setPerformer(const QString& performer)
{
};

QStringList APEv2::performers() const
{
	return QStringList();
};

void APEv2::setPerformers(const QStringList& performers)
{
};

QString APEv2::albumArtist() const
{
	return QString();
};

void APEv2::setAlbumArtist(const QString& albumArtist)
{
};

QStringList APEv2::albumArtists() const
{
	return QStringList();
};

void APEv2::setAlbumArtists(const QStringList& albumArtists)
{
};

QDate APEv2::date() const
{
	return QDate();
};

void APEv2::setDate(const QDate& date)
{
};

float APEv2::trackGain() const
{
	return 0;
};

void APEv2::setTrackGain(float gain)
{
};

float APEv2::trackPeak() const
{
	return 0;
};

void APEv2::setTrackPeak(float peak)
{
};

float APEv2::albumGain() const
{
	return 0;
};

void APEv2::setAlbumGain(float gain)
{
};

float APEv2::albumPeak() const
{
	return 0;
};

void APEv2::setAlbumPeak(float peak)
{
};

QPixmap APEv2::cover() const
{
	QPixmap pixmap;
	pixmap.loadFromData( tag(QLatin1String("Cover")).first().toByteArray() );

	return pixmap;
};

void APEv2::setCover(const QPixmap& cover)
{
	QByteArray data;
	cover.save(data);

	AdvancedTag::setTag(QLatin1String("Cover"), data);
};

int APEv2::tagCount()
{
	return mTags.count();
};

QStringList APEv2::tagKeys() const
{
	return mTags.keys();
};

QString APEv2::tagKey(int index) const
{
	if( index > 0 && index < mTags.keys().count() )
		return mTags.keys().at(index);

	return QString();
};

/// @TODO Make these case-insensitive
bool APEv2::containsTag(const QString& key)
{
	return mTags.contains(key);
};

int APEv2::tagCount(const QString& key) const
{
	return mTags.value(key).second.count();
};

AdvancedTag::TagType APEv2::tagType(const QString& key) const
{
	return mTags.value(key).first;
};

QList<QVariant> APEv2::tag(const QString& key) const
{
	if( mTags.contains( key.toUpper() ) )
		return mTags.value( key.toUpper() ).second; // "ALBUMARTIST"

	return QList<QVariant>();
};

QVariant APEv2::tag(const QString& key, int index) const
{
	if( mTags.contains( key.toUpper() ) )
	{
		QList<QVariant> items = mTags.value( key.toUpper() ).second;
		if(items.count() > index)
			return items.at(index);
	}

	return QVariant();
};

void APEv2::addTag(const QString& key, const QList<QVariant>& tag, TagType type)
{
	TagPair pair = mTags.value( key.toUpper() );
	pair.first = type;
	pair.second = QList<QVariant>() << pair.second << tag;

	mTags[ key.toUpper() ] = pair;
};

void APEv2::setTag(const QString& key, const QList<QVariant>& tag, TagType type)
{
	TagPair pair;
	pair.first = type;
	pair.second = tag;

	mTags[ key.toUpper() ] = pair;
};

void APEv2::clearTag(const QString& key)
{
	mTags.remove(key);
};

void APEv2::clearTag(const QString& key, int index)
{
	if( !mTags.contains(key) )
		return;

	TagData data = mTags.value(key).second;
	if( index >= 0 && index < data.count() )
	{
		data.removeAt(index);
		mTags[key].second = data;
	}
};

MetaData::Cuesheet* APEv2::cuesheet()
{
	return mCuesheet;
};

void APEv2::setCuesheet(MetaData::Cuesheet *sheet)
{
	if(!sheet)
		return;

	delete mCuesheet;
	mCuesheet = sheet;
	mCuesheet->write( QString() );
};

void APEv2::setCuesheet(const QString& text, bool updateSheet)
{
	AdvancedTag::setTag(QLatin1String("Cuesheet"), text);

	if(!updateSheet)
		return;

	if(!mCuesheet)
		mCuesheet = new Cuesheet;

	mCuesheet->read(text);
};

void APEv2::removeCuesheet()
{
	clearTag(QLatin1String("Cuesheet"));

	if(mCuesheet)
		delete mCuesheet;
};

QString APEv2::type() const
{
	return "APEv2";
};

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
