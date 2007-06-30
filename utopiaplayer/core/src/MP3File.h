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

#ifndef __MP3File_h__
#define __MP3File_h__

#include "AudioFile.h"

class MP3File : public AudioFile
{
public:
	MP3File(const QString& path);
	virtual ~MP3File();

	virtual void close();
	virtual bool load();
	virtual bool save();

	virtual bool rewind();
	virtual bool seek(quint32 sample);
	virtual int readSamples(float **samples, int count);

	virtual bool isOpen() const;
	virtual bool isValid() const;

	virtual QString type() const;
	virtual QString mimeType() const;
	virtual QStringList extensions() const;

protected:
	bool mOpen;
};

#endif // __MP3File_h__
