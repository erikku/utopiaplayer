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
 * @file album.h The Album block class definition
 * @todo Add property tags
 */

#ifndef __Album_h__
#define __Album_h__

#include <QtCore/QMap>
#include <QtCore/QDate>
#include <QtCore/QList>

#include <QtGui/QPixmap>

#include "utopiablock.h"
#include "songset.h"

namespace Utopia
{

class AlbumData : public QSharedData
{
public:
	/// The list of album names in each associated language (lang, name)
	QMap<QString, QString> mTitle;
	/// The variation of the album (like a Mix)
	QMap<QString, QString> mVariation;

	/// The release date for the album
	QDate mReleaseDate;

	/// A list of artists on the album
	QList<uid> mArtists; // class Artist
	/// A list of publishers for the album
	QList<uid> mPublishers; // class Publisher

	/// List of covers (like "Front Cover") 
	QMap<QString, uid> mCovers; // class Cover

	/// Special product codes like mIdentifiers["SKU"] = "SCL-XXX"
	QMap<QString, QString> mIdentifiers;

	/// The format of the album, could be "Album" or "Single" o
	/// "Single V" or whatever floats your boat
	QString mFormat;

	/// A list of all the tracks, sorted by "disc, track"
	QList<SongSet> mTracks;

	/// jpop, morning musume, karaoke (they get converted to all lower case)
	QStringList mPropertyTags;

	/// If the album is a compilation or not
	bool mCompilation;
};

class Album : public UtopiaBlock
{
public:
	Album();
	Album(const QString& name);

	bool operator==(const Album& block);
	bool operator!=(const Album& block);

	QStringList albumLangs() const;
	bool albumContainsLang(const QString& lang = CURRENT_LANG);

	QMap<QString, QString> albumTitles() const;
	bool albumContainsTitle(const QString& title);
	QString albumTitle(const QString& lang = CURRENT_LANG) const;

	QMap<QString, QString> albumVariations() const;
	bool albumContainsVariation(const QString& variation);
	QString albumVariation(const QString& lang = CURRENT_LANG) const;

	QDate releaseDate() const;

	QList<uid> artists() const;
	uid artist(const QString& name, const QString& lang = "");

	QList<uid> publishers()  const;
	uid publisher(const QString& name, const QString& lang = "");

	uid cover(const QString& page = QString("Front Cover"));
	QPixmap coverImage(const QString& page = QString("Front Cover")) const;
	QString coverFilename(const QString& page = QString("Front Cover")) const;

	QMap<QString, QString> identifiers() const;
	QString identifier(const QString& key = QString("SKU")) const;

	QString format() const;

	QList<SongSet> tracks() const;
	SongSet track(uid song) const;
	SongSet track(int track, int disc = 0) const;

	bool isCompilation();

	QStringList tags() const;
	bool containsTag(const QString& tag);

	virtual QStringList type() const { return QStringList() << "Album" << UtopiaBlock::type(); };

	void addAlbumTitle(const QString& title, const QString& lang = CURRENT_LANG);
	void removeAlbumTitle(const QString& title = "", const QString& lang = CURRENT_LANG);
	void clearAlbumTitles();

	void addAlbumVariation(const QString& variation, const QString& lang = CURRENT_LANG);
	void removeAlbumVariation(const QString& variation = "", const QString& lang = CURRENT_LANG);
	void clearAlbumVariations();

	void setReleaseDate(const QDate& date);
	void clearReleaseDate();

	void addArtist(uid artist);
	void removeArtist(uid artist);
	void clearArtists();

	void addPublisher(uid publisher);
	void removePublisher(uid publisher);
	void clearPublishers();

	void addCover(uid cover, const QString& page = QString("Front Cover"));
	void removeCover(uid cover);
	void clearCovers();

	void addIdentifier(const QString& value, const QString& key = QString("SKU"));
	void removeIdentifier(const QString& key);
	void clearIdentifiers();

	void setFormat(const QString& fmt);
	void clearFormat();

	void addTrack(const SongSet& track);
	void addTrack(uid song, int track, int disc = 0);
	void removeTrack(uid song);
	void removeTrack(const SongSet& track);
	void removeTrack(int track, int disc = 0);
	void clearTracks();

	void setCompilation(bool compilation);
	void clearCompilation();

	void addTag(const QString& tag);
	void removeTag(const QString& tag);
	void clearTags();

	virtual void clear();

	virtual QString xml(bool encased = true) const;

private:
	QSharedDataPointer<AlbumData> d;
};

class AlbumParser : public UtopiaBlockParser
{
public:
	AlbumParser() : UtopiaBlockParser() { };

	virtual bool startDocument();
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __Album_h__
