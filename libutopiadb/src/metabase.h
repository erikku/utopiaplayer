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

#ifndef __MetaBase_h__
#define __MetaBase_h__

#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QObject>

#include "utopiablock.h"
#include "album.h"
#include "artist.h"
#include "composer.h"
#include "publisher.h"
#include "staff.h"
#include "mood.h"
#include "genre.h"
#include "cover.h"
#include "credit.h"
#include "song.h"
#include "songedition.h"
#include "songfile.h"

namespace Utopia
{

class MetaBase : public QObject
{
	Q_OBJECT

public:
	MetaBase(QObject *parent = 0);

	virtual QList<UtopiaBlock> blocks() const = 0;

	virtual QList<Album> albums() const = 0;
	virtual bool containsAlbumTitle(const QString& title) const = 0;
	virtual Album albumFromTitle(const QString& title) const = 0;

	virtual QList<Individual> individuals() const = 0;
	virtual bool containsIndividualName(const QString& name) const = 0;
	virtual Individual individualFromName(const QString& name) const = 0;

	virtual QList<Artist> artists() const = 0;
	virtual bool containsArtistName(const QString& name) const = 0;
	virtual Artist artistFromName(const QString& name) const = 0;

	virtual QList<Composer> composers() const = 0;
	virtual bool containsComposerName(const QString& name) const = 0;
	virtual Composer composerFromName(const QString& name) const = 0;

	virtual QList<Publisher> publishers() const = 0;
	virtual bool containsPublisherName(const QString& name) const = 0;
	virtual Publisher publisherFromName(const QString& name) const = 0;

	virtual uid nextAvailableID() = 0;
	virtual bool hasID(uid id) = 0;

	virtual QString getSetting(const QString& key) const = 0;

public slots:
	virtual void setSetting(const QString& key, const QString& value) = 0;
	virtual void addBlock(const UtopiaBlock& block) = 0;
	virtual void updateBlock(const UtopiaBlock& block) = 0;
};

}; // namespace Utopia

#endif // __MetaBase_h__
