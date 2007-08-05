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
 * @file songedition.h The SongEdition block class definition
 */

#ifndef __SongEdition_h__
#define __SongEdition_h__

#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>

#include "utopiablock.h"
#include "albumset.h"

namespace Utopia
{

class SongEditionData : public QSharedData
{
public:
	QMap<QString, QString> mTitle;
	QMap<QString, QString> mSubTitle;
	/// jpop, morning musume, karaoke (they get converted to all lower case)
	QStringList mPropertyTags;

	/// List of last 10 times the song was played
	QList<QDateTime> mLastPlayed;

	bool mRandomPlay;

	int mPlayCount;
	int mRating;

	uid mSong;

	QList<AlbumSet> mAlbums;

	// We are not doing the lyrics part right now
	// Take the lyrics and made different versions in addition to languages
	//QMap<QString, Lyrics*> mLyrics;
};

class SongEdition : public UtopiaBlock
{
public:
	SongEdition();

	bool operator==(const SongEdition& block);
	bool operator!=(const SongEdition& block);

	QMap<QString, QString> titles() const;
	bool containsTitle(const QString& title);
	QString title(const QString& lang = CURRENT_LANG) const;

	QMap<QString, QString> subtitles() const;
	bool containsSubtitle(const QString& subtitle);
	QString subtitle(const QString& lang = CURRENT_LANG) const;

	QStringList tags() const;
	bool containsTag(const QString& tag);

	QList<QDateTime> timesPlayed() const;
	QDateTime lastPlayed() const;

	bool randomPlay();

	int playCount();
	int rating();

	uid song();

	QList<AlbumSet> albums() const;
	AlbumSet album(uid album) const;
	AlbumSet album(int track, int disc = 0) const;

	virtual QStringList type() const { return QStringList() << "SongEdition" << UtopiaBlock::type(); };

	void addTitle(const QString& title, const QString& lang = CURRENT_LANG);
	void removeTitle(const QString& title = "", const QString& lang = CURRENT_LANG);
	void clearTitle();

	void addSubtitle(const QString& subtitle, const QString& lang = CURRENT_LANG);
	void removeSubtitle(const QString& subtitle = "", const QString& lang = CURRENT_LANG);
	void clearSubtitle();

	void addTag(const QString& tag);
	void removeTag(const QString& tag);
	void clearTags();

	void addTimePlayed(const QDateTime& time);
	void clearTimesPlayed();

	void setRandomPlay(bool random = true);

	void increasePlayCount();
	void decreasePlayCount();
	void setPlayCount(int count = 0);
	void clearPlayCount();

	void setRating(int rating);

	void addAlbum(const AlbumSet& album);
	void addAlbum(uid album, int track, int disc = 0);
	void removeAlbum(const AlbumSet& album);
	void removeAlbum(uid alum);
	void removeAlbum(int track, int disc = 0);
	void clearAlbums();

	void setSong(uid song);

	virtual void clear();

protected:
	virtual void xmlSegment(QXmlStreamWriter *writer, bool encased = true) const;

private:
	QSharedDataPointer<SongEditionData> d;
};

class SongEditionParser : public UtopiaBlockParser
{
public:
	SongEditionParser() : UtopiaBlockParser() { };

	virtual bool startDocument();
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __SongEdition_h__
