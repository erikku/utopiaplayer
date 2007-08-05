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
 * @file individual.cpp The Individual block class implementation
 */

#include "individual.h"

#include <QtXml/QXmlStreamWriter>

using namespace Utopia;

//#define d( reinterpret_cast<const IndividualData*>(d.constData()) )
//#define d ( reinterpret_cast<IndividualData*>(d.data()) )
/*
IndividualData::IndividualData(const IndividualData& other)// : UtopiaBlockData(other)
{
	mIndividualNames = other.mIndividualNames;
	mColor = other.mColor;
};
*/
/**
 * @brief The default constructor
 * This constructor sets all data to defaults and sets the object's parent.
 */
Individual::Individual() : UtopiaBlock()
{
	d = new IndividualData;
};

/**
 * @brief The copy constructor
 * This constructor copies all data from the given block into this block and
 * sets the object's parent.
 * @param block The block to copy the data from
 */
/*Individual::Individual(const Individual& block)
{
	Individual::operator=(block);
};*/

/**
 * @brief The default constructor
 * This constructor sets all data to defaults, sets the object's parent, and
 * sets the object's name.
 * @param name The object's name
 */
Individual::Individual(const QString& name) : UtopiaBlock(name)
{
	d = new IndividualData;
};

/**
 * @brief The assignment operator
 * This assignment operator sets all the object data equal to the data in
 * the object passed to the right of the equals sign.
 * @param block The object who's data we want to set this object's data to
 * @returns The new object with the copied data.
 */
/*Individual& Individual::operator=(const Individual& block)
{
	d = block.d;
	e = block.e;

	return *this;
};*/

/**
 * @brief The equality operator
 * This equality operator compares all the data in this object to that of
 * the given object.
 * @param block The object to compare this object to
 * @returns true if the objects have the same data, false otherwise
 */
bool Individual::operator==(const Individual& block) const
{
	if(block.d.constData()->mIndividualNames != d->mIndividualNames || block.d.constData()->mColor != d->mColor)
		return false;

	return UtopiaBlock::operator==(block);
};

/**
 * @brief The not equal operator
 * This not equal operator compares all the data in this object to that of
 * the given object.
 * @param block The object to compare this object to
 * @returns true if the objects don't have the same data, false otherwise
 */
bool Individual::operator!=(const Individual& block) const
{
	return !( Individual::operator==(block) );
};

/**
 * @brief Returns the name of the individual
 * This function returns the name of the individual represented by this block
 * given a language. If the individual does not have a name for the given language,
 * a blank string is returned.
 * @param lang The language of the name to return, defaults to CURRENT_LANG
 * @returns the name of the individual for the given language or a blank string
 * if the individual does not have a name for the given language.
 */
QString Individual::individualName(const QString& lang) const
{
	
	return d->mIndividualNames.value(lang);
};

/**
 * @brief Returns a QMap of language codes and their associated names
 * This function returns a QMap of language codes and their associated names
 * for the block.
 * @returns a QMap of the language/name pairs
 */
QMap<QString, QString> Individual::individualNamePairs() const
{
	return d->mIndividualNames;
};

QList<QString> Individual::individualNames() const
{
	return d->mIndividualNames.values();
};

QList<QString> Individual::individualLangs() const
{
	return d->mIndividualNames.keys();
};

QColor Individual::color() const
{
	return d->mColor;
};

bool Individual::individualContainsName(const QString& name) const
{
	return d->mIndividualNames.key(name).isEmpty();
};

bool Individual::individualContainsLang(const QString& lang) const
{
	return d->mIndividualNames.contains(lang);
};

void Individual::addIndividualName(const QString& name, const QString& lang)
{
	d->mIndividualNames[lang] = name;
};

void Individual::removeIndividualName(const QString& name, const QString& lang)
{
	if(name.isEmpty())
	{
		d->mIndividualNames.remove(lang);
	}
	else
	{
		d->mIndividualNames.remove(d->mIndividualNames.key(name));
	}
};

void Individual::clearIndividualNames()
{
	d->mIndividualNames.clear();
};

void Individual::setColor(const QColor& color)
{
	d->mColor = color;
};

void Individual::setColor(int r, int g, int b)
{
	d->mColor = QColor(r, g, b);
};

void Individual::clearColor()
{
	d->mColor = QColor();
};

QMap<QString, QStringList> Individual::indexes() const
{
	QMap<QString, QStringList> result = UtopiaBlock::indexes();
	result["name"] = individualNames();

	return result;
};

/**
 * @brief Clears all data
 * This function clears all data in the object back to empty and/or defaults.
 */
void Individual::clear()
{
	d->mIndividualNames.clear();
	d->mColor = QColor();

	UtopiaBlock::clear();
};

void Individual::xmlSegment(QXmlStreamWriter *writer, bool encased) const
{
	if(encased)
		writer->writeStartElement("individual");

	UtopiaBlock::xmlSegment(writer, false);

	if(d->mIndividualNames.count())
		xmlLangMap(writer, "name", d->mIndividualNames);
	if(d->mColor != QColor())
	{
		writer->writeEmptyElement("color");
		writer->writeAttribute("r", QString::number(d->mColor.red()));
		writer->writeAttribute("g", QString::number(d->mColor.green()));
		writer->writeAttribute("b", QString::number(d->mColor.blue()));
		writer->writeEndElement();
	}

	if(encased)
		writer->writeEndElement();
};

bool IndividualParser::startDocument()
{
	delete mBlock;
	mBlock = new Individual;

	return true;
};

bool IndividualParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
	UtopiaBlockParser::startElement(namespaceURI, localName, qName, atts);

	if(localName == "color")
		((Individual*)mBlock)->setColor( QColor(atts.value("r").trimmed().toInt(), atts.value("g").trimmed().toInt(), atts.value("b").trimmed().toInt()) );

	return true;
};

bool IndividualParser::characters(const QString& ch)
{
	if(mElements.top() == "value")
	{
		if( mElements.at(mElements.count() - 2) == "name" )
		{
			((Individual*)mBlock)->addIndividualName(ch.trimmed(), mAtts.top().value("lang"));
			return true;
		}
	}
	if(mElements.top() == "name")
		return true;

	return UtopiaBlockParser::characters(ch);
};
