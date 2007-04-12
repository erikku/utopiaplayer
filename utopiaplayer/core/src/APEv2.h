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

	virtual int year() const;
	virtual void setYear(int year);

	virtual int track() const;
	virtual void setTrack(int track);

	virtual QList<QVariant> tag(const QString& key) const;
	virtual QVariant tag(const QString& key, int index) const;

	virtual void setTag(const QString& key, const QString& tag);
	virtual void setTag(const QString& key, const QStringList& tag);

	virtual void clear();
	virtual bool isEmpty();

protected:
	QString stringFromVariant(const QVariant& data) const;
	QStringList stringListFromVariantList(const QList<QVariant>& data) const;

	typedef QList<QVariant> TagData;
	typedef QPair< AdvancedTag::TagType, TagData> TagPair;

	QMap<QString, TagPair> mTags;
};

}; // namespace MetaData

#endif // __APEv2_h__
