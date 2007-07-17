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

class Cuesheet;

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
		MultipleEntries = 0x400,
		CuesheetTag = 0x800
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
	virtual int totalTracks() const;
	virtual void setTotalTracks(int total);

	virtual int disc() const;
	virtual void setDisc(int disc);

	virtual int totalDiscs() const;
	virtual void setTotalDiscs(int total);

	virtual QString composer() const;
	virtual void setComposer(const QString& composer);

	virtual QStringList composers() const;
	virtual void setComposers(const QStringList& composers);

	virtual QString performer() const;
	virtual void setPerformer(const QString& performer);

	virtual QStringList performers() const;
	virtual void setPerformers(const QStringList& performers);

	virtual QString albumArtist() const;
	virtual void setAlbumArtist(const QString& albumArtist);

	virtual QStringList albumArtists() const;
	virtual void setAlbumArtists(const QStringList& albumArtists);

	virtual QDate date() const;
	virtual void setDate(const QDate& date);

	virtual float trackGain() const;
	virtual void setTrackGain(float gain);

	virtual float trackPeak() const;
	virtual void setTrackPeak(float peak);

	virtual float albumGain() const;
	virtual void setAlbumGain(float gain);

	virtual float albumPeak() const;
	virtual void setAlbumPeak(float peak);

	virtual QPixmap cover() const;
	virtual void setCover(const QPixmap& cover);

	  ////////////////////////////////////////////////////////
	 // Custom tag editing funtions bellow                 //
	////////////////////////////////////////////////////////

	virtual bool canSupportCustomTags();
	virtual bool canSupportMultipleEntries();

	virtual int tagCount();
	virtual QStringList tagKeys() const;
	virtual QString tagKey(int index) const;

	virtual bool containsTag(const QString& key);
	virtual int tagCount(const QString& key) const;
	virtual AdvancedTag::TagType tagType(const QString& key) const;

	virtual QList<QVariant> tag(const QString& key) const;
	virtual QVariant tag(const QString& key, int index) const;

	virtual bool keysMatch(const QString& key1, const QString& key2);

	virtual void addTag(const QString& key, const QUrl& tag);
	virtual void addTag(const QString& key, const QString& tag);
	virtual void addTag(const QString& key, const QByteArray& tag);
	virtual void addTag(const QString& key, const QList<QUrl>& tag);
	virtual void addTag(const QString& key, const QStringList& tag);
	virtual void addTag(const QString& key, const QList<QByteArray>& tag);
	virtual void addTag(const QString& key, const QList<QVariant>& tag, TagType type);

	virtual void setTag(const QString& key, const QUrl& tag);
	virtual void setTag(const QString& key, const QString& tag);
	virtual void setTag(const QString& key, const QByteArray& tag);
	virtual void setTag(const QString& key, const QList<QUrl>& tag);
	virtual void setTag(const QString& key, const QStringList& tag);
	virtual void setTag(const QString& key, const QList<QByteArray>& tag);
	virtual void setTag(const QString& key, const QList<QVariant>& tag, TagType type);

	virtual void clearTag(const QString& key);
	virtual void clearTag(const QString& key, int index);

	// Cuesheet Functions
	virtual Cuesheet* cuesheet();
	virtual void setCuesheet(Cuesheet *sheet);
	virtual void setCuesheet(const QString& text, bool updateSheet = true);
	virtual void removeCuesheet();

protected:
	QString stringFromVariant(const QVariant& data) const;
	QStringList stringListFromVariantList(const QList<QVariant>& data) const;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(AdvancedTag::TagFeatures)

}; // namespace MetaData

#endif // __AdvancedTag_h__
