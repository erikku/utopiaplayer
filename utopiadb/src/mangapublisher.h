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

/**
 * @file mangapublisher.h The manga publisher class definition
 */

#ifndef __MangaPublisher_h__
#define __MangaPublisher_h__

// UtopiaDB Headers
#include "mangacommon.h"
#include "utopiablock.h"

// Qt Headers
#include <QtCore/QStringList>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>

namespace Utopia
{

/**
 * @brief A class to store a managa publisher
 */
class MangaPublisher : public UtopiaBlock
{
	Q_OBJECT

public:
	MangaPublisher(QObject* parent = 0);
	MangaPublisher(const MangaPublisher& publisher, QObject* parent = 0);

	MangaPublisher& operator=(const MangaPublisher& publisher);
	bool operator==(const MangaPublisher& publisher);
	bool operator!=(const MangaPublisher& publisher);
	
	QMap<QString, QString> publisherNames();
	QString publisherName(const QString& lang = QLocale::system().language());

public slots:
	void addPublisherName(const QString& name, const QString& lang = CURRENT_LANG);
	void removePublisherName(const QString& name = "", const QString& lang = CURRENT_LANG);
	void clearPublisherNames();
	
	void clear();

protected:
	QMap<QString, QString> mPublisherName;
};

}; // namespace Utopia

#endif // __MangaPublisher_h__
