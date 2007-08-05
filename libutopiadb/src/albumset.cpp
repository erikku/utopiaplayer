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

#include <QtXml/QXmlStreamWriter>

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
	mTrack = block.mTrack;
	mAlbum = block.mAlbum;

	return *this;
};

bool AlbumSet::operator==(const AlbumSet& block)
{
	if(mTrack == block.mTrack && mAlbum == block.mAlbum)
		return true;

	return false;
};

bool AlbumSet::operator!=(const AlbumSet& block)
{
	return !( AlbumSet::operator==(block) );
};

int AlbumSet::track()
{
	return mTrack.track();
};

int AlbumSet::disc()
{
	return mTrack.disc();
};

uid AlbumSet::album()
{
	return mAlbum;
};

void AlbumSet::setTrack(int value)
{
	mTrack.setTrack(value);
};

void AlbumSet::setDisc(int value)
{
	mTrack.setDisc(value);
};

void AlbumSet::setAlbum(uid value)
{
	mAlbum = value;
};

void AlbumSet::clear()
{
	mAlbum = 0;
};

void AlbumSet::xmlSegment(QXmlStreamWriter *writer) const
{
	writer->writeEmptyElement("album");
	writer->writeAttribute("id", QString::number(mAlbum));
	writer->writeAttribute("disc", QString::number(mTrack.disc()));
	writer->writeAttribute("track", QString::number(mTrack.track()));
	writer->writeEndElement();
};
