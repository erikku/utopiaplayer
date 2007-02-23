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
 * @file song.h The Song block class definition
 */

#ifndef __Song_h__
#define __Song_h__

#include "utopiablock.h"

#include <QtCore/QList>

namespace Utopia
{

class SongData : public QSharedData
{
public:
	QList<uid> mGenres;
	QList<uid> mMoods;

	QList<uid> mArtists;
	QList<uid> mPublishers;
	QList<uid> mComposers;
	QList<uid> mStaff;

	QList<uid> mCredits;
	QList<uid> mSongEditions;
};

class Song : public UtopiaBlock
{
public:
	Song();

	bool operator==(const Song& block);
	bool operator!=(const Song& block);

	QList<uid> genres() const;
	QList<uid> moods() const;

	QList<uid> artists() const;
	QList<uid> publishers() const;
	QList<uid> composers() const;
	QList<uid> staff() const;

	QList<uid> credits() const;
	QList<uid> songEditions() const;

	void addGenre(uid genre);
	void removeGenre(uid genre);
	void clearGenres();

	void addMood(uid mood);
	void removeMood(uid mood);
	void clearMoods();

	void addArtist(uid artist);
	void removeArtist(uid artist);
	void clearArtists();

	void addPublisher(uid publisher);
	void removePublisher(uid publisher);
	void clearPublishers();

	void addComposer(uid composer);
	void removeComposer(uid composer);
	void clearComposers();

	void addStaff(uid staff);
	void removeStaff(uid staff);
	void clearStaff();

	void addCredit(uid credit);
	void removeCredit(uid credit);
	void clearCredits();

	void addSongEdition(uid songedition);
	void removeSongEdition(uid songedition);
	void clearSongEditions();

	virtual void clear();

	virtual QStringList type() const { return QStringList() << "Song" << UtopiaBlock::type(); };

	virtual QString xml(bool encased = true) const;

private:
	QSharedDataPointer<SongData> d;
};

class SongParser : public UtopiaBlockParser
{
public:
	SongParser() : UtopiaBlockParser() { };

	virtual bool startDocument();
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __Song_h__

