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

#ifndef __BlockParser_h__
#define __BlockParser_h__

#include "utopiablock.h"

#include <QtCore/QStack>
#include <QtCore/QVariant>
#include <QtXml/QXmlDefaultHandler>

namespace Utopia
{

class MetaBase;

class BlockParser : public QXmlDefaultHandler
{
public:
	BlockParser(MetaBase *metabase = 0);

	virtual bool startDocument();
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
	virtual bool characters(const QString& ch);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);
	virtual bool endDocument();

	static void initParsers();
	static void addParser(const QString& name, TypeParser *parser);
	static void cleanupParsers();

protected:
	MetaBase *mMetaBase;
	QString mCurrentBlock;
	QString mCurrentElement;
	QString mCurrentSettingsKey;
};

}; // namespace Utopia

#endif // __BlockParser_h__
