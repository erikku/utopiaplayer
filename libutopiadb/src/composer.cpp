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
 * @file composer.cpp The Composer block class implementation
 */

#include "composer.h"

#include <QtXml/QXmlStreamWriter>

using namespace Utopia;

Composer::Composer() : Individual()
{
	// Nothing here
};

Composer::Composer(const QString& name) : Individual(name)
{
	// Stuff here
};

QString Composer::composerName(const QString& lang) const
{
	return Individual::individualName(lang);
};

QMap<QString, QString> Composer::composerNamePairs() const
{
	return Individual::individualNamePairs();
};

QList<QString> Composer::composerNames() const
{
	return Individual::individualNames();
};

QList<QString> Composer::composerLangs() const
{
	return Individual::individualLangs();
};

bool Composer::composerContainsName(const QString& name)
{
	return Individual::individualContainsName(name);
};

bool Composer::composerContainsLang(const QString& lang)
{
	return Individual::individualContainsLang(lang);
};

void Composer::addComposerName(const QString& name, const QString& lang)
{
	Individual::addIndividualName(name, lang);
};

void Composer::removeComposerName(const QString& name, const QString& lang)
{
	Individual::removeIndividualName(name, lang);
};

void Composer::clearComposerNames()
{
	Individual::clearIndividualNames();
};

void Composer::xmlSegment(QXmlStreamWriter *writer, bool encased) const
{
	if(encased)
		writer->writeStartElement("composer");

	Individual::xmlSegment(writer, false);

	if(encased)
		writer->writeEndElement();
};

bool ComposerParser::startDocument()
{
	delete mBlock;
	mBlock = new Composer;

	return true;
};
