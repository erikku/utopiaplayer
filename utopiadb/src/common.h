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
 * @file common.h Some common UtopiaDB stuff
 */

#ifndef __Common_h__
#define __Common_h__

#include <QtCore/QStack>
#include <QtCore/QLocale>
#include <QtCore/QString>
#include <QtXml/QXmlAttributes>

/// The Utopia namespace, where everything happens!
namespace Utopia
{

/// The current system language
#define CURRENT_LANG QLocale::system().name().section('_', 0, 0)

class UtopiaBlock;
class Individual;
class Publisher;
class Artist;
class Composer;
class Staff;
class Mood;
class Genre;
class Cover;
class Credit;
class Album;
class AlbumSet;
class Song;
class SongEdition;
class SongFile;
class SongSet;
class TagID;
//class Lyrics;

//class UtopiaFactory;

typedef quint32 uid;

typedef struct _Track
{
	int disc;
	int track;
}Track;

class TypeParser
{
public:
	TypeParser()
	{
		mBlock = 0;
		mElements.push("__base__");
	};

	virtual bool startDocument() = 0;
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts) = 0;
	virtual bool characters(const QString& ch) = 0;
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName) = 0;
	virtual bool endDocument() = 0;

	virtual UtopiaBlock* block() const { return mBlock; };

protected:
	UtopiaBlock *mBlock;
	QStack<QString> mElements;
	QStack<QXmlAttributes> mAtts;
};

/// @todo Manga stuff (and move it somewhere else
/*
#define IssueIdent QPair<bool, QString>

typedef enum AgeRating { EC, E, E10, T, M, AO };

typedef enum CopyType { PHYSICAL, ELECTRONIC };

typedef enum Visibility
{
	PUBLIC,
	REGISTERED,
	FRIENDS,
	AFRIENDS,
	PRIVATE
};
*/

}; // namespace Utopia

#endif // __Common_h__
