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

#ifndef __Cuesheet_h__
#define __Cuesheet_h__

#include "AdvancedTag.h"

namespace MetaData
{

/*
REM GENRE J-pop
REM DATE 2006
PERFORMER "モーニング娘。"
TITLE "歩いてる"
REM REPLAYGAIN_ALBUM_GAIN -9.26 dB
REM REPLAYGAIN_ALBUM_PEAK 1.000000
FILE "NEW CINEMA    - Messenger.wav" WAVE
  TRACK 01 AUDIO
    TITLE "歩いてる"
    REM REPLAYGAIN_TRACK_GAIN -9.44 dB
    REM REPLAYGAIN_TRACK_PEAK 1.000000
    INDEX 01 00:00:00
  TRACK 02 AUDIO
    TITLE "踊れ!モーニングカレー"
    REM REPLAYGAIN_TRACK_GAIN -10.12 dB
    REM REPLAYGAIN_TRACK_PEAK 1.000000
    INDEX 00 04:55:00
    INDEX 01 04:56:61
  TRACK 03 AUDIO
    TITLE "歩いてる(Instrumental)"
    REM REPLAYGAIN_TRACK_GAIN -5.77 dB
    REM REPLAYGAIN_TRACK_PEAK 1.000000
    INDEX 00 08:44:55
    INDEX 01 08:46:73
*/

class CuesheetTrack : public AdvancedTag
{
	Q_OBJECT

public:
	virtual QFlags<AdvancedTag::TagFeatures> features();

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

	virtual void removeTag(const QString& path);
	virtual qint64 position(const QString& path);
	virtual bool fileContainsTag(const QString& path);
	virtual bool conformsToSpec(const QString& path);

	virtual bool read(const QString& path, const QString& encoding = QString());
	virtual bool write(const QString& path, const QString& encoding = QString());

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

	virtual QString type() const;

private:
	typedef QList<QVariant> TagData;
	typedef QPair< AdvancedTag::TagType, TagData > TagPair;

	QMap<QString, TagPair> mTags;
};

class Cuesheet : public CuesheetTrack
{
	Q_OBJECT

public:
	int trackCount();
	CuesheetTrack* trackTag(int track);
	void addTrack(CuesheetTrack *track);
	void setTrack(int track, CuesheetTrack *track);
	void removeTrack(CuesheetTrack *track);
	void removeTrack(int track);

private:
	QList<CuesheetTrack*> mTracks;
};


}; // namespace MetaData

#endif // __Cuesheet_h__
