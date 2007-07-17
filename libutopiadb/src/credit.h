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
 * @file credit.h The Credit block class definition
 */

#ifndef __Credit_h__
#define __Credit_h__

#include "utopiablock.h"

namespace Utopia
{

class CreditData : public QSharedData
{
public:
	QString mPre, mFirstName, mMiddleName, mLastName, mPost;
	QString mRole;
	QString mNick;
	QString mURL;
	QString mSite;
};

class Credit : public UtopiaBlock
{
public:
	Credit();

	bool operator==(const Credit& block);
	bool operator!=(const Credit& block);

	QString pre() const;
	QString firstName() const;
	QString middleName() const;
	QString lastName() const;
	QString post() const;

	QString role() const;
	QString nick() const;
	QString url() const;
	QString site() const;

	virtual QStringList type() const { return QStringList() << "Credit" << UtopiaBlock::type(); };

	void setPre(const QString& pre);
	void setFirstName(const QString& first);
	void setMiddleName(const QString& middle);
	void setLastName(const QString& last);
	void setPost(const QString& post);

	void setRole(const QString& role);
	void setNick(const QString& nick);
	void setURL(const QString& url);
	void setSite(const QString& site);

	virtual void clear();

	virtual QString xml(bool encased = true) const;

private:
	QSharedDataPointer<CreditData> d;
};

class CreditParser : public UtopiaBlockParser
{
public:
	CreditParser() : UtopiaBlockParser() { };

	virtual bool startDocument();
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __Credit_h__
