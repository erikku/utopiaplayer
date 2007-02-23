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

#include "iTunesLibraryPreParser.h"

#include <QtCore/QUrl>

bool iTunesLibraryPreParser::startDocument()
{
	mSongCount = 0;
	mPlaylistCount = 0;
	mLibraryID.clear();
	mMusicFolder.clear();

	mDicts.clear();
	mCurrentKey = "Main";
	mCurrentElement.clear();

	mDicts << "BASE";

	return true;
};

bool iTunesLibraryPreParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
	mCurrentElement = localName;

	if( localName == "dict" )
		mDicts.push(mCurrentKey);

	return true;
};

bool iTunesLibraryPreParser::characters(const QString& ch)
{
	if( mCurrentElement == "key" )
	{
		mCurrentKey = ch.trimmed();
		return true;
	}

	if(mDicts.top() != "Main")
		return true;

	if( mCurrentElement == "string" )
	{
		if(mCurrentKey == "Music Folder")
		{
			QUrl url = QUrl::fromEncoded(ch.trimmed().toUtf8());
			mMusicFolder = url.toLocalFile().replace("//localhost/", "");
		}
		if(mCurrentKey == "Library Persistent ID")
		{
			mLibraryID = ch.trimmed();
		}
	}

	return true;
};

bool iTunesLibraryPreParser::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	mCurrentElement.clear();

	if( localName == "dict" )
	{
		mDicts.pop();
		if( mDicts.top() == "Tracks" )
			mSongCount++;
		else if( mDicts.top() == "Playlists" )
			mPlaylistCount++;
	}

	return true;
};

bool iTunesLibraryPreParser::endDocument()
{
	return true;
};

int iTunesLibraryPreParser::songCount()
{
	return mSongCount;
};

int iTunesLibraryPreParser::playlistCount()
{
	return mPlaylistCount - 1;
};

QString iTunesLibraryPreParser::libraryID() const
{
	return mLibraryID;
};

QString iTunesLibraryPreParser::musicFolder() const
{
	return mMusicFolder;
};
