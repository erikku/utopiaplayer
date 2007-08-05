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
 * @file artist.cpp The Artist block class implementation
 */

#include "artist.h"

#include <QtXml/QXmlStreamWriter>

using namespace Utopia;

Artist::Artist() : Individual()
{
	// Nothing here
};

Artist::Artist(const QString& name) : Individual(name)
{
	addArtistName(name);
};

QString Artist::artistName(const QString& lang) const
{
	return Individual::individualName(lang);
};

QMap<QString, QString> Artist::artistNamePairs() const
{
	return Individual::individualNamePairs();
};

QList<QString> Artist::artistNames() const
{
	return Individual::individualNames();
};

QList<QString> Artist::artistLangs() const
{
	return Individual::individualLangs();
};

bool Artist::artistContainsName(const QString& name)
{
	return Individual::individualContainsName(name);
};

bool Artist::artistContainsLang(const QString& lang)
{
	return Individual::individualContainsLang(lang);
};

void Artist::addArtistName(const QString& name, const QString& lang)
{
	Individual::addIndividualName(name, lang);
};

void Artist::removeArtistName(const QString& name, const QString& lang)
{
	Individual::removeIndividualName(name, lang);
};

void Artist::clearArtistNames()
{
	Individual::clearIndividualNames();
};

void Artist::xmlSegment(QXmlStreamWriter *writer, bool encased) const
{
	if(encased)
		writer->writeStartElement("artist");

	Individual::xmlSegment(writer, false);

	if(encased)
		writer->writeEndElement();
};

bool ArtistParser::startDocument()
{
	delete mBlock;
	mBlock = new Artist;

	return true;
};
