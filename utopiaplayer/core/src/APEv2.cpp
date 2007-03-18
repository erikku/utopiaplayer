/******************************************************************************\
*  Utopia Player - A cross-platform, multilingual, tagging media manager       *
*  Copyright (C) 2006-2007 John Eric Martin <john.eric.martin@gmail.com>       *
*                                                                              *
*  This program is free software; you can redistribute it and/or modify        *
*  it under the terms of the GNU General Public License version 2 as           *
*  published by the Free Software Foundation.                                  *
*                                                                              *
*  This program is distributed in the hope that it will be useful,             *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
*  GNU General Public License for more details.                                *
*                                                                              *
*  You should have received a copy of the GNU General Public License           *
*  along with this program; if not, write to the                               *
*  Free Software Foundation, Inc.,                                             *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                   *
\******************************************************************************/

#include "APEv2.h"

#include <QtCore/QFile>

namespace MetaData
{

typedef struct
{
	char magic[8]; // 'APETAGEX'
	float version; // 1.000 or 2.000
	quint32 tagSize; // Including the footer (if this is the header) and all tag items (excluding this header)
	quint32 itemCount;
	quint32 flags;
	char reserved[8]; // Must be zero
}APEv2Header;

}; // namespace MetaData

using namespace MetaData;

QString APEv2::tagType() const
{
	return "APEv2";
};

bool APEv2::fileContainsAPEv2(const QString& file, APEv2Position pos)
{
	APEv2Header header;

	QFile handle(file);
	if( !handle.open(QIODevice::ReadOnly) || handle.isSequential() || handle.size() < sizeof(APEv2Header) )
		return false;

	if(pos == Header || pos == Both)
	{
		handle.seek(0);

		if( handle.read((char*)&header, sizeof(APEv2Header)) == sizeof(APEv2Header) )
		{
			if( memcmp(header.magic, "APETAGEX", 8) == 0 )
				return true;
		}
	}

	if(pos == Footer || pos == Both)
	{
		handle.seek( handle.size() - sizeof(APEv2Header) );

		if( handle.read((char*)&header, sizeof(APEv2Header)) == sizeof(APEv2Header) )
		{
			if( memcmp(header.magic, "APETAGEX", 8) == 0 )
				return true;
		}
	}

	return false;
};
