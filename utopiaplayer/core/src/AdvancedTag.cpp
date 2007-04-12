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

#include "AdvancedTag.h"

using namespace MetaData;

bool AdvancedTag::hasFeature(AdvancedTag::TagFeature feature)
{
	return features().testFlag(feature);
};

QString AdvancedTag::title() const
{
	if(titles().count())
		return titles().first();

	return QString();
};

void AdvancedTag::setTitle(const QString& title)
{
	setTitles(QStringList() << title);
};

QString AdvancedTag::artist() const
{
	if(artists().count())
		return artists().first();

	return QString();
};

void AdvancedTag::setArtist(const QString& artist)
{
	setArtists(QStringList() << artist);
};

QString AdvancedTag::album() const
{
	if(albums().count())
		return albums().first();

	return QString();
};

void AdvancedTag::setAlbum(const QString& album)
{
	setAlbums(QStringList() << album);
};

QString AdvancedTag::comment() const
{
	if(comments().count())
		return comments().first();

	return QString();
};

void AdvancedTag::setComment(const QString& comment)
{
	setComments(QStringList() << comment);
};

QString AdvancedTag::genre() const
{
	if(genres().count())
		return genres().first();

	return QString();
};

void AdvancedTag::setGenre(const QString& genre)
{
	setGenres(QStringList() << genre);
};

QString AdvancedTag::composer() const
{
	if(composers().count())
		return composers().first();

	return QString();
};

void AdvancedTag::setComposer(const QString& composer)
{
	setComposers(QStringList() << composer);
};

QString AdvancedTag::performer() const
{
	if(performers().count())
		return performers().first();

	return QString();
};

void AdvancedTag::setPerformer(const QString& performer)
{
	setPerformers(QStringList() << performer);
};

QString AdvancedTag::albumArtist() const
{
	if(albumArtists().count())
		return albumArtists().first();

	return QString();
};

void AdvancedTag::setAlbumArtist(const QString& albumArtist)
{
	setAlbumArtists(QStringList() << albumArtist);
};
