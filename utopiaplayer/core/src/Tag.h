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

#ifndef __Tag_h__
#define __Tag_h__

#include <QtCore/QObject>
#include <QtCore/QString>

namespace MetaData
{

class Tag : public QObject
{
	Q_OBJECT

public:
	Tag(QObject *parent = 0) : QObject(parent) { };

	virtual QString title() const = 0;
	virtual void setTitle(const QString& title) = 0;

	virtual QString artist() const = 0;
	virtual void setArtist(const QString& artist) = 0;

	virtual QString album() const = 0;
	virtual void setAlbum(const QString& album) = 0;

	virtual QString comment() const = 0;
	virtual void setComment(const QString& comment) = 0;

	virtual QString genre() const = 0;
	virtual void setGenre(const QString& genre) = 0;

	virtual int year() const = 0;
	virtual void setYear(int year) = 0;

	virtual int track() const = 0;
	virtual void setTrack(int track) = 0;

	virtual void clear() = 0;
	virtual bool isEmpty() = 0;

	virtual QString encoding() const = 0;
	virtual QString defaultEncoding() const = 0;

	virtual Tag* duplicate() = 0;

	virtual qint64 size() = 0;
	virtual QByteArray tagData() const = 0;

	// File operations //
	virtual void removeTag(const QString& path) = 0;
	virtual qint64 position(const QString& path) = 0;
	virtual bool containsTag(const QString& path) = 0;
	virtual bool conformsToSpec(const QString& path) = 0;

	virtual bool read(const QString& path, const QString& encoding = QString()) = 0;
	virtual bool write(const QString& path, const QString& encoding = QString()) = 0;

	virtual bool hasAdvancedFeatures() { return false; };

	virtual QString type() const = 0;
};

}; // namespace MetaData

#endif // __Tag_h__
