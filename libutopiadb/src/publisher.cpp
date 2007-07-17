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
 * @file publisher.cpp The Publisher block class implementation
 */

#include "publisher.h"

using namespace Utopia;

Publisher::Publisher() : Individual()
{
	// Nothing here
};

Publisher::Publisher(const QString& name) : Individual(name)
{
	// Stuff here
};

QString Publisher::publisherName(const QString& lang) const
{
	return Individual::individualName(lang);
};

QMap<QString, QString> Publisher::publisherNamePairs() const
{
	return Individual::individualNamePairs();
};

QList<QString> Publisher::publisherNames() const
{
	return Individual::individualNames();
};

QList<QString> Publisher::publisherLangs() const
{
	return Individual::individualLangs();
};

bool Publisher::publisherContainsName(const QString& name)
{
	return Individual::individualContainsName(name);
};

bool Publisher::publisherContainsLang(const QString& lang)
{
	return Individual::individualContainsLang(lang);
};

void Publisher::addPublisherName(const QString& name, const QString& lang)
{
	Individual::addIndividualName(name, lang);
};

void Publisher::removePublisherName(const QString& name, const QString& lang)
{
	Individual::removeIndividualName(name, lang);
};

void Publisher::clearPublisherNames()
{
	Individual::clearIndividualNames();
};

QString Publisher::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<publisher>\n";

	string += Individual::xml(false);

	if(encased)
		string += "</publisher>\n";

	return string;
};

bool PublisherParser::startDocument()
{
	delete mBlock;
	mBlock = new Publisher;

	return true;
};
