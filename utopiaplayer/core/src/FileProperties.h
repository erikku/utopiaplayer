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

#ifndef __FileProperties_h__
#define __FileProperties_h__

#include "ui_FileProperties.h"

class AudioFile;

namespace MetaData
{
	class Tag;
	class AdvancedTag;
};

class FileProperties : public QWidget
{
	Q_OBJECT

public:
	FileProperties(QWidget *parent = 0);
	FileProperties(AudioFile *file, QWidget *parent = 0);

public slots:
	void populate(AudioFile *file);
	void populateTag(MetaData::Tag *tag);
	void populateTag(MetaData::AdvancedTag *tag);

protected:
	QString sizeToString(quint64 size) const;
	QString secondsToString(quint32 seconds) const;

	Ui::FileProperties ui;
};

#endif // __FileProperties_h__
