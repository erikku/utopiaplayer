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
 * @file artist.h The Artist block class definition
 */

#ifndef __Artist_h__
#define __Artist_h__

#include "individual.h"

namespace Utopia
{

class Artist : public Individual
{
public:
	Artist();
	Artist(const QString& name);

	QString artistName(const QString& lang = CURRENT_LANG) const;
	QMap<QString, QString> artistNamePairs() const;
	QList<QString> artistNames() const;
	QList<QString> artistLangs() const;
	bool artistContainsName(const QString& name);
	bool artistContainsLang(const QString& lang = CURRENT_LANG);

	virtual QStringList type() const { return QStringList() << "Artist" << Individual::type(); };

	void addArtistName(const QString& name, const QString& lang = CURRENT_LANG);
	void removeArtistName(const QString& name = "", const QString& lang = CURRENT_LANG);
	void clearArtistNames();

protected:
	virtual void xmlSegment(QXmlStreamWriter *writer, bool encased = true) const;
};

class ArtistParser : public IndividualParser
{
public:
	ArtistParser() : IndividualParser() { };

	virtual bool startDocument();
};

}; // namespace Utopia

#endif // __Artist_h__
