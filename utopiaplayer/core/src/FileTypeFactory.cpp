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

#include "FileTypeFactory.h"

#include "MP3File.h"
#include "OGGFile.h"
#include "WavPackFile.h"

AudioFile* createMP3File(const QString& file)
{
	return new MP3File(file);
};

AudioFile* createOGGFile(const QString& file)
{
	return new OGGFile(file);
};

AudioFile* createWavPackFile(const QString& file)
{
	return new WavPackFile(file);
};

FileTypeFactory::FileTypeFactory()
{
	addType(createMP3File);
	addType(createOGGFile);
	addType(createWavPackFile);
};

void FileTypeFactory::addType(AudioFile* (*function)(const QString&))
{
	AudioFile *type = function( QString() );

	mFileTypes[type->type()] = function;

	delete type;
};

void FileTypeFactory::removeType(const QString& name)
{
	mFileTypes.remove(name);
};

QStringList FileTypeFactory::typeNames() const
{
	return QStringList(mFileTypes.keys());
};

QList<AudioFile* (*)(const QString&)> FileTypeFactory::creatorFunctions() const
{
	return mFileTypes.values();
};

AudioFile* FileTypeFactory::getHandle(const QString& path)
{
	AudioFile *file = 0;

	foreach(AudioFile* (*function)(const QString&), mFileTypes.values())
	{
		file = function(path);

		if(file->isValid())
			break;

		delete file;
		file = 0;
	}

	return file;
};
