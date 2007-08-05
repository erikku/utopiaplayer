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

#include "xmlmetabase.h"
#include "blockparser.h"
#include "qgzipfile.h"

using namespace Utopia;

#include <QtXml/QXmlStreamWriter>

XmlMetaBase::XmlMetaBase(QObject *parent) : MetaBase(parent)
{
	mNextAvailableID = 1;
};

QList<UtopiaBlock> XmlMetaBase::blocks() const
{
	return mBlocks.values();
};

QList<Album> XmlMetaBase::albums() const
{
	return mAlbums.values();
};

bool XmlMetaBase::containsAlbumTitle(const QString& title) const
{
	return mAlbums.contains(title);
};

Album XmlMetaBase::albumFromTitle(const QString& title) const
{
	return mAlbums.value(title);
};

QList<Individual> XmlMetaBase::individuals() const
{
	return mIndividuals.values();
};

bool XmlMetaBase::containsIndividualName(const QString& name) const
{
	return mIndividuals.contains(name);
};

Individual XmlMetaBase::individualFromName(const QString& name) const
{
	return mIndividuals.value(name);
};

QList<Artist> XmlMetaBase::artists() const
{
	return mArtists.values();
};

bool XmlMetaBase::containsArtistName(const QString& name) const
{
	return mArtists.contains(name);
};

Artist XmlMetaBase::artistFromName(const QString& name) const
{
	return mArtists.value(name);
};

QList<Composer> XmlMetaBase::composers() const
{
	return mComposers.values();
};

bool XmlMetaBase::containsComposerName(const QString& name) const
{
	return mComposers.contains(name);
};

Composer XmlMetaBase::composerFromName(const QString& name) const
{
	return mComposers.value(name);
};

QList<Publisher> XmlMetaBase::publishers() const
{
	return mPublishers.values();
};

bool XmlMetaBase::containsPublisherName(const QString& name) const
{
	return mPublishers.contains(name);
};

Publisher XmlMetaBase::publisherFromName(const QString& name) const
{
	return mPublishers.value(name);
};

void XmlMetaBase::addBlock(const UtopiaBlock& block)
{
	updateBlock(block);
};

void XmlMetaBase::updateBlock(const UtopiaBlock& block)
{
	mBlocks[block.id()] = block;
	if( block.type().contains("Album") )
	{
		Album album = (Album&)block;
		for(int i = 0; i < album.albumTitles().count(); i++)
		{
			mAlbums[album.albumTitles().values().at(i)] = album;
		}
	}
	if( block.type().contains("Individual") )
	{
		Individual individual = (Individual&)block;
		for(int i = 0; i < individual.individualNames().count(); i++)
		{
			mIndividuals[individual.individualNames().at(i)] = individual;
		}
	}
	if( block.type().contains("Artist") )
	{
		Artist artist = (Artist&)block;
		for(int i = 0; i < artist.artistNames().count(); i++)
		{
			mArtists[artist.artistNames().at(i)] = artist;
		}
	}
	if( block.type().contains("Composer") )
	{
		Composer composer = (Composer&)block;
		for(int i = 0; i < composer.composerNames().count(); i++)
		{
			mComposers[composer.composerNames().at(i)] = composer;
		}
	}
	if( block.type().contains("Publisher") )
	{
		Publisher publisher = (Publisher&)block;
		for(int i = 0; i < publisher.publisherNames().count(); i++)
		{
			mPublishers[publisher.publisherNames().at(i)] = publisher;
		}
	}
	if( block.type().contains("Staff") )
	{
		Staff staff = (Staff&)block;
		for(int i = 0; i < staff.staffNames().count(); i++)
		{
			mStaff[staff.staffNames().at(i)] = staff;
		}
	}
	if( block.type().contains("Mood") )
	{
		Mood mood = (Mood&)block;
		for(int i = 0; i < mood.moods().count(); i++)
		{
			mMoods[mood.moods().at(i)] = mood;
		}
	}
	if( block.type().contains("Genre") )
	{
		Genre genre = (Genre&)block;
		for(int i = 0; i < genre.genres().count(); i++)
		{
			mGenres[genre.genres().at(i)] = genre;
		}
	}
	if( block.type().contains("Cover") )
	{
		Cover cover = (Cover&)block;
		mCovers[cover.path()] = cover;
	}
	if( block.type().contains("Credit") )
	{
		Credit credit = (Credit&)block;
		mCredits[credit.firstName()] = credit;
		mCredits[credit.lastName()] = credit;
	}
	if( block.type().contains("SongEdition") )
	{
		SongEdition edition = (SongEdition&)block;
		for(int i = 0; i < edition.titles().count(); i++)
		{
			mSongEditions[edition.titles().values().at(i)] = edition;
		}
	}
	if( block.type().contains("SongFile") )
	{
		SongFile file = (SongFile&)block;
		mSongFiles[file.path()] = file;
	}
};

XmlMetaBase* XmlMetaBase::fromFile(const QString& path)
{
	XmlMetaBase *base = new XmlMetaBase;

	QGzipFile file(path);
	file.open(QIODevice::ReadOnly);

	QXmlInputSource source(&file);
	BlockParser handler(base);

	QXmlSimpleReader xmlReader;
	xmlReader.setContentHandler(&handler);
	xmlReader.setErrorHandler(&handler);
	xmlReader.parse(&source);

	file.close();

	return base;
};

void XmlMetaBase::toFile(const QString& path, bool compressed)
{
	QIODevice *file = 0;

	if(compressed)
		file = new QGzipFile(path);
	else
		file = new QFile(path);

	file->open(QIODevice::WriteOnly);

	{

	QXmlStreamWriter writer(file);
	writer.setAutoFormatting(true);

	writer.writeStartElement("utopiadb");

	writer.writeStartElement("settings");

	writer.writeStartElement("setting");
	writer.writeAttribute("key", "next_avaliable_id");
	writer.writeCharacters( QString::number(mNextAvailableID) );
	writer.writeEndElement();

	for(int i = 0; i < mSettings.keys().count(); i++)
	{
		writer.writeStartElement("setting");
		writer.writeAttribute("key", mSettings.keys().at(i));
		writer.writeCharacters( mSettings.value(mSettings.keys().at(i)) );
		writer.writeEndElement();
	}

	writer.writeEndElement();

	for(int i = 0; i < mBlocks.values().count(); i++)
		mBlocks.values().at(i).xmlStream(&writer);

	writer.writeEndElement();

	}

	file->close();
	delete file;
};

uid XmlMetaBase::nextAvailableID()
{
	while( mBlocks.keys().contains(mNextAvailableID) )
		mNextAvailableID++;

	return mNextAvailableID;
};

bool XmlMetaBase::hasID(uid id)
{
	return mBlocks.keys().contains(id);
};

QString XmlMetaBase::getSetting(const QString& key) const
{
	return mSettings.value(key);
};

void XmlMetaBase::setSetting(const QString& key, const QString& value)
{
	if(key == "next_avaliable_id")
	{
		mNextAvailableID = value.trimmed().toInt();
		return;
	}

	mSettings[key] = value;
};
