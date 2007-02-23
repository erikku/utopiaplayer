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

#ifndef __Series_h__
#define __Series_h__

// Utopia Headers
#include "utopiablock.h"
#include "utopiacommon.h"

// Qt Headers
#include <QtCore/QStringList>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>

namespace Utopia
{

class Series : public UtopiaBlock
{
	Q_OBJECT

public:
	Series(QObject* parent = 0);
	Series(const MangaSeries& series, QObject* parent = 0);
	~Series();

	Series& operator=(const Series& series);
	bool operator==(const Series& series);
	bool operator!=(const Series& series);

	QString abbrName();

	QMap<QString, QString> title();
	QString title(const QString& locale = QLocale::system().language());

	QList<MangaPublisher*> publishers();
	QList<MangaPublisher*> mangaka();

	AgeRating ageRating();
	Visibility visibility();

	int favorRating();

	QStringList ageDescriptors();
	QStringList genres();

public slots:
	void setAbbrName(const QString& name);

	void addTitle(const QString& title, const QString& lang = CURRENT_LANG);
	void removeTitle(const QString& title = "", const QString& lang = CURRENT_LANG);
	void clearTitles();

	void addPublisher(const QString& publisher);
	void addPublisher(MangaPublisher* publisher);
	void removePublisher(MangaPublisher* publisher);
	void removePublisher(const QString& publisher);
	void clearPublishers();

	void addMangaka(const QString& mangaka);
	void addMangaka(MangaMangaka* mangaka);
	void removeMangaka(MangaMangaka* mangaka);
	void removeMangaka(const QString& mangaka);
	void clearMangaka();

	void setAgeRating(AgeRating rating);
	void setVisibility(Visibility visibility);

	void setFavorRating(int rating);

	void addAgeDescriptor(const QString& descriptor);
	void addAgeDescriptors(const QStringList& descriptors);
	void removeAgeDescriptor(const QString& descriptor);
	void removeAgeDescriptors(const QStringList& descriptors);
	void clearAgeDescriptors();

	void addGenre(const QString& genre);
	void addGenres(const QStringList& genres);
	void removeGenre(const QString& genre);
	void removeGenres(const QStringList& genres);
	void clearGenres();

	void clear();

private:
	QString mAbbrName;
	QMap<QString, QString> mTitle;

	QList<MangaPublisher*> mPublishers;
	QList<MangaMangaka*> mMangaka;

	AgeRating mAgeRating;
	Visibility mVisibility;

	int mFavorRating;

	QStringList mAgeDescriptors;
	QStringList mGenres;
};

}; // namespace Utopia

#endif // __Series_h__
