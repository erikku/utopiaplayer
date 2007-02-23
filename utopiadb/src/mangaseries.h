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

#ifndef __MangaSeries_h__
#define __MangaSeries_h__

// Utopia Headers
#include "series.h"

// Utopia Classes
class MangaPublisher;
class MangaMangaka;
class MangaVolume;
class MediaRelationship;

namespace Utopia
{

class MangaSeries : public Series
{
	Q_OBJECT

public:
	MangaSeries(QObject* parent = 0);
	MangaSeries(const MangaSeries& series, QObject* parent = 0);
	~MangaSeries();

	MangaSeries& operator=(const MangaSeries& series);
	bool operator==(const MangaSeries& series);
	bool operator!=(const MangaSeries& series);

	MangaVolume* volume(IssueIdent issue);
	MangaVolume* volume(const QString& volume);
	QMap<IssueIdent, MangaVolume*> volumes();

	MediaRelationship* mediaRelationship(Game* game);
	MediaRelationship* mediaRelationship(AnimeSeries* anime);
	MediaRelationship* mediaRelationship(const QString& related_title);
	QList<MediaRelationship*> mediaRelationships();

public slots:
	void addVolume(IssueIdent issue, const QString& volume);
	void addVolume(IssueIdent issue, MangaVolume* volume);
	void removeVolume(IssueIdent issue);
	void removeVolume(MangaVolume* volume);
	void removeVolume(const QString& volume);
	void clearVolumes();

	void addMediaRelationship(const QString& relationship);
	void addMediaRelationship(MediaRelationship* relationship);
	void removeMediaRelationship(MediaRelationship* relationship);
	void removeMediaRelationship(const QString& relationship);
	void clearMediaRelationships();

	void clear();

private:
	QMap<IssueIdent, MangaVolume*> mVolumes;
	QList<MediaRelationship*> mMediaRelationships;
};

}; // namespace Utopia

#endif // __MangaSeries_h__
