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

#include "qgzipfile.h"

QGzipFile::QGzipFile(const QString& path)
{
	mPath = path;
	mHandle = NULL;
};

bool QGzipFile::open(OpenMode mode)
{
	if(mode & QIODevice::ReadOnly)
		mHandle = gzopen(mPath.toLocal8Bit().data(), "rb");
	else if(mode & QIODevice::ReadWrite)
		mHandle = gzopen(mPath.toLocal8Bit().data(), "wb+");
	else if(mode & QIODevice::WriteOnly)
		mHandle = gzopen(mPath.toLocal8Bit().data(), "wb");

	if(mHandle == NULL)
		return false;

	return QIODevice::open(mode);
};

void QGzipFile::close()
{
	QIODevice::close();
	if(mHandle) gzclose(mHandle);
	mHandle = NULL;
};

bool QGzipFile::isSequential() const
{
	return true;
};

bool QGzipFile::seek(qint64 pos)
{
	return (gzseek(mHandle, pos, SEEK_SET) != -1);
};

qint64 QGzipFile::readData(char *data, qint64 maxSize)
{
	if(mHandle == NULL)
		return 0;

	return gzread(mHandle, data, maxSize);
};

qint64 QGzipFile::writeData(const char *data, qint64 maxSize)
{
	if(mHandle == NULL)
		return 0;

	return gzwrite(mHandle, data, maxSize);
};
