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
 * @file tagid.cpp The TagID class implementation
 */

#include "tagid.h"
#include "utopiablock.h"

using namespace Utopia;

bool TagID::operator==(const TagID& block)
{
	if(mSystemID == block.mSystemID && mSongID == block.mSongID)
		return true;

	return false;
};

bool TagID::operator!=(const TagID& block)
{
	return !( TagID::operator==(block) );
};

QString TagID::systemID() const
{
	return mSystemID;
};

QString TagID::songID() const
{
	return mSongID;
};

void TagID::setSystemID(const QString& id)
{
	mSystemID = id;
};

void TagID::setSongID(const QString& id)
{ 
	mSongID = id;
};

void TagID::clear()
{
	mSystemID = QString();
	mSongID = QString();
};

QString TagID::xml(bool encased) const
{
	QString string;

	string += "<tagid systemid=\"" + UtopiaBlock::xmlSafe(mSystemID) + "\" songid=\"" + UtopiaBlock::xmlSafe(mSongID) + "\" />\n";

	return string;
};
