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

#include "MP3FilePlugin.h"

#include "MP3File.h"
#include "Application.h"
#include "FileTypeFactory.h"

bool gMP3FilePluginLoaded = false;

AudioFile* createMP3File(const QString& file)
{
	return new MP3File(file);
};

MP3FilePlugin::~MP3FilePlugin()
{
	unload();
};

QString MP3FilePlugin::name() const
{
	return "MP3 File";
};

QString MP3FilePlugin::version() const
{
	return "0.1.0";
};

QStringList MP3FilePlugin::authors() const
{
	return QStringList() << "John Eric Martin <john.eric.martin@gmail.com>";
};

QString MP3FilePlugin::copyrightNotice() const
{
	return "Copyright (C) 2007 John Eric Martin";
};
	
void MP3FilePlugin::load()
{
	uApp->fileTypeFactory()->addType(createMP3File);
	gMP3FilePluginLoaded = true;
};

void MP3FilePlugin::unload()
{
	if(!gMP3FilePluginLoaded)
		return;

	uApp->fileTypeFactory()->removeType("MPEG 1 Layer 3");
	gMP3FilePluginLoaded = false;
};

bool MP3FilePlugin::isLoaded()
{
	return gMP3FilePluginLoaded;
};

Q_EXPORT_PLUGIN2(mp3fileplugin, MP3FilePlugin)
