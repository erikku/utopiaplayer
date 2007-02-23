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

#ifndef __XmlMetaBase_h__
#define __XmlMetaBase_h__

#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QObject>

#include "metabase.h"

namespace Utopia
{

class XmlMetaBase : public MetaBase
{
	Q_OBJECT

public:
	XmlMetaBase(QObject *parent = 0);

	virtual QList<UtopiaBlock> blocks() const;

	virtual QList<Album> albums() const;
	virtual bool containsAlbumTitle(const QString& title) const;
	virtual Album albumFromTitle(const QString& title) const;

	virtual QList<Individual> individuals() const;
	virtual bool containsIndividualName(const QString& name) const;
	virtual Individual individualFromName(const QString& name) const;

	virtual QList<Artist> artists() const;
	virtual bool containsArtistName(const QString& name) const;
	virtual Artist artistFromName(const QString& name) const;

	virtual QList<Composer> composers() const;
	virtual bool containsComposerName(const QString& name) const;
	virtual Composer composerFromName(const QString& name) const;

	virtual QList<Publisher> publishers() const;
	virtual bool containsPublisherName(const QString& name) const;
	virtual Publisher publisherFromName(const QString& name) const;

	static XmlMetaBase* fromFile(const QString& path);
	void toFile(const QString& path, bool compressed = true);

	virtual uid nextAvailableID();
	virtual bool hasID(uid id);

	virtual QString getSetting(const QString& key) const;

public slots:
	virtual void setSetting(const QString& key, const QString& value);
	virtual void addBlock(const UtopiaBlock& block);
	virtual void updateBlock(const UtopiaBlock& block);

protected:
	uid mNextAvailableID;

	QMap<QString, QString> mSettings;
	QHash<uid, UtopiaBlock> mBlocks;

	QHash<QString, Album> mAlbums;
	QHash<QString, Individual> mIndividuals;
	QHash<QString, Artist> mArtists;
	QHash<QString, Composer> mComposers;
	QHash<QString, Publisher> mPublishers;
	QHash<QString, Staff> mStaff;
	QHash<QString, Mood> mMoods;
	QHash<QString, Genre> mGenres;
	QHash<QString, Cover> mCovers;
	QHash<QString, Credit> mCredits;
	QHash<QString, SongEdition> mSongEditions;
	QHash<QString, SongFile> mSongFiles;
};

}; // namespace Utopia

#endif // __XmlMetaBase_h__
