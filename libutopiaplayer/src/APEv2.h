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

#ifndef __APEv2_h__
#define __APEv2_h__

#include "AdvancedTag.h"

#include <QtCore/QMap>
#include <QtCore/QPair>

namespace MetaData
{

class APEv2 : public AdvancedTag
{
	Q_OBJECT

public:
	APEv2(QObject *parent = 0);
	APEv2(const QString& path);

	virtual QFlags<AdvancedTag::TagFeatures> features();

	// QStringList copies of the basic tags //
	virtual QStringList titles() const;
	virtual void setTitles(const QStringList& titles);

	virtual QStringList artists() const;
	virtual void setArtists(const QStringList& artists);

	virtual QStringList albums() const;
	virtual void setAlbums(const QStringList& albums);

	virtual QStringList comments() const;
	virtual void setComments(const QStringList& comments);

	virtual QStringList genres() const;
	virtual void setGenres(const QStringList& genres);

	// Basic tags that are not defined in AdvancedTag //
	virtual int year() const;
	virtual void setYear(int year);

	virtual int track() const;
	virtual void setTrack(int track);

	virtual void clear();
	virtual bool isEmpty();

	virtual QString encoding() const;
	virtual QString defaultEncoding() const;

	virtual Tag* duplicate();

	virtual qint64 size();
	virtual QByteArray tagData() const;

	// File operations //
	virtual void removeTag(const QString& path);
	virtual qint64 position(const QString& path);
	virtual bool fileContainsTag(const QString& path);
	virtual bool conformsToSpec(const QString& path);

	virtual bool read(const QString& path, const QString& encoding = QString());
	virtual bool write(const QString& path, const QString& encoding = QString());

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

	virtual int tagCount();
	virtual QStringList tagKeys() const;
	virtual QString tagKey(int index) const;

	virtual bool containsTag(const QString& key);
	virtual int tagCount(const QString& key) const;
	virtual AdvancedTag::TagType tagType(const QString& key) const;

	virtual QList<QVariant> tag(const QString& key) const;
	virtual QVariant tag(const QString& key, int index) const;

	virtual void addTag(const QString& key, const QList<QVariant>& tag, TagType type);
	virtual void setTag(const QString& key, const QList<QVariant>& tag, TagType type);

	virtual void clearTag(const QString& key);
	virtual void clearTag(const QString& key, int index);

	virtual MetaData::Cuesheet* cuesheet();
	virtual void setCuesheet(MetaData::Cuesheet *sheet);
	virtual void setCuesheet(const QString& text, bool updateSheet = true);
	virtual void removeCuesheet();

	virtual QString type() const;

protected:
	void setupKeyNames();

	typedef QList<QVariant> TagData;
	typedef QPair< AdvancedTag::TagType, TagData > TagPair;

	QMap<QString, TagPair> mTags;

	QString mCurrentEncoding;
	MetaData::Cuesheet *mCuesheet;
};

}; // namespace MetaData

#endif // __APEv2_h__
