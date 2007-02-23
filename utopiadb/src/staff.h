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
 * @file staff.h The Staff block class definition
 */

#ifndef __Staff_h__
#define __Staff_h__

#include "individual.h"

namespace Utopia
{

class StaffData : public QSharedData
{
public:
	QMap<QString, QString> mRole;
};

class Staff : public Individual
{
public:
	Staff();
	Staff(const QString& name);

	bool operator==(const Staff& block);
	bool operator!=(const Staff& block);

	QString role(const QString& lang = CURRENT_LANG) const;
	QMap<QString, QString> roleNamePairs() const;
	QList<QString> roleNames() const;
	QList<QString> roleLangs() const;

	QString staffName(const QString& lang = CURRENT_LANG) const;
	QMap<QString, QString> staffNamePairs() const;
	QList<QString> staffNames() const;
	QList<QString> staffLangs() const;
	bool staffContainsName(const QString& name);
	bool staffContainsLang(const QString& lang = CURRENT_LANG);

	virtual QStringList type() const { return QStringList() << "Staff" << Individual::type(); };

	void addStaffName(const QString& name, const QString& lang = CURRENT_LANG);
	void removeStaffName(const QString& name = "", const QString& lang = CURRENT_LANG);
	void clearStaffNames();

	void addRole(const QString& role, const QString& lang = CURRENT_LANG);
	void removeRole(const QString& role = "", const QString& lang = CURRENT_LANG);
	void clearRole();

	virtual void clear();

	virtual QString xml(bool encased = true) const;

private:
	QSharedDataPointer<StaffData> d;
};

class StaffParser : public IndividualParser
{
public:
	StaffParser() : IndividualParser() { };

	virtual bool startDocument();
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __Staff_h__
