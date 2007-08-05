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
 * @file composer.h The Composer block class definition
 */

#ifndef __Composer_h__
#define __Composer_h__

#include "individual.h"

namespace Utopia
{

class Composer : public Individual
{
public:
	Composer();
	Composer(const QString& name);

	QString composerName(const QString& lang = CURRENT_LANG) const;
	QMap<QString, QString> composerNamePairs() const;
	QList<QString> composerNames() const;
	QList<QString> composerLangs() const;
	bool composerContainsName(const QString& name);
	bool composerContainsLang(const QString& lang = CURRENT_LANG);

	virtual QStringList type() const { return QStringList() << "Composer" << Individual::type(); };

	void addComposerName(const QString& name, const QString& lang = CURRENT_LANG);
	void removeComposerName(const QString& name = "", const QString& lang = CURRENT_LANG);
	void clearComposerNames();

protected:
	virtual void xmlSegment(QXmlStreamWriter *writer, bool encased = true) const;
};

class ComposerParser : public IndividualParser
{
public:
	ComposerParser() : IndividualParser() { };

	virtual bool startDocument();
};

}; // namespace Utopia

#endif // __Composer_h__
