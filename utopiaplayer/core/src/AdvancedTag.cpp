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

#include "AdvancedTag.h"
#include "Cuesheet.h"

using namespace MetaData;

bool AdvancedTag::hasFeature(AdvancedTag::TagFeature feature)
{
	return features().testFlag(feature);
};

QString AdvancedTag::title() const
{
	if(titles().count())
		return titles().first();

	return QString();
};

void AdvancedTag::setTitle(const QString& title)
{
	setTitles(QStringList() << title);
};

QString AdvancedTag::artist() const
{
	if(artists().count())
		return artists().first();

	return QString();
};

void AdvancedTag::setArtist(const QString& artist)
{
	setArtists(QStringList() << artist);
};

QString AdvancedTag::album() const
{
	if(albums().count())
		return albums().first();

	return QString();
};

void AdvancedTag::setAlbum(const QString& album)
{
	setAlbums(QStringList() << album);
};

QString AdvancedTag::comment() const
{
	if(comments().count())
		return comments().first();

	return QString();
};

void AdvancedTag::setComment(const QString& comment)
{
	setComments(QStringList() << comment);
};

QString AdvancedTag::genre() const
{
	if(genres().count())
		return genres().first();

	return QString();
};

void AdvancedTag::setGenre(const QString& genre)
{
	setGenres(QStringList() << genre);
};

int AdvancedTag::totalTracks() const
{
	return 0;
};

void AdvancedTag::setTotalTracks(int total)
{
	Q_UNUSED(total);
};

int AdvancedTag::disc() const
{
	return 0;
};

void AdvancedTag::setDisc(int disc)
{
	Q_UNUSED(disc);
};

int AdvancedTag::totalDiscs() const
{
	return 0;
};

void AdvancedTag::setTotalDiscs(int total)
{
	Q_UNUSED(total);
};

QString AdvancedTag::composer() const
{
	if(composers().count())
		return composers().first();

	return QString();
};

void AdvancedTag::setComposer(const QString& composer)
{
	setComposers(QStringList() << composer);
};

QStringList AdvancedTag::composers() const
{
	return QStringList();
};

void AdvancedTag::setComposers(const QStringList& composers)
{
	Q_UNUSED(composers);
};

QString AdvancedTag::performer() const
{
	if(performers().count())
		return performers().first();

	return QString();
};

void AdvancedTag::setPerformer(const QString& performer)
{
	setPerformers(QStringList() << performer);
};

QStringList AdvancedTag::performers() const
{
	return QStringList();
};

void AdvancedTag::setPerformers(const QStringList& performers)
{
	Q_UNUSED(performers);
};

QString AdvancedTag::albumArtist() const
{
	if(albumArtists().count())
		return albumArtists().first();

	return QString();
};

void AdvancedTag::setAlbumArtist(const QString& albumArtist)
{
	setAlbumArtists(QStringList() << albumArtist);
};

QStringList AdvancedTag::albumArtists() const
{
	return QStringList();
};

void AdvancedTag::setAlbumArtists(const QStringList& albumArtists)
{
	Q_UNUSED(albumArtists);
};

QDate AdvancedTag::date() const
{
	return QDate();
};

void AdvancedTag::setDate(const QDate& date)
{
	Q_UNUSED(date);
};

float AdvancedTag::trackGain() const
{
	return 0.0f;
};

void AdvancedTag::setTrackGain(float gain)
{
	Q_UNUSED(gain);
};

float AdvancedTag::trackPeak() const
{
	return 1.0f;
};

void AdvancedTag::setTrackPeak(float peak)
{
	Q_UNUSED(peak);
};

float AdvancedTag::albumGain() const
{
	return 0.0f;
};

void AdvancedTag::setAlbumGain(float gain)
{
	Q_UNUSED(gain);
};

float AdvancedTag::albumPeak() const
{
	return 1.0f;
};

void AdvancedTag::setAlbumPeak(float peak)
{
	Q_UNUSED(peak);
};

QPixmap AdvancedTag::cover() const
{
	return QPixmap();
};

void AdvancedTag::setCover(const QPixmap& cover)
{
	Q_UNUSED(cover);
};

bool AdvancedTag::canSupportCustomTags()
{
	return hasFeature(CustomTags);
};

bool AdvancedTag::canSupportMultipleEntries()
{
	return hasFeature(MultipleEntries);
};

int AdvancedTag::tagCount()
{
	return 0;
};

QStringList AdvancedTag::tagKeys() const
{
	return QStringList();
};

QString AdvancedTag::tagKey(int index) const
{
	Q_UNUSED(index);
	return QString();
};

bool AdvancedTag::containsTag(const QString& key)
{
	Q_UNUSED(key);
	return false;
};

int AdvancedTag::tagCount(const QString& key) const
{
	Q_UNUSED(key);
	return 0;
};

AdvancedTag::TagType AdvancedTag::tagType(const QString& key) const
{
	Q_UNUSED(key);
	return Unknown;
};

QList<QVariant> AdvancedTag::tag(const QString& key) const
{
	Q_UNUSED(key);
	return QList<QVariant>();
};

QVariant AdvancedTag::tag(const QString& key, int index) const
{
	Q_UNUSED(key);
	Q_UNUSED(index);
	return QVariant();
};

bool AdvancedTag::keysMatch(const QString& key1, const QString& key2)
{
	return (key1.compare(key2, Qt::CaseInsensitive) == 0);
};

void AdvancedTag::addTag(const QString& key, const QUrl& tag)
{
	addTag(key, QList<QVariant>() << tag, URL);
};

void AdvancedTag::addTag(const QString& key, const QString& tag)
{
	addTag(key, QList<QVariant>() << tag, String);
};

void AdvancedTag::addTag(const QString& key, const QByteArray& tag)
{
	addTag(key, QList<QVariant>() << tag, Binary);
};

void AdvancedTag::addTag(const QString& key, const QList<QUrl>& tag)
{
	QList<QVariant> list;
	foreach(QUrl url, tag)
		list << url;

	addTag(key, list, URL);
};

void AdvancedTag::addTag(const QString& key, const QStringList& tag)
{
	QList<QVariant> list;
	foreach(QString string, tag)
		list << string;

	addTag(key, list, String);
};

void AdvancedTag::addTag(const QString& key, const QList<QByteArray>& tag)
{
	QList<QVariant> list;
	foreach(QByteArray data, tag)
		list << data;

	addTag(key, list, Binary);
};

void AdvancedTag::addTag(const QString& key, const QList<QVariant>& tag, TagType type)
{
	Q_UNUSED(key);
	Q_UNUSED(tag);
	Q_UNUSED(type);
};

void AdvancedTag::setTag(const QString& key, const QUrl& tag)
{
	setTag(key, QList<QVariant>() << tag, URL);
};

void AdvancedTag::setTag(const QString& key, const QString& tag)
{
	setTag(key, QList<QVariant>() << tag, String);
};

void AdvancedTag::setTag(const QString& key, const QByteArray& tag)
{
	setTag(key, QList<QVariant>() << tag, Binary);
};

void AdvancedTag::setTag(const QString& key, const QList<QUrl>& tag)
{
	QList<QVariant> list;
	foreach(QUrl url, tag)
		list << url;

	setTag(key, list, URL);
};

void AdvancedTag::setTag(const QString& key, const QStringList& tag)
{
	QList<QVariant> list;
	foreach(QString string, tag)
		list << string;

	setTag(key, list, String);
};

void AdvancedTag::setTag(const QString& key, const QList<QByteArray>& tag)
{
	QList<QVariant> list;
	foreach(QByteArray data, tag)
		list << data;

	setTag(key, list, Binary);
};

void AdvancedTag::setTag(const QString& key, const QList<QVariant>& tag, TagType type)
{
	Q_UNUSED(key);
	Q_UNUSED(tag);
	Q_UNUSED(type);
};

void AdvancedTag::clearTag(const QString& key)
{
	Q_UNUSED(key);
};

void AdvancedTag::clearTag(const QString& key, int index)
{
	Q_UNUSED(key);
	Q_UNUSED(index);
};

Cuesheet* AdvancedTag::cuesheet()
{
	return 0;
};

void AdvancedTag::setCuesheet(Cuesheet *sheet)
{
	delete sheet;
};

void AdvancedTag::setCuesheet(const QString& text, bool updateSheet)
{
	Q_UNUSED(text);
	Q_UNUSED(updateSheet);
};

void AdvancedTag::removeCuesheet()
{
};

QString AdvancedTag::stringFromVariant(const QVariant& data) const
{
	return fromEncoding(encoding(), data.toByteArray().data(), data.toByteArray().size());
};

QStringList AdvancedTag::stringListFromVariantList(const QList<QVariant>& data) const
{
	QStringList final;

	foreach(QVariant entry, data)
		final << fromEncoding(encoding(), entry.toByteArray().data(), entry.toByteArray().size());

	return final;
};
