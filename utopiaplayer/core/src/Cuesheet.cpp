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

#include "Cuesheet.h"

using namespace MetaData;

QFlags<AdvancedTag::TagFeatures> CuesheetTrack::features()
{
	QFlags<AdvancedTag::TagFeatures> theFeatures;
	theFeatures |= AdvancedTag::Disc | AdvancedTag::TotalDiscs | AdvancedTag::TotalTracks
			| AdvancedTag::Composer | AdvancedTag::Performer | AdvancedTag::AlbumArtist
			| AdvancedTag::Date | AdvancedTag::ReplayGain | AdvancedTag::CustomTags
			| AdvancedTag::MultipleEntries;

	return theFeatures;
};

int CuesheetTrack::year() const
{
	return tag(QLatin1String("YEAR")).first().toInt();
};

void CuesheetTrack::setYear(int year)
{
	AdvancedTag::setTag(QLatin1String("YEAR"), QString::number(year));
};

int CuesheetTrack::track() const
{
	return tag(QLatin1String("TRACK")).first().toInt();
};

void CuesheetTrack::setTrack(int track)
{
	AdvancedTag::setTag(QLatin1String("TRACK"), QString::number(track));
};

void CuesheetTrack::clear()
{
	mTags.clear();
};

bool CuesheetTrack::isEmpty()
{
	return (mTags.count() == 0);
};

QString CuesheetTrack::encoding() const
{
	return "UTF-8";
};

QString CuesheetTrack::defaultEncoding() const
{
	return "UTF-8";
};

Tag* CuesheetTrack::duplicate()
{
	CuesheetTrack *tag = new CuesheetTrack;
	tag->mTags = mTags;

	return tag;
};

qint64 CuesheetTrack::size()
{
	return tagData().size();
};

QByteArray CuesheetTrack::tagData() const
{
	return QByteArray();
};

void CuesheetTrack::removeTag(const QString& path) { };

qint64 CuesheetTrack::position(const QString& path)
{
	return 0;
};

bool CuesheetTrack::fileContainsTag(const QString& path)
{
	return false;
};

bool CuesheetTrack::conformsToSpec(const QString& path)
{
	return true;
};

bool CuesheetTrack::read(const QString& path, const QString& encoding)
{
	return true;
};

bool CuesheetTrack::write(const QString& path, const QString& encoding)
{
	Q_UNUSED(path);

	return true;
};

QStringList CuesheetTrack::titles() const
{
	return stringListFromVariantList( tag(QLatin1String("TITLE")) );
};

void CuesheetTrack::setTitles(const QStringList& titles)
{
	AdvancedTag::setTag(QLatin1String("TITLE"), titles);
};

QStringList CuesheetTrack::artists() const
{
	return stringListFromVariantList( tag(QLatin1String("ARTIST")) );
};

void CuesheetTrack::setArtists(const QStringList& artists)
{
	AdvancedTag::setTag(QLatin1String("ARTIST"), artists);
};

QStringList CuesheetTrack::albums() const
{
	return stringListFromVariantList( tag(QLatin1String("ALBUM")) );
};

void CuesheetTrack::setAlbums(const QStringList& albums)
{
	AdvancedTag::setTag(QLatin1String("ALBUM"), albums);
};

QStringList CuesheetTrack::comments() const
{
	return stringListFromVariantList( tag(QLatin1String("COMMENT")) );
};

void CuesheetTrack::setComments(const QStringList& comments)
{
	AdvancedTag::setTag(QLatin1String("COMMENT"), comments);
};

QStringList CuesheetTrack::genres() const
{
	return stringListFromVariantList( tag(QLatin1String("GENRE")) );
};

void CuesheetTrack::setGenres(const QStringList& genres)
{
	AdvancedTag::setTag(QLatin1String("GENRE"), genres);
};

QString CuesheetTrack::type() const
{
	return "CuesheetTrack";
};
