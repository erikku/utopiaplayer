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
 * @file publisher.h The Publisher block class definition
 */

#ifndef __Publisher_h__
#define __Publisher_h__

#include "individual.h"

namespace Utopia
{

class Publisher : public Individual
{
public:
	Publisher();
	Publisher(const QString& name);

	QString publisherName(const QString& lang = CURRENT_LANG) const;
	QMap<QString, QString> publisherNamePairs() const;
	QList<QString> publisherNames() const;
	QList<QString> publisherLangs() const;
	bool publisherContainsName(const QString& name);
	bool publisherContainsLang(const QString& lang = CURRENT_LANG);

	virtual QStringList type() const { return QStringList() << "Publisher" << Individual::type(); };

	void addPublisherName(const QString& name, const QString& lang = CURRENT_LANG);
	void removePublisherName(const QString& name = "", const QString& lang = CURRENT_LANG);
	void clearPublisherNames();

protected:
	virtual void xmlSegment(QXmlStreamWriter *writer, bool encased = true) const;
};

class PublisherParser : public IndividualParser
{
public:
	PublisherParser() : IndividualParser() { };

	virtual bool startDocument();
};

}; // namespace Utopia

#endif // __Publisher_h__
