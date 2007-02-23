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

#ifndef __iTunesLibraryPreParser_h__
#define __iTunesLibraryPreParser_h__

#include <QtCore/QStack>
#include <QtCore/QVariant>
#include <QtXml/QXmlDefaultHandler>

class iTunesLibraryPreParser : public QXmlDefaultHandler
{
public:
	virtual bool startDocument();
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
	virtual bool characters(const QString& ch);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);
	virtual bool endDocument();

	int songCount();
	int playlistCount();
	QString libraryID() const;
	QString musicFolder() const;

protected:
	int mSongCount;
	int mPlaylistCount;

	QString mCurrentKey;
	QString mCurrentElement;

	QString mLibraryID;
	QString mMusicFolder;

	QStack<QString> mDicts;
};

#endif // __iTunesLibraryPreParser_h__
