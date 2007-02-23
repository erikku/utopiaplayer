/******************************************************************************\
*  Utopia Player - A cross-platform, multilingual, tagging media manager       *
*  Copyright (C) 2006-2007 John Eric Martin <cpuwhiz105@users.sourceforge.net> *
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

#ifndef __WavPackFile_h__
#define __WavPackFile_h__

#include "AudioFile.h"

#include <wavpack/wavpack.h>

class WavPackFile : public AudioFile
{
public:
	WavPackFile(const QString& path);
	virtual ~WavPackFile();

	virtual void close();
	virtual bool load();
	virtual bool save();

	virtual bool rewind();
	virtual bool seek(quint32 sample);
	virtual int readSamples(float **samples, int count);

	virtual bool isOpen() const;
	virtual bool isValid() const;

	virtual QString type() const;

protected:
	int32_t *wvBuffer;
	char wvError[80];
	WavpackContext *wvContext;
};

#endif // __WavPackFile_h__
