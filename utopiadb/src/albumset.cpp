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
 * @file albumset.cpp The AlbumSet class implementation
 */

#include "albumset.h"

using namespace Utopia;

AlbumSet::AlbumSet()
{
	clear();
};

AlbumSet::AlbumSet(const AlbumSet& block)
{
	AlbumSet::operator=(block);
};

AlbumSet& AlbumSet::operator=(const AlbumSet& block)
{
	mTrack.track = block.mTrack.track;
	mTrack.disc = block.mTrack.disc;
	mAlbum = block.mAlbum;

	return *this;
};

bool AlbumSet::operator==(const AlbumSet& block)
{
	if(mTrack.track == block.mTrack.track && mTrack.disc == block.mTrack.disc && mAlbum == block.mAlbum)
		return true;

	return false;
};

bool AlbumSet::operator!=(const AlbumSet& block)
{
	return !( AlbumSet::operator==(block) );
};

int AlbumSet::track()
{
	return mTrack.track;
};

int AlbumSet::disc()
{
	return mTrack.disc;
};

uid AlbumSet::album()
{
	return mAlbum;
};

void AlbumSet::setTrack(int value)
{
	mTrack.track = value;
};

void AlbumSet::setDisc(int value)
{
	mTrack.disc = value;
};

void AlbumSet::setAlbum(uid value)
{
	mAlbum = value;
};

void AlbumSet::clear()
{
	mTrack.track = 0;
	mTrack.disc = 0;
	mAlbum = 0;
};

QString AlbumSet::xml(bool encased) const
{
	QString string;

	string += "<album id=\"" + QString::number(mAlbum) + "\" disc=\"" + QString::number(mTrack.disc) + "\" track=\"" + QString::number(mTrack.track) + "\" />\n";

	return string;
};
