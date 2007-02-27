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
 * @file utopiablock.h The base block class definition
 */

#ifndef __UtopiaBlock_h__
#define __UtopiaBlock_h__

#include "common.h"

#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QSharedData>
#include <QtCore/QSharedDataPointer>

namespace Utopia
{

class UtopiaBlockData : public QSharedData
{
public:
	UtopiaBlockData() { mID = 0; };

	/// The uniqure ID of the object
	uid mID;
	/// The current name of the object
	QString mName;
	/// The current comments of the object
	QString mComments;
	/// The language override of the object
	QString mLangOverride;
	/// The native language of the object
	QString mNativeLang;
};

/**
 * @brief The base class for all UtopiaDB data.
 * The UtopiaBlock class stores common information for all records. Amoung
 * this information is a comment, the native language of the record, and
 * the override language. This class also contains a name() field that can
 * be used to identify the specifc record. As such, the name() feild
 * should not be used for record data, instead use something like 'title'.
 * This class and it's derivatives can be used like any basic type.
 * For example:
 * @code
 * UtopiaBlock block1;
 * UtopiaBlock block2(block1);
 * if(block2 != block1)
 *     block2 = block1;
 * @endcode
 * All of the above is valid uses for this class and all inherited classes.
 * @see name()
 * @author John Eric Martin <cpuwhiz105@users.sourceforge.net>
 */
class UtopiaBlock
{
public:
	UtopiaBlock();
	UtopiaBlock(const UtopiaBlock& block);
	UtopiaBlock(const QString& name);
	virtual ~UtopiaBlock() { };

	UtopiaBlock& operator=(const UtopiaBlock& block);
	bool operator==(const UtopiaBlock& block) const;
	bool operator!=(const UtopiaBlock& block) const;

	uid id() const;
	QString name() const;
	QString comments() const;
	QString langOverride() const;
	QString nativeLang() const;

	virtual QStringList type() const { return QStringList() << "UtopiaBlock"; };

	void setID(uid id);
	void setName(const QString& name);
	void setComments(const QString& comments);
	void setLangOverride(const QString& lang = CURRENT_LANG);
	void setNativeLang(const QString& lang = CURRENT_LANG);

	virtual void clear();

	virtual QString xml(bool encased = true) const;

	static QString xmlSafe(const QString& string);
	static QString xmlIDList(const QString& tagName, const QList<uid>& ids);
	static QString xmlLangMap(const QString& tagName, const QMap<QString, QString>& map);

private:
	QSharedDataPointer<UtopiaBlockData> d;
};

class UtopiaBlockParser : public TypeParser
{
public:
	UtopiaBlockParser() : TypeParser() { };

	virtual bool startDocument();
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
	virtual bool characters(const QString& ch);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);
	virtual bool endDocument();
};

}; // namespace Utopia

#endif // __UtopiaBlock_h__
