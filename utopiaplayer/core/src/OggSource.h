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

#ifndef __OggSource_h__
#define __OggSource_h__

#include "MediaSourceInterface.h"

#include <QtCore/QUrl>

class OggSource : public MediaSourceInterface
{
	Q_OBJECT

public:
	OggSource(QObject *parent = 0, const QStringList& args = QStringList());
	~OggSource();

	virtual QString pluginName() const { return tr("OGG Media Source") };
	virtual PluginType pluginType() { return MediaSourcePlugin; };

public slots:
	virtual void setURL(const QUrl& url);

protected:
	void open();
	void close();

	int mCurrentSection;
	FILE *mFileHandle;
	OggVorbis_File mVorbisFile;
	vorbis_info *mVorbisInfo;
    ogg_int64_t mFileLength;
};

#endif // __OggSource_h__
