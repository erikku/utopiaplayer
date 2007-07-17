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
 * @file songedition.cpp The SongEdition block class implementation
 */

#include "songedition.h"

using namespace Utopia;

SongEdition::SongEdition() : UtopiaBlock()
{
	d = new SongEditionData;
	clear();
};

bool SongEdition::operator==(const SongEdition& block)
{
	if(d->mTitle != block.d->mTitle || d->mSubTitle != block.d->mSubTitle || d->mPropertyTags != block.d->mPropertyTags || d->mLastPlayed != block.d->mLastPlayed
	|| d->mRandomPlay != block.d->mRandomPlay || d->mPlayCount != block.d->mPlayCount || d->mRating != block.d->mRating || d->mAlbums != block.d->mAlbums || d->mSong != block.d->mSong)
		return false;

	return UtopiaBlock::operator==(block);
};

bool SongEdition::operator!=(const SongEdition& block)
{
	return !( SongEdition::operator==(block) );
};

QMap<QString, QString> SongEdition::titles() const
{
	return d->mTitle;
};

bool SongEdition::containsTitle(const QString& title)
{
	return d->mTitle.values().contains(title);
};

QString SongEdition::title(const QString& lang) const
{
	return d->mTitle.value(lang);
};

QMap<QString, QString> SongEdition::subtitles() const
{
	return d->mSubTitle;
};

bool SongEdition::containsSubtitle(const QString& subtitle)
{
	return d->mSubTitle.values().contains(subtitle);
};

QString SongEdition::subtitle(const QString& lang) const
{
	return d->mSubTitle.value(lang);
};

QStringList SongEdition::tags() const
{
	return d->mPropertyTags;
};

bool SongEdition::containsTag(const QString& tag)
{
	return d->mPropertyTags.contains(tag);
};

QList<QDateTime> SongEdition::timesPlayed() const
{
	return d->mLastPlayed;
};

QDateTime SongEdition::lastPlayed() const
{
	if(d->mLastPlayed.isEmpty())
		return QDateTime();

	return d->mLastPlayed.last();
};

bool SongEdition::randomPlay()
{
	return d->mRandomPlay;
};

int SongEdition::playCount()
{
	return d->mPlayCount;
};

int SongEdition::rating()
{
	return d->mRating;
};

QList<AlbumSet> SongEdition::albums() const
{
	return d->mAlbums;
};

AlbumSet SongEdition::album(uid album) const
{
	AlbumSet set;

	for(int i = 0; i < d->mAlbums.count(); i++)
	{
		set = d->mAlbums.at(i);

		if(set.album() == album)
			return set;
	}

	return AlbumSet();
};

AlbumSet SongEdition::album(int track, int disc) const
{
	AlbumSet set;

	for(int i = 0; i < d->mAlbums.count(); i++)
	{
		set = d->mAlbums.at(i);

		if(set.track() == track && set.disc() == disc)
			return set;
	}

	return AlbumSet();
};

void SongEdition::addTitle(const QString& title, const QString& lang)
{
	d->mTitle[lang] = title;
};

void SongEdition::removeTitle(const QString& title, const QString& lang)
{
	if(title.isEmpty())
		d->mTitle.remove(lang);
	else
		d->mTitle.remove( d->mTitle.key(title) );
};

void SongEdition::clearTitle()
{
	d->mTitle.clear();
};

void SongEdition::addSubtitle(const QString& subtitle, const QString& lang)
{
	d->mSubTitle[lang] = subtitle;
};

void SongEdition::removeSubtitle(const QString& subtitle, const QString& lang)
{
	if(subtitle.isEmpty())
		d->mSubTitle.remove(lang);
	else
		d->mSubTitle.remove( d->mSubTitle.key(subtitle) );
};

void SongEdition::clearSubtitle()
{
	d->mSubTitle.clear();
};

void SongEdition::addTag(const QString& tag)
{
	if( d->mPropertyTags.contains(tag) )
		return;

	d->mPropertyTags << tag;
};

void SongEdition::removeTag(const QString& tag)
{
	int index = d->mPropertyTags.indexOf(tag);
	if( index == -1 )
		return;

	d->mPropertyTags.removeAt(index);
};

void SongEdition::clearTags()
{
	d->mPropertyTags.clear();
};

void SongEdition::addTimePlayed(const QDateTime& time)
{
	if(d->mLastPlayed.count() > 9)
		d->mLastPlayed.removeFirst();

	d->mLastPlayed << time;
};

void SongEdition::clearTimesPlayed()
{
	d->mLastPlayed.clear();
};

void SongEdition::setRandomPlay(bool random)
{
	d->mRandomPlay = random;
};

void SongEdition::increasePlayCount()
{
	d->mPlayCount++;
};

void SongEdition::decreasePlayCount()
{
	d->mPlayCount--;
};

void SongEdition::setPlayCount(int count)
{
	d->mPlayCount = count;
};

void SongEdition::clearPlayCount()
{
	d->mPlayCount = 0;
};

void SongEdition::setRating(int rating)
{
	d->mRating = rating;
};

void SongEdition::addAlbum(const AlbumSet& album)
{
	if( d->mAlbums.contains(album) )
		return;

	d->mAlbums << album;
};

void SongEdition::addAlbum(uid album, int track, int disc)
{
	AlbumSet set;
	set.setAlbum(album);
	set.setTrack(track);
	set.setDisc(disc);

	d->mAlbums << set;
};

void SongEdition::removeAlbum(const AlbumSet& album)
{
	int index = d->mAlbums.indexOf(album);
	if( index == -1 )
		return;

	d->mAlbums.removeAt(index);
};

void SongEdition::removeAlbum(uid album)
{
	AlbumSet set;
	QMutableListIterator<AlbumSet> i(d->mAlbums);

	while( i.hasNext() )
	{
		set = i.next();

		if(set.album() == album)
			i.remove();
	}
};

void SongEdition::removeAlbum(int track, int disc)
{
	AlbumSet set;
	QMutableListIterator<AlbumSet> i(d->mAlbums);

	while( i.hasNext() )
	{
		set = i.next();

		if(set.track() == track && set.disc() == disc)
			i.remove();
	}
};

void SongEdition::clearAlbums()
{
	d->mAlbums.clear();
};

void SongEdition::clear()
{
	d->mTitle.clear();
	d->mSubTitle.clear();
	d->mPropertyTags.clear();
	d->mLastPlayed.clear();
	d->mRandomPlay = true;
	d->mPlayCount = 0;
	d->mRating = 0;
	d->mSong = 0;
	d->mAlbums.clear();

	UtopiaBlock::clear();
};

void SongEdition::setSong(uid song)
{
	d->mSong = song;
};

QString SongEdition::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<songedition>\n";

	string += UtopiaBlock::xml(false);

	if(d->mTitle.count())
		string += xmlLangMap("title", d->mTitle);
	if(d->mSubTitle.count())
		string += xmlLangMap("subtitle", d->mSubTitle);
	if(d->mPropertyTags.count())
		string += "  <tags>" + d->mPropertyTags.join(",") + "</tags>\n";

	if(!d->mLastPlayed.count())
	{
		string += "  <lastplayed>\n";
		for(int i = 0; i < d->mLastPlayed.count(); i++)
		{
			string += "    <timestamp>" + d->mLastPlayed.at(i).toString(Qt::ISODate) + "</timestamp>\n";
		}
		string += "  </lastplayed>\n";
	}

	if(d->mRandomPlay)
		string += "  <randomplay/>\n";
	if(d->mPlayCount)
		string += "  <playcount>" + QString::number(d->mPlayCount) + "</playcount>\n";
	if(d->mRating)
		string += "  <rating>" + QString::number(d->mRating) + "</rating>\n";
	if(d->mSong)
		string += "  <song>" + QString::number(d->mSong) + "</song>\n";

	if(d->mAlbums.count())
	{
		string += "  <albums>\n";
		for(int i = 0; i < d->mAlbums.count(); i++)
		{
			string += d->mAlbums.at(i).xml();
		}
		string += "  </albums>\n";
	}

	if(encased)
		string += "</songedition>\n";

	return string;
};

bool SongEditionParser::startDocument()
{
	delete mBlock;
	mBlock = new SongEdition;

	return true;
};

bool SongEditionParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
	UtopiaBlockParser::startElement(namespaceURI, localName, qName, atts);

	if(localName == "album")
		((SongEdition*)mBlock)->addAlbum(atts.value("id").trimmed().toInt(), atts.value("track").trimmed().toInt(), atts.value("disc").trimmed().toInt());

	if(localName == "randomplay")
		((SongEdition*)mBlock)->setRandomPlay(true);

	return true;
};

bool SongEditionParser::characters(const QString& ch)
{
	if(mElements.top() == "value")
	{
		if( mElements.at(mElements.count() - 2) == "title" )
		{
			((SongEdition*)mBlock)->addTitle(ch.trimmed(), mAtts.top().value("lang"));
			return true;
		}
		if( mElements.at(mElements.count() - 2) == "subtitle" )
		{
			((SongEdition*)mBlock)->addSubtitle(ch.trimmed(), mAtts.top().value("lang"));
			return true;
		}
	}
	if(mElements.top() == "title")
		return true;
	if(mElements.top() == "subtitle")
		return true;

	if(mElements.top() == "tags")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((SongEdition*)mBlock)->addTag(id.trimmed());
		}
		return true;
	}

	if(mElements.top() == "timestamp")
	{
		if( mElements.at(mElements.count() - 2) == "lastplayed" )
		{
			((SongEdition*)mBlock)->addTimePlayed(QDateTime::fromString(ch.trimmed(), Qt::ISODate));
			return true;
		}
	}
	if(mElements.top() == "lastplayed")
		return true;

	if(mElements.top() == "playcount")
	{
		((SongEdition*)mBlock)->setPlayCount(ch.trimmed().toInt());
		return true;
	}
	if(mElements.top() == "rating")
	{
		((SongEdition*)mBlock)->setRating(ch.trimmed().toInt());
		return true;
	}
	if(mElements.top() == "song")
	{
		((SongEdition*)mBlock)->setSong(ch.trimmed().toInt());
		return true;
	}

	if(mElements.top() == "albums")
		return true;

	return UtopiaBlockParser::characters(ch);
};
