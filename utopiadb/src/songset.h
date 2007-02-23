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
 * @file songset.h The SongSet class definition
 */

#ifndef __SongSet_h__
#define __SongSet_h__

#include "common.h"

namespace Utopia
{

class SongSet
{
public:
	SongSet();
	SongSet(const SongSet& block);

	SongSet& operator=(const SongSet& block);
	bool operator==(const SongSet& block);
	bool operator!=(const SongSet& block);

	int track();
	int disc();
 	uid song();
	uid songEdition();

	void setTrack(int value);
	void setDisc(int value);
	void setSong(uid value);
	void setSongEdition(uid value);
	void clear();

	QString xml(bool encased = true) const;

protected:
	Track mTrack;
	uid mSong, mSongEdition;
};

}; // namespace Utopia

#endif // __SongSet_h__
