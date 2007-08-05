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
 * @file album.cpp The Album block class implementation
 */

#include "album.h"

#include <QtXml/QXmlStreamWriter>

using namespace Utopia;

Album::Album() : UtopiaBlock()
{
	d = new AlbumData;
};

Album::Album(const QString& name) : UtopiaBlock()
{
	d = new AlbumData;
	addAlbumTitle(name);
};

bool Album::operator==(const Album& block)
{
	if(d->mTitle != block.d->mTitle || d->mVariation != block.d->mVariation || d->mReleaseDate != block.d->mReleaseDate ||
		d->mArtists != block.d->mArtists || d->mPublishers != block.d->mPublishers || d->mCovers != block.d->mCovers ||
		d->mIdentifiers != block.d->mIdentifiers || d->mFormat != block.d->mFormat || d->mTracks != block.d->mTracks ||
		d->mCompilation != block.d->mCompilation || d->mPropertyTags != block.d->mPropertyTags)
		return false;

	return UtopiaBlock::operator==(block);
};

bool Album::operator!=(const Album& block)
{
	return !( Album::operator==(block) );
};

QStringList Album::albumLangs() const
{
	return d->mTitle.keys();
};

bool Album::albumContainsLang(const QString& lang)
{
	return d->mTitle.keys().contains(lang);
};

QMap<QString, QString> Album::albumTitles() const
{
	return d->mTitle;
};

bool Album::albumContainsTitle(const QString& title)
{
	return d->mTitle.values().contains(title);
};

QString Album::albumTitle(const QString& lang) const
{
	return d->mTitle.value(lang);
};

QMap<QString, QString> Album::albumVariations() const
{
	return d->mVariation;
};

bool Album::albumContainsVariation(const QString& variation)
{
	return d->mVariation.values().contains(variation);
};

QString Album::albumVariation(const QString& lang) const
{
	return d->mVariation.value(lang);
};


QDate Album::releaseDate() const
{
	return d->mReleaseDate;
};

QList<uid> Album::artists() const
{
	return d->mArtists;
};

QList<uid> Album::publishers() const
{
	return d->mPublishers;
};

uid Album::cover(const QString& page)
{
	return d->mCovers.value(page);
};

QMap<QString, QString> Album::identifiers() const
{
	return d->mIdentifiers;
};

QString Album::identifier(const QString& key) const
{
	return d->mIdentifiers.value(key);
};

QString Album::format() const
{
	return d->mFormat;
};

QList<SongSet> Album::tracks() const
{
	return d->mTracks;
};

bool Album::isCompilation()
{
	return d->mCompilation;
};

void Album::addCover(uid cover, const QString& page)
{
	d->mCovers[page] = cover;
};

void Album::clearPublishers()
{
	d->mPublishers.clear();
};

void Album::addPublisher(uid publisher)
{
	if( d->mPublishers.contains(publisher) )
		return;

	d->mPublishers << publisher;
};

void Album::setFormat(const QString& fmt)
{
	d->mFormat = fmt;
};

void Album::removeCover(uid song)
{
	d->mCovers.remove( d->mCovers.key(song) );
};

void Album::clearReleaseDate()
{
	d->mReleaseDate = QDate();
};

void Album::removeTrack(uid song)
{
	SongSet set;
	QMutableListIterator<SongSet> i(d->mTracks);

	while( i.hasNext() )
	{
		set = i.next();

		if(set.song() == song)
			i.remove();
	}
};

void Album::removeTrack(const SongSet& track)
{
	int index = d->mTracks.indexOf(track);
	if( index == -1 )
		return;

	d->mTracks.removeAt(index);
};

void Album::removeTrack(int track, int disc)
{
	SongSet set;
	QMutableListIterator<SongSet> i(d->mTracks);

	while( i.hasNext() )
	{
		set = i.next();

		if(set.track() == track && set.disc() == disc)
			i.remove();
	}
};

void Album::addAlbumTitle(const QString& title, const QString& lang)
{
	d->mTitle[lang] = title;
};

void Album::clearAlbumVariations()
{
	d->mVariation.clear();
};

void Album::addArtist(uid artist)
{
	if( d->mArtists.contains(artist) )
		return;

	d->mArtists << artist;
};

void Album::clearIdentifiers()
{
	d->mIdentifiers.clear();
};

void Album::clearArtists()
{
	d->mArtists.clear();
};

void Album::removeArtist(uid artist)
{
	int index = d->mArtists.indexOf(artist);
	if( index == -1 )
		return;

	d->mArtists.removeAt(index);
};

void Album::clearTracks()
{
	d->mTracks.clear();
};

void Album::clear()
{
	d->mTitle.clear();
	d->mVariation.clear();
	d->mReleaseDate = QDate();
	d->mArtists.clear();
	d->mPublishers.clear();
	d->mCovers.clear();
	d->mIdentifiers.clear();
	d->mFormat = QString();
	d->mTracks.clear();
	d->mCompilation = false;
	d->mPropertyTags.clear();

	UtopiaBlock::clear();
};

void Album::clearFormat()
{
	d->mFormat = QString();
};

void Album::addAlbumVariation(const QString& variation, const QString& lang)
{
	d->mVariation[lang] = variation;
};

void Album::removeIdentifier(const QString& key)
{
	d->mIdentifiers.remove( key );
};

void Album::addTrack(uid song, int track, int disc)
{
	SongSet set;
	set.setSong(song);
	set.setTrack(track);
	set.setDisc(disc);

	if( d->mTracks.contains(set) )
		return;

	d->mTracks << set;

};

void Album::setReleaseDate(const QDate& date)
{
	d->mReleaseDate = date;
};

void Album::removeAlbumTitle(const QString& title, const QString& lang)
{
	if(title.isEmpty())
	{
		d->mTitle.remove( lang );
	}
	else
	{
		d->mTitle.remove( d->mTitle.key(title) );
	}
};

void Album::removeAlbumVariation(const QString& variation, const QString& lang)
{
	if(variation.isEmpty())
	{
		d->mVariation.remove( lang );
	}
	else
	{
		d->mVariation.remove( d->mVariation.key(variation) );
	}
};

void Album::addTrack(const SongSet& track)
{
	if( d->mTracks.contains(track) )
		return;

	d->mTracks << track;
};

void Album::removePublisher(uid publisher)
{
	int index = d->mPublishers.indexOf(publisher);
	if( index == -1 )
		return;

	d->mPublishers.removeAt(index);
};

void Album::addIdentifier(const QString& value, const QString& key)
{
	d->mIdentifiers[key] = value;
};

void Album::setCompilation(bool compilation)
{
	d->mCompilation = compilation;
};

void Album::clearCovers()
{
	d->mCovers.clear();
};

void Album::clearCompilation()
{
	d->mCompilation = false;
};

void Album::clearAlbumTitles()
{
	d->mTitle.clear();
};

QStringList Album::tags() const
{
	return d->mPropertyTags;
};

bool Album::containsTag(const QString& tag)
{
	return d->mPropertyTags.contains(tag);
};

void Album::addTag(const QString& tag)
{
	if( d->mPropertyTags.contains(tag) )
		return;

	d->mPropertyTags << tag;
};

void Album::removeTag(const QString& tag)
{
	int index = d->mPropertyTags.indexOf(tag);
	if( index == -1 )
		return;

	d->mPropertyTags.removeAt(index);
};

void Album::clearTags()
{
	d->mPropertyTags.clear();
};

void Album::xmlSegment(QXmlStreamWriter *writer, bool encased) const
{
	if(encased)
		writer->writeStartElement("album");

	UtopiaBlock::xmlSegment(writer, false);

	if(d->mTitle.count())
		xmlLangMap(writer, "title", d->mTitle);
	if(d->mVariation.count())
		xmlLangMap(writer, "variation", d->mVariation);
	if(!d->mReleaseDate.isValid())
		writer->writeTextElement("releasedate>", d->mReleaseDate.toString("yyyy-MM-dd"));
	if(d->mArtists.count())
		xmlIdList(writer, "artists", d->mArtists);
	if(d->mPublishers.count())
		xmlIdList(writer, "publishers", d->mPublishers);

	if(d->mCovers.count())
	{
		writer->writeStartElement("covers");

		QStringList keys = d->mCovers.keys();
		for(int i = 0; i < keys.count(); i++)
		{
			writer->writeStartElement("cover");
			writer->writeAttribute("name", keys.at(i));
			writer->writeCharacters( QString::number(d->mCovers.value(keys.at(i))) );
			writer->writeEndElement();
		}

		writer->writeEndElement();
	}

	if(d->mIdentifiers.count())
	{
		writer->writeStartElement("identifiers");

		QStringList keys = d->mIdentifiers.keys();
		for(int i = 0; i < keys.count(); i++)
		{
			writer->writeStartElement("identifier");
			writer->writeAttribute("name", keys.at(i));
			writer->writeCharacters( d->mIdentifiers.value(keys.at(i)) );
			writer->writeEndElement();
		}

		writer->writeEndElement();
	}

	if(!d->mFormat.isEmpty())
		writer->writeTextElement("format", d->mFormat);

	if(d->mTracks.count())
	{
		writer->writeStartElement("tracks");

		QStringList tracks;
		for(int i = 0; i < d->mTracks.count(); i++)
			d->mTracks.at(i).xmlSegment(writer);

		writer->writeEndElement();
	}

	if(d->mPropertyTags.count())
		writer->writeTextElement("tags", d->mPropertyTags.join(","));

	if(d->mCompilation)
		writer->writeEmptyElement("compilation");

	if(encased)
		writer->writeEndElement();
};

bool AlbumParser::startDocument()
{
	delete mBlock;
	mBlock = new Album;

	return true;
};

bool AlbumParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
	UtopiaBlockParser::startElement(namespaceURI, localName, qName, atts);

	if(localName == "song")
		((Album*)mBlock)->addTrack(atts.value("id").trimmed().toInt(), atts.value("track").trimmed().toInt(), atts.value("disc").trimmed().toInt());

	if(localName == "compilation")
		((Album*)mBlock)->setCompilation(true);

	return true;
};

bool AlbumParser::characters(const QString& ch)
{
	if(mElements.top() == "value")
	{
		if( mElements.at(mElements.count() - 2) == "title" )
		{
			((Album*)mBlock)->addAlbumTitle(ch.trimmed(), mAtts.top().value("lang"));
			return true;
		}
		if( mElements.at(mElements.count() - 2) == "variation" )
		{
			((Album*)mBlock)->addAlbumVariation(ch.trimmed(), mAtts.top().value("lang"));
			return true;
		}
	}
	if(mElements.top() == "title")
		return true;
	if(mElements.top() == "variation")
		return true;

	if(mElements.top() == "releasedata")
	{
		((Album*)mBlock)->setReleaseDate(QDate::fromString(ch.trimmed(), "yyyy-MM-dd"));
		return true;
	}

	if(mElements.top() == "artists")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Album*)mBlock)->addArtist(id.toInt());
		}
		return true;
	}
	if(mElements.top() == "publishers")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Album*)mBlock)->addPublisher(id.toInt());
		}
		return true;
	}

	if(mElements.top() == "cover")
	{
		((Album*)mBlock)->addCover(ch.trimmed().toInt(), mAtts.top().value("name"));
		return true;
	}
	if(mElements.top() == "covers")
		return true;

	if(mElements.top() == "identifier")
	{
		((Album*)mBlock)->addIdentifier(ch.trimmed(), mAtts.top().value("name"));
		return true;
	}
	if(mElements.top() == "identifiers")
		return true;

	if(mElements.top() == "format")
	{
		((Album*)mBlock)->setFormat(ch.trimmed());
		return true;
	}

	if(mElements.top() == "tracks")
		return true;

	if(mElements.top() == "tags")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Album*)mBlock)->addTag(id);
		}
		return true;
	}

	return UtopiaBlockParser::characters(ch);
};
