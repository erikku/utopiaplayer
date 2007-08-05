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

/**
 * @file cover.h The Cover block class definition
 */

#ifndef __Cover_h__
#define __Cover_h__

#include <QtGui/QPixmap>

#include "utopiablock.h"

namespace Utopia
{

class CoverData : public QSharedData
{
public:
	/// The path to the cover image
	QString mPath;
	/// A QPixmap of the cover image
	QPixmap mCover;
};

class Cover : public UtopiaBlock
{
public:
	Cover();
	Cover(const QString& path);

	bool operator==(const Cover& block);
	bool operator!=(const Cover& block);

	QString path() const;
	QPixmap cover() const;

	virtual QStringList type() const { return QStringList() << "Cover" << UtopiaBlock::type(); };

	void setPath(const QString& path);
	void clearPath();

	void setCover(const QPixmap& cover);
	void clearCover();

	void load();
	void save();

	virtual void clear();

protected:
	virtual void xmlSegment(QXmlStreamWriter *writer, bool encased = true) const;

private:
	QSharedDataPointer<CoverData> d;
};

class CoverParser : public UtopiaBlockParser
{
public:
	CoverParser() : UtopiaBlockParser() { };

	virtual bool startDocument();
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __Cover_h__
