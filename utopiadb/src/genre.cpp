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
 * @file genre.cpp The Genre block class implementation
 */

#include "genre.h"

using namespace Utopia;

Genre::Genre() : UtopiaBlock()
{
	d = new GenreData;
	clear();
};

Genre::Genre(const QMap<QString, QString>& genres) : UtopiaBlock()
{
	clear();
	d->mGenre = genres;
};

Genre::Genre(const QString& genre, const QString& lang) : UtopiaBlock()
{
	clear();
	d->mGenre[lang] = genre;
};

bool Genre::operator==(const Genre& block)
{
	if(d->mGenre != block.d->mGenre)
		return false;

	return UtopiaBlock::operator==(block);
};

bool Genre::operator!=(const Genre& block)
{
	return !( Genre::operator==(block) );
};

void Genre::clear()
{
	d->mGenre.clear();

	// No need to emit dataChanged() since the base class does...
	UtopiaBlock::clear();
};

QList<QString> Genre::langs() const
{
	return d->mGenre.keys();
};

bool Genre::containsLang(const QString& lang)
{
	return d->mGenre.value(lang).isEmpty();
};

QList<QString> Genre::genres() const
{
	return d->mGenre.values();
};

bool Genre::containsGenre(const QString& genre)
{
	return d->mGenre.key(genre).isEmpty();
};

QString Genre::genre(const QString& lang) const
{
	return d->mGenre.value(lang);
};

void Genre::add(const QString& genre, const QString& lang)
{
	d->mGenre[lang] = genre;
};

void Genre::remove(const QString& genre, const QString& lang)
{
	if(genre.isEmpty())
	{
		d->mGenre.remove( lang );
	}
	else
	{
		d->mGenre.remove( d->mGenre.key(genre) );
	}
};

QString Genre::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<genre>\n";

	string += UtopiaBlock::xml(false);

	if(d->mGenre.count())
		string += xmlLangMap("name", d->mGenre);

	if(encased)
		string += "</genre>\n";

	return string;
};

bool GenreParser::startDocument()
{
	delete mBlock;
	mBlock = new Genre;

	return true;
};

bool GenreParser::characters(const QString& ch)
{
	if(mElements.top() == "value")
	{
		if( mElements.at(mElements.count() - 2) == "name" )
		{
			((Genre*)mBlock)->add(ch.trimmed(), mAtts.top().value("lang"));
			return true;
		}
	}
	if(mElements.top() == "name")
		return true;

	return UtopiaBlockParser::characters(ch);
};
