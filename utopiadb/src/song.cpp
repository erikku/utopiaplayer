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
 * @file song.cpp The Song block class implementation
 */

#include "song.h"

using namespace Utopia;

Song::Song() : UtopiaBlock()
{
	d = new SongData;
	clear();
};

bool Song::operator==(const Song& block)
{
	if(d->mGenres != block.d->mGenres || d->mMoods != block.d->mMoods || d->mArtists != block.d->mArtists || d->mPublishers != block.d->mPublishers ||
	d->mComposers != block.d->mComposers || d->mStaff != block.d->mStaff || d->mCredits != block.d->mCredits || d->mSongEditions != block.d->mSongEditions)
		return false;

	return UtopiaBlock::operator==(block);
};

bool Song::operator!=(const Song& block)
{
	return !( Song::operator==(block) );
};

QList<uid> Song::genres() const
{
	return d->mGenres;
};

QList<uid> Song::moods() const
{
	return d->mMoods;
};

QList<uid> Song::artists() const
{
	return d->mArtists;
};

QList<uid> Song::publishers() const
{
	return d->mPublishers;
};

QList<uid> Song::composers() const
{
	return d->mComposers;
};

QList<uid> Song::staff() const
{
	return d->mStaff;
};

QList<uid> Song::credits() const
{
	return d->mCredits;
};

QList<uid> Song::songEditions() const
{
	return d->mSongEditions;
};

void Song::addGenre(uid genre)
{
	if( d->mGenres.contains(genre) )
		return;

	d->mGenres << genre;
};

void Song::removeGenre(uid genre)
{
	int index = d->mGenres.indexOf(genre);
	if( index == -1 )
		return;

	d->mGenres.removeAt(index);
};

void Song::clearGenres()
{
	d->mGenres.clear();
};

void Song::addMood(uid mood)
{
	if( d->mMoods.contains(mood) )
		return;

	d->mMoods << mood;
};

void Song::removeMood(uid mood)
{
	int index = d->mMoods.indexOf(mood);
	if( index == -1 )
		return;

	d->mMoods.removeAt(index);
};

void Song::clearMoods()
{
	d->mMoods.clear();
};

void Song::addArtist(uid artist)
{
	if( d->mArtists.contains(artist) )
		return;

	d->mArtists << artist;
};

void Song::removeArtist(uid artist)
{
	int index = d->mArtists.indexOf(artist);
	if( index == -1 )
		return;

	d->mArtists.removeAt(index);
};

void Song::clearArtists()
{
	d->mArtists.clear();
};

void Song::addPublisher(uid publisher)
{
	if( d->mPublishers.contains(publisher) )
		return;

	d->mPublishers << publisher;
};

void Song::removePublisher(uid publisher)
{
	int index = d->mPublishers.indexOf(publisher);
	if( index == -1 )
		return;

	d->mPublishers.removeAt(index);
};

void Song::clearPublishers()
{
	d->mPublishers.clear();
};

void Song::addComposer(uid composer)
{
	if( d->mComposers.contains(composer) )
		return;

	d->mComposers << composer;
};

void Song::removeComposer(uid composer)
{
	int index = d->mComposers.indexOf(composer);
	if( index == -1 )
		return;

	d->mComposers.removeAt(index);
};

void Song::clearComposers()
{
	d->mComposers.clear();
};

void Song::addStaff(uid staff)
{
	if( d->mStaff.contains(staff) )
		return;

	d->mStaff << staff;
};

void Song::removeStaff(uid staff)
{
	int index = d->mStaff.indexOf(staff);
	if( index == -1 )
		return;

	d->mStaff.removeAt(index);
};

void Song::clearStaff()
{
	d->mStaff.clear();
};

void Song::addCredit(uid credit)
{
	if( d->mCredits.contains(credit) )
		return;

	d->mCredits << credit;
};

void Song::removeCredit(uid credit)
{
	int index = d->mCredits.indexOf(credit);
	if( index == -1 )
		return;

	d->mCredits.removeAt(index);
};

void Song::clearCredits()
{
	d->mCredits.clear();
};

void Song::addSongEdition(uid songedition)
{
	if( d->mSongEditions.contains(songedition) )
		return;

	d->mSongEditions << songedition;
};

void Song::removeSongEdition(uid songedition)
{
	int index = d->mSongEditions.indexOf(songedition);
	if( index == -1 )
		return;

	d->mSongEditions.removeAt(index);
};

void Song::clearSongEditions()
{
	d->mSongEditions.clear();
};

void Song::clear()
{
	d->mGenres.clear();
	d->mMoods.clear();
	d->mArtists.clear();
	d->mPublishers.clear();
	d->mComposers.clear();
	d->mStaff.clear();
	d->mCredits.clear();
	d->mSongEditions.clear();

	UtopiaBlock::clear();
};

QString Song::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<song>\n";

	string += UtopiaBlock::xml(false);

	if(d->mGenres.count())
		string += xmlIDList("genres", d->mGenres);
	if(d->mMoods.count())
		string += xmlIDList("moods", d->mMoods);
	if(d->mArtists.count())
		string += xmlIDList("artists", d->mArtists);
	if(d->mPublishers.count())
		string += xmlIDList("publishers", d->mPublishers);
	if(d->mComposers.count())
		string += xmlIDList("composers", d->mComposers);
	if(d->mStaff.count())
		string += xmlIDList("staff", d->mStaff);
	if(d->mCredits.count())
		string += xmlIDList("credits", d->mCredits);
	if(d->mSongEditions.count())
		string += xmlIDList("songeditions", d->mSongEditions);

	if(encased)
		string += "</song>\n";

	return string;
};

bool SongParser::startDocument()
{
	delete mBlock;
	mBlock = new Song;

	return true;
};

bool SongParser::characters(const QString& ch)
{
	if(mElements.top() == "genres")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Song*)mBlock)->addGenre(id.trimmed().toInt());
		}
		return true;
	}
	if(mElements.top() == "moods")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Song*)mBlock)->addMood(id.trimmed().toInt());
		}
		return true;
	}
	if(mElements.top() == "artists")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Song*)mBlock)->addArtist(id.trimmed().toInt());
		}
		return true;
	}
	if(mElements.top() == "publishers")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Song*)mBlock)->addPublisher(id.trimmed().toInt());
		}
		return true;
	}
	if(mElements.top() == "composers")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Song*)mBlock)->addComposer(id.trimmed().toInt());
		}
		return true;
	}
	if(mElements.top() == "staff")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Song*)mBlock)->addStaff(id.trimmed().toInt());
		}
		return true;
	}
	if(mElements.top() == "credits")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Song*)mBlock)->addCredit(id.trimmed().toInt());
		}
		return true;
	}
	if(mElements.top() == "songeditions")
	{
		QStringList ids = ch.trimmed().split(",");
		foreach(QString id, ids)
		{
			((Song*)mBlock)->addSongEdition(id.trimmed().toInt());
		}
		return true;
	}

	return UtopiaBlockParser::characters(ch);
};
