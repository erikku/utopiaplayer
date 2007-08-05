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
 * @file albumset.h The AlbumSet block class definition
 */

#ifndef __AlbumSet_h__
#define __AlbumSet_h__

#include "common.h"

class QXmlStreamWriter;

namespace Utopia
{

class AlbumSet
{
public:
	AlbumSet();
	AlbumSet(const AlbumSet& block);

	AlbumSet& operator=(const AlbumSet& block);
	bool operator==(const AlbumSet& block);
	bool operator!=(const AlbumSet& block);

	int track();
	int disc();
 	uid album();

	void setTrack(int value);
	void setDisc(int value);
	void setAlbum(uid value);
	void clear();

	void xmlSegment(QXmlStreamWriter *writer) const;

protected:
	Track mTrack;
	uid mAlbum;
};

}; // namespace Utopia

#endif // __AlbumSet_h__
