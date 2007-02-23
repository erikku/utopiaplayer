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
 * @file tagid.h The TagID block class definition
 */

#ifndef __TagID_h__
#define __TagID_h__

#include <QtCore/QString>

namespace Utopia
{

class TagID
{
public:
	bool operator==(const TagID& block);
	bool operator!=(const TagID& block);

	QString systemID() const;
	QString songID() const;

	void setSystemID(const QString& id);
	void setSongID(const QString& id);

	void clear();

	QString xml(bool encased = true) const;

protected:
	QString mSystemID;
	QString mSongID;
};

}; // namespace Utopia

#endif // __TagID_h__
