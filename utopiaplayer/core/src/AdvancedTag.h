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

#ifndef __AdvancedTag_h__
#define __AdvancedTag_h__

#include "Tag.h"

#include <QtCore/QUrl>
#include <QtCore/QDate>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QByteArray>
#include <QtCore/QStringList>
#include <QtGui/QPixmap>

namespace MetaData
{

/// @TODO Make default functions for all those features you can leave out (which is just about everything)
class AdvancedTag : public Tag
{
	Q_OBJECT
	Q_ENUMS(TagType)

public:
	AdvancedTag(QObject *parent = 0) : Tag(parent) { };

	typedef enum TagType
	{
		String,
		Binary,
		URL,
		Unknown
	};
	
	typedef enum TagFeature
	{
		Disc = 0x001,
		TotalDiscs = 0x002,
		TotalTracks = 0x004,
		Composer = 0x008,
		Performer = 0x010,
		AlbumArtist = 0x020,
		Date = 0x040,
		ReplayGain = 0x080,
		EmbeddedCoverArt = 0x100,
		CustomTags = 0x200,
		MultipleEntries = 0x400
	};

	Q_DECLARE_FLAGS(TagFeatures, TagFeature)

	virtual bool hasAdvancedFeatures() { return true; };

	virtual QFlags<AdvancedTag::TagFeatures> features() = 0;
	virtual bool hasFeature(AdvancedTag::TagFeature feature);

	// Re-definition of the basic tag functions for convenience
	// They use the first entry from the multiple string functions bellow
	virtual QString title() const;
	virtual void setTitle(const QString& title);

	virtual QString artist() const;
	virtual void setArtist(const QString& artist);

	virtual QString album() const;
	virtual void setAlbum(const QString& album);

	virtual QString comment() const;
	virtual void setComment(const QString& comment);

	virtual QString genre() const;
	virtual void setGenre(const QString& genre);
	
	// QStringList copies of the basic tags //
	virtual QStringList titles() const = 0;
	virtual void setTitles(const QStringList& titles) = 0;

	virtual QStringList artists() const = 0;
	virtual void setArtists(const QStringList& artists) = 0;

	virtual QStringList albums() const = 0;
	virtual void setAlbums(const QStringList& albums) = 0;

	virtual QStringList comments() const = 0;
	virtual void setComments(const QStringList& comments) = 0;

	virtual QStringList genres() const = 0;
	virtual void setGenres(const QStringList& genres) = 0;

	// Advanced tags //
	virtual int totalTracks() const = 0;
	virtual void setTotalTracks(int total) = 0;

	virtual int disc() const = 0;
	virtual void setDisc(int disc) = 0;

	virtual int totalDiscs() const = 0;
	virtual void setTotalDiscs(int total) = 0;

	virtual QString composer() const;
	virtual void setComposer(const QString& composer);

	virtual QStringList composers() const = 0;
	virtual void setComposers(const QStringList& composers) = 0;

	virtual QString performer() const;
	virtual void setPerformer(const QString& performer);

	virtual QStringList performers() const = 0;
	virtual void setPerformers(const QStringList& performers) = 0;

	virtual QString albumArtist() const;
	virtual void setAlbumArtist(const QString& albumArtist);

	virtual QStringList albumArtists() const = 0;
	virtual void setAlbumArtists(const QStringList& albumArtists) = 0;

	virtual QDate date() const = 0;
	virtual void setDate(const QDate& date) = 0;

	virtual float trackGain() const = 0;
	virtual void setTrackGain(float gain) = 0;

	virtual float trackPeak() const = 0;
	virtual void setTrackPeak(float peak) = 0;

	virtual float albumGain() const = 0;
	virtual void setAlbumGain(float gain) = 0;

	virtual float albumPeak() const = 0;
	virtual void setAlbumPeak(float peak) = 0;

	virtual QPixmap cover() const = 0;
	virtual void setCover(const QPixmap& cover) = 0;

	  ////////////////////////////////////////////////////////
	 // Custom tag editing funtions bellow                 //
	////////////////////////////////////////////////////////

	virtual bool canSupportCustomTags();
	virtual bool canSupportMultipleEntries();

	virtual int tagCount() = 0;
	virtual QStringList tagKeys() const = 0;
	virtual QString tagKey(int index) const = 0;

	virtual bool containsTag(const QString& key) = 0;
	virtual int tagCount(const QString& key) const = 0;
	virtual AdvancedTag::TagType tagType(const QString& key) const = 0;

	virtual QList<QVariant> tag(const QString& key) const = 0;
	virtual QVariant tag(const QString& key, int index) const = 0;

	virtual bool keysMatch(const QString& key1, const QString& key2);

	virtual void addTag(const QString& key, const QUrl& tag) = 0;
	virtual void addTag(const QString& key, const QString& tag) = 0;
	virtual void addTag(const QString& key, const QByteArray& tag) = 0;
	virtual void addTag(const QString& key, const QList<QUrl>& tag) = 0;
	virtual void addTag(const QString& key, const QStringList& tag) = 0;
	virtual void addTag(const QString& key, const QList<QByteArray>& tag) = 0;
	virtual void addTag(const QString& key, const QList<QVariant>& tag, TagType type) = 0;

	virtual void setTag(const QString& key, const QUrl& tag) = 0;
	virtual void setTag(const QString& key, const QString& tag) = 0;
	virtual void setTag(const QString& key, const QByteArray& tag) = 0;
	virtual void setTag(const QString& key, const QList<QUrl>& tag) = 0;
	virtual void setTag(const QString& key, const QStringList& tag) = 0;
	virtual void setTag(const QString& key, const QList<QByteArray>& tag) = 0;
	virtual void setTag(const QString& key, const QList<QVariant>& tag, TagType type) = 0;

	virtual void clearTag(const QString& key) = 0;
	virtual void clearTag(const QString& key, int index) = 0;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(AdvancedTag::TagFeatures)

}; // namespace MetaData

#endif // __AdvancedTag_h__
