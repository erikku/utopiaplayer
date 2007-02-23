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
 * @file individual.h The Individual block class definition
 */

#ifndef __Individual_h__
#define __Individual_h__

#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtGui/QColor>

#include "utopiablock.h"

namespace Utopia
{

class IndividualData : public QSharedData
{
public:
	/// The list of individual's name in each associated language (lang, name)
	QMap<QString, QString> mIndividualNames;
	QColor mColor;
};

class Individual : public UtopiaBlock
{
public:
	Individual();
	Individual(const QString& name);
	virtual ~Individual() { };

	bool operator==(const Individual& block) const;
	bool operator!=(const Individual& block) const;

	QString individualName(const QString& lang = CURRENT_LANG) const;
	QMap<QString, QString> individualNamePairs() const;
	QList<QString> individualNames() const;
	QList<QString> individualLangs() const;
	bool individualContainsName(const QString& name) const;
	bool individualContainsLang(const QString& lang = CURRENT_LANG) const;

	QColor color() const;

	virtual QStringList type() const { return QStringList() << "Individual" << UtopiaBlock::type(); };

	void addIndividualName(const QString& name, const QString& lang = CURRENT_LANG);
	void removeIndividualName(const QString& name = "", const QString& lang = CURRENT_LANG);
	void clearIndividualNames();

	void setColor(const QColor& color);
	void setColor(int r, int g, int b);
	void clearColor();

	virtual void clear();

	virtual QString xml(bool encased = true) const;

private:
	QSharedDataPointer<IndividualData> d;
};

class IndividualParser : public UtopiaBlockParser
{
public:
	IndividualParser() : UtopiaBlockParser() { };

	virtual bool startDocument();
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __Individual_h__
