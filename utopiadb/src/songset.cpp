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
 * @file songset.cpp The SongSet class implementation
 */

#include "songset.h"

using namespace Utopia;

SongSet::SongSet()
{
	clear();
};

SongSet::SongSet(const SongSet& block)
{
	SongSet::operator=(block);
};

SongSet& SongSet::operator=(const SongSet& block)
{
	mTrack.track = block.mTrack.track;
	mTrack.disc = block.mTrack.disc;
	mSong = block.mSong;
	mSongEdition = block.mSongEdition;

	return *this;
};

bool SongSet::operator==(const SongSet& block)
{
	if(mTrack.track == block.mTrack.track && mTrack.disc == block.mTrack.disc &&
		mSong == block.mSong && mSongEdition == block.mSongEdition)
		return true;

	return false;
};

bool SongSet::operator!=(const SongSet& block)
{
	return !( SongSet::operator==(block) );
};

int SongSet::track()
{
	return mTrack.track;
};

int SongSet::disc()
{
	return mTrack.disc;
};

uid SongSet::song()
{
	return mSong;
};

uid SongSet::songEdition()
{
	return mSongEdition;
};

void SongSet::setTrack(int value)
{
	mTrack.track = value;
};

void SongSet::setDisc(int value)
{
	mTrack.disc = value;
};

void SongSet::setSong(uid value)
{
	mSong = value;
};

void SongSet::setSongEdition(uid value)
{
	mSongEdition = value;
};

void SongSet::clear()
{
	mTrack.track = 0;
	mTrack.disc = 0;
	mSong = 0;
	mSongEdition = 0;
};

QString SongSet::xml(bool encased) const
{
	QString string;

	string += "<song id=\"" + QString::number(mSong) + "\" disc=\"" + QString::number(mTrack.disc) + "\" track=\"" + QString::number(mTrack.track) + "\" />\n";

	return string;
};
