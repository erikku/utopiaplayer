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
 * @file credit.cpp The Credit block class implementation
 */

#include "credit.h"

using namespace Utopia;

Credit::Credit() : UtopiaBlock()
{
	d = new CreditData;
	clear();
};

bool Credit::operator==(const Credit& block)
{
	if(d->mPre != block.d->mPre || d->mFirstName != block.d->mFirstName || d->mMiddleName != block.d->mMiddleName || d->mLastName != block.d->mLastName
	|| d->mPost != block.d->mPost || d->mRole != block.d->mRole || d->mNick != block.d->mNick || d->mURL != block.d->mURL || d->mSite != block.d->mSite)
		return false;

	return UtopiaBlock::operator==(block);
};

bool Credit::operator!=(const Credit& block)
{
	return !( Credit::operator==(block) );
};

QString Credit::pre() const
{
	return d->mPre;
};

QString Credit::firstName() const
{
	return d->mFirstName;
};

QString Credit::middleName() const
{
	return d->mMiddleName;
};

QString Credit::lastName() const
{
	return d->mLastName;
};

QString Credit::post() const
{
	return d->mPost;
};

QString Credit::role() const
{
	return d->mRole;
};

QString Credit::nick() const
{
	return d->mNick;
};

QString Credit::url() const
{
	return d->mURL;
};

QString Credit::site() const
{
	return d->mSite;
};

void Credit::setPre(const QString& pre)
{
	d->mPre = pre;
};

void Credit::setFirstName(const QString& first)
{
	d->mFirstName = first;
};

void Credit::setMiddleName(const QString& middle)
{
	d->mMiddleName = middle;
};

void Credit::setLastName(const QString& last)
{
	d->mLastName = last;
};

void Credit::setPost(const QString& post)
{
	d->mPost = post;
};

void Credit::setRole(const QString& role)
{
	d->mRole = role;
};

void Credit::setNick(const QString& nick)
{
	d->mNick = nick;
};

void Credit::setURL(const QString& url)
{
	d->mURL = url;
};

void Credit::setSite(const QString& site)
{
	d->mSite = site;
};

void Credit::clear()
{
	d->mPre = QString();
	d->mFirstName = QString();
	d->mMiddleName = QString();
	d->mLastName = QString();
	d->mPost = QString();
	d->mRole = QString();
	d->mNick = QString();
	d->mURL = QString();
	d->mSite = QString();
	
	UtopiaBlock::clear();
};

QString Credit::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<credit>\n";

	string += UtopiaBlock::xml(false);

	if(!d->mPre.isEmpty())
		string += "  <pre>" + d->mPre + "</pre>\n";
	if(!d->mFirstName.isEmpty())
		string += "  <firstname>" + d->mFirstName + "</firstname>\n";
	if(!d->mMiddleName.isEmpty())
		string += "  <middlename>" + d->mMiddleName + "</middlename>\n";
	if(!d->mLastName.isEmpty())
		string += "  <lastname>" + d->mLastName + "</lastname>\n";
	if(!d->mPost.isEmpty())
		string += "  <post>" + d->mPost + "</post>\n";

	if(!d->mRole.isEmpty())
		string += "  <role>" + d->mRole + "</role>\n";
	if(!d->mNick.isEmpty())
		string += "  <nick>" + d->mNick + "</nick>\n";
	if(!d->mURL.isEmpty())
		string += "  <url>" + d->mURL + "</url>\n";
	if(!d->mSite.isEmpty())
		string += "  <site>" + d->mSite + "</site>\n";

	if(encased)
		string += "</credit>\n";

	return string;
};

bool CreditParser::startDocument()
{
	delete mBlock;
	mBlock = new Credit;

	return true;
};

bool CreditParser::characters(const QString& ch)
{
	if(mElements.top() == "pre")
	{
		((Credit*)mBlock)->setPre(ch.trimmed());
		return true;
	}
	if(mElements.top() == "firstname")
	{
		((Credit*)mBlock)->setFirstName(ch.trimmed());
		return true;
	}
	if(mElements.top() == "middlename")
	{
		((Credit*)mBlock)->setMiddleName(ch.trimmed());
		return true;
	}
	if(mElements.top() == "lastname")
	{
		((Credit*)mBlock)->setLastName(ch.trimmed());
		return true;
	}
	if(mElements.top() == "post")
	{
		((Credit*)mBlock)->setPost(ch.trimmed());
		return true;
	}

	if(mElements.top() == "role")
	{
		((Credit*)mBlock)->setRole(ch.trimmed());
		return true;
	}
	if(mElements.top() == "nick")
	{
		((Credit*)mBlock)->setNick(ch.trimmed());
		return true;
	}
	if(mElements.top() == "url")
	{
		((Credit*)mBlock)->setURL(ch.trimmed());
		return true;
	}
	if(mElements.top() == "site")
	{
		((Credit*)mBlock)->setSite(ch.trimmed());
		return true;
	}

	return UtopiaBlockParser::characters(ch);
};
