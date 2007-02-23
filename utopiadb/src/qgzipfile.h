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

#ifndef __QGzipFile_h__
#define __QGzipFile_h__

#include <QtCore/QIODevice>
#include <zlib.h>

class QGzipFile : public QIODevice
{
	Q_OBJECT

public:
	QGzipFile(const QString& path);

	virtual bool open(OpenMode mode);
	virtual void close();

	virtual bool isSequential () const;

	virtual bool seek(qint64 pos);

protected:
	virtual qint64 readData(char *data, qint64 maxSize);
	virtual qint64 writeData(const char *data, qint64 maxSize);

protected:
	gzFile mHandle;
	QString mPath;
};

#endif // __QGzipFile_h__
