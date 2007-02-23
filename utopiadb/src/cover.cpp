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
 * @file cover.cpp The Cover block class implementation
 */

#include "cover.h"

using namespace Utopia;

Cover::Cover() : UtopiaBlock()
{
	d = new CoverData;
	clear();
};

Cover::Cover(const QString& path) : UtopiaBlock()
{
	d = new CoverData;
	setPath(path);
	load();
};

bool Cover::operator==(const Cover& block)
{
	if(d->mPath != block.d->mPath)
		return false;

	if(!d->mCover && !block.d->mCover)
		return UtopiaBlock::operator==(block);

	if(!d->mCover || !block.d->mCover)
		return false;

	if(d->mCover.size() != block.d->mCover.size())
		return false;

	return UtopiaBlock::operator==(block);
};

bool Cover::operator!=(const Cover& block)
{
	return !( Cover::operator==(block) );
};

QString Cover::path() const
{
	return d->mPath;
};

QPixmap Cover::cover() const
{
	return d->mCover;
};

void Cover::setPath(const QString& path)
{
	d->mPath = path;
	d->mCover.load(d->mPath);
};

void Cover::clearPath()
{
	d->mPath.clear();
};

void Cover::setCover(const QPixmap& cover)
{
	d->mCover = cover;
};

void Cover::clearCover()
{
	d->mCover = QPixmap();
};

void Cover::load()
{
	d->mCover = QPixmap();

	d->mCover.load(d->mPath);
};

void Cover::save()
{
	d->mCover.save(d->mPath);
};

void Cover::clear()
{
	d->mPath.clear();
	d->mCover = QPixmap();
	
	UtopiaBlock::clear();
};

QString Cover::xml(bool encased) const
{
	QString string;

	if(encased)
		string += "<cover>\n";

	string += UtopiaBlock::xml(false);

	if(!d->mPath.isEmpty())
		string += "  <path>" + xmlSafe(d->mPath) + "</path>\n";

	if(encased)
		string += "</cover>\n";

	return string;
};

bool CoverParser::startDocument()
{
	delete mBlock;
	mBlock = new Cover;

	return true;
};

bool CoverParser::characters(const QString& ch)
{
	if(mElements.top() == "path")
	{
		if( mElements.at(mElements.count() - 2) == "name" )
		{
			((Cover*)mBlock)->setPath(ch.trimmed());
			return true;
		}
	}

	return UtopiaBlockParser::characters(ch);
};
