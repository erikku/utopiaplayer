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

#include "blockparser.h"

#include "metabase.h"

using namespace Utopia;

namespace Utopia
{
	static QMap<QString, TypeParser*> gTypeParsers;
};

BlockParser::BlockParser(MetaBase *metabase) : QXmlDefaultHandler()
{
	mMetaBase = metabase;
};

bool BlockParser::startDocument()
{
	mCurrentBlock.clear();
	mCurrentElement.clear();
	mCurrentSettingsKey.clear();

	return true;
};
#include <iostream>
bool BlockParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
	mCurrentElement = localName;

	if(!mCurrentBlock.isEmpty())
		return gTypeParsers[mCurrentBlock]->startElement(namespaceURI, localName, qName, atts);

	if( localName == "utopiadb" ||  localName == "settings" )
		return true;

	if( localName == "setting" )
	{
		mCurrentSettingsKey = atts.value("key");
		return true;
	}

	if( !gTypeParsers.contains(localName) )
		throw QObject::tr("Unknown block type <i>%1</i>").arg(localName).toLocal8Bit().data();

	mCurrentBlock = localName;
	return gTypeParsers[mCurrentBlock]->startDocument();
};

bool BlockParser::characters(const QString& ch)
{
	if( ch.trimmed().isEmpty() )
		return true;

	if( mCurrentElement == "setting" )
	{
		mMetaBase->setSetting(mCurrentSettingsKey, ch.trimmed());
		return true;
	}

	if(!mCurrentBlock.isEmpty())
		return gTypeParsers[mCurrentBlock]->characters(ch);

	return true;
};

bool BlockParser::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	if(!mCurrentBlock.isEmpty())
	{
		if(mCurrentBlock == localName)
		{
			mMetaBase->addBlock(*gTypeParsers[mCurrentBlock]->block());
			bool ret = gTypeParsers[mCurrentBlock]->endDocument();
			mCurrentBlock.clear();
			return ret;
		}
		else
		{
			return gTypeParsers[mCurrentBlock]->endElement(namespaceURI, localName, qName);
		}
	}

	if( localName == "utopiadb" || localName == "settings" || localName == "setting" )
		return true;

	throw QObject::tr("We have some random element <i>%1</i>").arg(localName);

	return true;
};

bool BlockParser::endDocument()
{
	mCurrentBlock.clear();
	mCurrentElement.clear();
	mCurrentSettingsKey.clear();

	return true;
};

void BlockParser::initParsers()
{
	addParser("block", new UtopiaBlockParser);
	addParser("individual", new IndividualParser);
	addParser("artist", new ArtistParser);
	addParser("composer", new ComposerParser);
	addParser("publisher", new PublisherParser);
	addParser("staff", new StaffParser);
	addParser("mood", new MoodParser);
	addParser("genre", new GenreParser);
	addParser("cover", new CoverParser);
	addParser("credit", new CreditParser);
	addParser("album", new AlbumParser);
	addParser("song", new SongParser);
	addParser("songedition", new SongEditionParser);
	addParser("songfile", new SongFileParser);
};

void BlockParser::addParser(const QString& name, TypeParser *parser)
{
	gTypeParsers[name] = parser;
};

void BlockParser::cleanupParsers()
{
	foreach(TypeParser *parser, gTypeParsers)
		delete parser;

	gTypeParsers.clear();
};
