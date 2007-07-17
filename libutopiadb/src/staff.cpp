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
 * @file staff.cpp The Staff block class implementation
 */

#include "staff.h"

using namespace Utopia;

Staff::Staff() : Individual()
{
	d = new StaffData;
};

Staff::Staff(const QString& name) : Individual(name)
{
	d = new StaffData;
};

bool Staff::operator==(const Staff& block)
{
	if(d->mRole != block.d->mRole)
		return false;

	return Individual::operator==(block);
};

bool Staff::operator!=(const Staff& block)
{
	return !( Staff::operator==(block) );
};

QString Staff::staffName(const QString& lang) const
{
	return Individual::individualName(lang);
};

QMap<QString, QString> Staff::staffNamePairs() const
{
	return Individual::individualNamePairs();
};

QList<QString> Staff::staffNames() const
{
	return Individual::individualNames();
};

QList<QString> Staff::staffLangs() const
{
	return Individual::individualLangs();
};

bool Staff::staffContainsName(const QString& name)
{
	return Individual::individualContainsName(name);
};

bool Staff::staffContainsLang(const QString& lang)
{
	return Individual::individualContainsLang(lang);
};

void Staff::addStaffName(const QString& name, const QString& lang)
{
	Individual::addIndividualName(name, lang);
};

void Staff::removeStaffName(const QString& name, const QString& lang)
{
	Individual::removeIndividualName(name, lang);
};

void Staff::clearStaffNames()
{
	Individual::clearIndividualNames();
};

QString Staff::role(const QString& lang) const
{
	return d->mRole.value(lang);
};

QMap<QString, QString> Staff::roleNamePairs() const
{
	return d->mRole;
};

QList<QString> Staff::roleNames() const
{
	return d->mRole.values();
};

QList<QString> Staff::roleLangs() const
{
	return d->mRole.keys();
};

void Staff::addRole(const QString& role, const QString& lang)
{
	d->mRole[lang] = role;
};

void Staff::removeRole(const QString& role, const QString& lang)
{
	if(role.isEmpty())
		d->mRole.remove( lang );
	else
		d->mRole.remove( d->mRole.key(role) );
};

void Staff::clearRole()
{
	d->mRole.clear();
};

void Staff::clear()
{
	d->mRole.clear();

	Individual::clear();
};

QString Staff::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<staff>\n";

	string += Individual::xml(false);

	if(d->mRole.count())
		string += xmlLangMap("role", d->mRole);

	if(encased)
		string += "</staff>\n";

	return string;
};

bool StaffParser::startDocument()
{
	delete mBlock;
	mBlock = new Staff;

	return true;
};

bool StaffParser::characters(const QString& ch)
{
	if(mElements.top() == "value")
	{
		if( mElements.at(mElements.count() - 2) == "role" )
		{
			((Staff*)mBlock)->addRole(ch.trimmed(), mAtts.top().value("lang"));
			return true;
		}
	}
	if(mElements.top() == "role")
		return true;

	return IndividualParser::characters(ch);
};
