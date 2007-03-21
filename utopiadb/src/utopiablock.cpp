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
 * @file utopiablock.cpp The base block class implementation
 */

#include "utopiablock.h"

#include <QtCore/QStringList>

using namespace Utopia;

/**
 * @brief The default constructor
 *
 * This constructor sets all data to defaults and sets the object's parent.
 */
UtopiaBlock::UtopiaBlock()
{
	d = new UtopiaBlockData;
	d->mID = 0;
};

/**
 * @brief The copy constructor
 *
 * This constructor copies all data from the given block into this block and
 * sets the object's parent.
 * @param block The block to copy the data from
 */
UtopiaBlock::UtopiaBlock(const UtopiaBlock& block)
{
	d = block.d;
};

/**
 * @brief The default constructor
 *
 * This constructor sets all data to defaults, sets the object's parent, and
 * sets the object's name.
 * @param name The object's name
 */
UtopiaBlock::UtopiaBlock(const QString& name)
{
	d = new UtopiaBlockData;
	d->mName = name;
	d->mID = 0;
};

/**
 * @~english
 * @brief The assignment operator
 *
 * This assignment operator sets all the object data equal to the data in
 * the object passed to the right of the equals sign.
 * @param block The object who's data we want to set this object's data to
 * @returns The new object with the copied data.
 * @~english
 * @~japanese
 * @brief 割り当てオペレータ
 *
 * この割り当てオペレータはすべての目的データを等号の後で渡される目的のデータと等しく置く。
 * @param block データである目的私達はこの目的のデータをに置きたいと思う。
 * @returns コピーされたデータの新しい目的。
 * @~japanese
 */
UtopiaBlock& UtopiaBlock::operator=(const UtopiaBlock& block)
{
	d = block.d;
	return *this;
}

/**
 * @brief The equality operator
 *
 * This equality operator compares all the data in this object to that of
 * the given object.
 * @param block The object to compare this object to
 * @returns true if the objects have the same data, false otherwise
 */
bool UtopiaBlock::operator==(const UtopiaBlock& block) const
{
	if(d->mID == block.d->mID && d->mName == block.d->mName && d->mComments == block.d->mComments && d->mLangOverride == block.d->mLangOverride && d->mNativeLang == block.d->mNativeLang)
		return true;

	return false;
};

/**
 * @brief The not equal operator
 *
 * This not equal operator compares all the data in this object to that of
 * the given object.
 * @param block The object to compare this object to
 * @returns true if the objects don't have the same data, false otherwise
 */
bool UtopiaBlock::operator!=(const UtopiaBlock& block) const
{
	return !( UtopiaBlock::operator==(block) );
};

/**
 * @brief Retrieve the ID
 *
 * This function returns a uid containing the ID of the object.
 * @returns The ID of the object
 */
uid UtopiaBlock::id() const
{
	return d->mID;
};

/**
 * @brief Retrieve the name
 *
 * This function returns a QString containing the name of the object.
 * @returns The name of the object
 */
QString UtopiaBlock::name() const
{
	return d->mName;
};

/**
 * @brief Retrieve the comments
 *
 * This function returns a QString containing the given comments for this
 * object.
 * @returns The comments for this object
 */
QString UtopiaBlock::comments() const
{
	return d->mComments;
};

/**
 * @brief Retrieve the language override
 *
 * This function returns a QString containing the language override for this
 * object. The language override is used to display a specific language pair
 * for a object as opposed to the default langauge. This is useful if, for
 * example, you have the database displaying Japanese entries, but you want
 * this specific object to display entries in English instead.
 * @returns The current language override, langOverride().isEmpty() returns
 * true if there is no language override currently set.
 */
QString UtopiaBlock::langOverride() const
{
	return d->mLangOverride;
};

/**
 * @brief Retrieve the native language
 *
 * This function returns a QString containing the native language for this
 * object. The native language is the original language of the entry. For
 * example, let's say we have a entry for the Ichigo 100% anime. This anime
 * Can be written in English (en) as Ichigo 100% or in Japanese (ja) as
 * いちご１００％. The original language of the anime is Japanese, so we can
 * use this function to determine this, and then retrive the native language
 * of the object for display or editing as opposed to the default language
 * or the override language.
 * @returns The current native language. If nativeLang().isEmpty() returns
 * true, the native language has not been set yet (and should be set).
 */
QString UtopiaBlock::nativeLang() const
{
	return d->mNativeLang;
};

/**
 * @brief Set the object ID
 *
 * This function sets the ID of the object.
 * @param id The new ID for this object
 */
void UtopiaBlock::setID(uid id)
{
	d->mID = id;
};

/**
 * @brief Set the object name
 *
 * This function sets the name of the object.
 * @param name The new name for this object
 */
void UtopiaBlock::setName(const QString& name)
{
	d->mName = name;
};

/**
 * @brief Set the object comments
 *
 * This function sets the comments for this object.
 * @param comments The new comments
 */
void UtopiaBlock::setComments(const QString& comments)
{
	d->mComments = comments;
};

/**
 * @brief Set the lanugage override
 *
 * This function sets the language override for the object. For a description
 * of the language override, @link langOverride() @endlink.
 * @param lang The new language override
 * @see langOverride()
 */
void UtopiaBlock::setLangOverride(const QString& lang)
{
	d->mLangOverride = lang;
};

/**
 * @brief Set the native lanugage
 *
 * This function sets the natve language for the object. For a description
 * of the native override, @link nativeLang() @endlink.
 * @param lang The new native language
 * @see nativeLang()
 */
void UtopiaBlock::setNativeLang(const QString& lang)
{
	d->mNativeLang = lang;
};

QMap<QString, QStringList> UtopiaBlock::indexes() const
{
	return QMap<QString, QStringList>();
};

QStringList UtopiaBlock::indexKeys() const
{
	return indexes().keys();
};

QStringList UtopiaBlock::indexValues(const QString& key) const
{
	return indexes().value(key);
};

/**
 * @brief Clears all data
 *
 * This function clears all data in the object back to empty and/or defaults.
 */
void UtopiaBlock::clear()
{
	d->mID = 0;
	d->mName.clear();
	d->mComments.clear();
	d->mLangOverride.clear();
	d->mNativeLang.clear();
};

QString UtopiaBlock::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<block>\n";

	string += "  <id>" + QString::number(d->mID) + "</id>\n";

	if(!d->mName.isEmpty())
		string += "  <objname>" + xmlSafe(d->mName) + "</objname>\n";
	if(!d->mComments.isEmpty())
		string += "  <comments>" + xmlSafe(d->mComments) + "</comments>\n";
	if(!d->mLangOverride.isEmpty())
		string += "  <langoverride>" + d->mLangOverride + "</langoverride>\n";
	if(!d->mNativeLang.isEmpty())
		string += "  <nativelang>" + d->mNativeLang + "</nativelang>\n";

	if(encased)
		string += "</block>\n";

	return string;
};

QString UtopiaBlock::xmlSafe(const QString& string)
{
	QString escaped = string;

	escaped.replace("<", "&lt;");
	escaped.replace("&", "&amp;");
	escaped.replace(">", "&gt;");
	escaped.replace("\'", "&apos;");
	escaped.replace("\"", "&quot;");

	return escaped;
};

QString UtopiaBlock::xmlIDList(const QString& tagName, const QList<uid>& ids)
{
	QString string;
	QStringList list;

	for(int i = 0; i < ids.count(); i++)
	{
		list << QString::number(ids.at(i));
	}

	string += "  <" + tagName + ">";
	string += list.join(",");
	string += "  </" + tagName + ">";

	return string;
};

QString UtopiaBlock::xmlLangMap(const QString& tagName, const QMap<QString, QString>& map)
{
	QString string;
	QStringList keys( map.keys() );

	string += "  <" + tagName + ">\n";

	for(int i = 0; i < keys.count(); i++)
	{
		string += "    <value lang=\"" + keys.at(i) + "\">" + xmlSafe( map.value( keys.at(i) ) ) + "</value>\n";
	}

	string += "  </" + tagName + ">\n";

	return string;
};

bool UtopiaBlockParser::startDocument()
{
	delete mBlock;
	mBlock = new UtopiaBlock;

	return true;
};

bool UtopiaBlockParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
	mElements.push(localName);
	mAtts.push(atts);

	return true;
};

bool UtopiaBlockParser::characters(const QString& ch)
{
	if(mElements.top() == "id")
	{
		mBlock->setID( ch.toInt() );
		return true;
	}
	if(mElements.top() == "objname")
	{
		mBlock->setName( ch.trimmed() );
		return true;
	}
	if(mElements.top() == "comments")
	{
		mBlock->setComments( ch.trimmed() );
		return true;
	}
	if(mElements.top() == "langoverride")
	{
		mBlock->setLangOverride( ch.trimmed() );
		return true;
	}
	if(mElements.top() == "nativelang")
	{
		mBlock->setNativeLang( ch.trimmed() );
		return true;
	}

	return true;
};

bool UtopiaBlockParser::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	if(mElements.top() != localName)
		return false;

	mElements.pop();
	mAtts.pop();

	return true;
};

bool UtopiaBlockParser::endDocument()
{
	delete mBlock;

	mElements.clear();
	mAtts.clear();

	mBlock = 0;
	mElements.push("__base__");

	return true;
};
