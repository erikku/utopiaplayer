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
 * @file mood.cpp The Mood block class implementation
 */

#include "mood.h"

using namespace Utopia;

#include <QtXml/QXmlStreamWriter>

Mood::Mood() : UtopiaBlock()
{
	d = new MoodData;
	clear();
};

Mood::Mood(const QMap<QString, QString>& moods) : UtopiaBlock()
{
	clear();
	d->mMood = moods;
};

Mood::Mood(const QString& mood, const QString& lang) : UtopiaBlock()
{
	clear();
	d->mMood[lang] = mood;
};

bool Mood::operator==(const Mood& block)
{
	if(d->mMood != block.d->mMood)
		return false;

	return UtopiaBlock::operator==(block);
};

bool Mood::operator!=(const Mood& block)
{
	return !( Mood::operator==(block) );
};

void Mood::clear()
{
	d->mMood.clear();

	UtopiaBlock::clear();
};

QList<QString> Mood::langs() const
{
	return d->mMood.keys();
};

bool Mood::containsLang(const QString& lang)
{
	return d->mMood.value(lang).isEmpty();
};

QList<QString> Mood::moods() const
{
	return d->mMood.values();
};

bool Mood::containsMood(const QString& mood)
{
	return d->mMood.key(mood).isEmpty();
};

QString Mood::mood(const QString& lang) const
{
	return d->mMood.value(lang);
};

void Mood::add(const QString& mood, const QString& lang)
{
	d->mMood[lang] = mood;
};

void Mood::remove(const QString& mood, const QString& lang)
{
	if(mood.isEmpty())
	{
		d->mMood.remove( lang );
	}
	else
	{
		d->mMood.remove( d->mMood.key(mood) );
	}
};

void Mood::xmlSegment(QXmlStreamWriter *writer, bool encased) const
{
	if(encased)
		writer->writeStartElement("mood");

	UtopiaBlock::xmlSegment(writer, false);

	if(d->mMood.count())
		xmlLangMap(writer, "name", d->mMood);

	if(encased)
		writer->writeEndElement();
};

bool MoodParser::startDocument()
{
	delete mBlock;
	mBlock = new Mood;

	return true;
};

bool MoodParser::characters(const QString& ch)
{
	if(mElements.top() == "value")
	{
		if( mElements.at(mElements.count() - 2) == "name" )
		{
			((Mood*)mBlock)->add(ch.trimmed(), mAtts.top().value("lang"));
			return true;
		}
	}
	if(mElements.top() == "name")
		return true;

	return UtopiaBlockParser::characters(ch);
};
