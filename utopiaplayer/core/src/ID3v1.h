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

#ifndef __ID3v1_h__
#define __ID3v1_h__

#include "Tag.h"

namespace MetaData
{

typedef struct _ID3v1Data
{
	char    Magic[3];
	char    Title[30];
	char    Artist[30];
	char    Album[30];
	quint32 Year;
	char    Comment[29];
	quint8  Track;
	quint8  Genre;
}ID3v1Data;

class ID3v1 : Tag
{
public:
	ID3v1();
	ID3v1(const ID3v1& other);
	ID3v1(const QString& path);
	virtual ~ID3v1();

	virtual QString title() const;
	virtual QString artist() const;
	virtual QString album() const;
	virtual QString comment() const;
	virtual QString genre() const;

	virtual int year() const;
	virtual int track() const;

	virtual void setTitle(const QString& title);
	virtual void setArtist(const QString& artist);
	virtual void setAlbum(const QString& album);
	virtual void setComment(const QString& comment);
	virtual void setGenre(const QString& genre);

	virtual void setYear(int year);
	virtual void setTrack(int track);

	virtual bool isEmpty();

	virtual bool read(const QString& path);
	virtual bool write(const QString& path);

	virtual QString tagType() const;

private:
	void writeString(void *dest, const QString& src, int size);

	ID3v1Data *d;
};

}; // namespace MetaData

#endif // __ID3v1_h__
