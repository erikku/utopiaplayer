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

#include "iTunesLibraryImportExport.h"
#include "iTunesImportOptions.h"
#include "Application.h"

#include <utopiadb/metabase.h>

#include <QtCore/QUrl>
#include <QtCore/QDateTime>

#include <QtGui/QAction>
#include <QtGui/QMessageBox>

iTunesLibraryImportExport::iTunesLibraryImportExport() : ImportExportInterface(0)
{
	mImportAction = new QAction(tr("iTunes Music Library..."), 0);
	connect(mImportAction, SIGNAL(triggered()), this, SLOT(doImport()));
	mExportAction = new QAction(tr("iTunes Music Library..."), 0);
	connect(mExportAction, SIGNAL(triggered()), this, SLOT(doExport()));
	//QStringList albumcovers = listRecursiveDirectoryContents(QDir("/media/windows/Documents and Settings/Eric/My Documents/My Music/iTunes/Album Artwork/Local/34A6B8C643F01262"), QStringList() << "*.itc");
};

iTunesLibraryImportExport::~iTunesLibraryImportExport()
{
	delete mImportAction;
	delete mExportAction;
};

QAction* iTunesLibraryImportExport::importAction()
{
	return mImportAction;
};

QAction* iTunesLibraryImportExport::exportAction()
{
	return mExportAction;
};

void iTunesLibraryImportExport::doImport()
{
	(new iTunesImportOptions)->show();
};

void iTunesLibraryImportExport::doExport()
{
};

bool iTunesLibraryParser::startDocument()
{
	mLibraryID.clear();
	mMusicFolder.clear();

	mDicts.clear();
	mElements.clear();
	mCurrentDict.clear();

	mCurrentKey = QString();
	mDicts << "BASE";
	mElements << "BASE";

	return true;
};

bool iTunesLibraryParser::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
	mElements.push(localName);

	if( localName == QString("dict") )
	{
		mDicts.push(mCurrentKey);
		mCurrentDict.clear();
	}

	if( mCurrentKey == QString("Compilation") )
	{
		if(localName == QString("true") || localName == QString("false"))
			mCurrentDict[mCurrentKey] = localName;
	}

	return true;
};

bool iTunesLibraryParser::characters(const QString& ch)
{
	if( mElements.top() == QString("key") )
	{
		mCurrentKey = ch.trimmed();
	}
	else if( mElements.top() == QString("integer") )
		mCurrentDict[mCurrentKey] = ch.trimmed().toInt();
	else if( mElements.top() == QString("real") )
		mCurrentDict[mCurrentKey] = ch.trimmed().toFloat();
	else if( mElements.top() == QString("string") )
		mCurrentDict[mCurrentKey] = ch.trimmed();
	else if( mElements.top() == QString("date") )
		mCurrentDict[mCurrentKey] = QDateTime::fromString(ch.trimmed(), Qt::ISODate);

	return true;
};

bool iTunesLibraryParser::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	if(mElements.top() == localName)
		mElements.pop();
	else
		return false; // We need to tell it the error at some point

	if(mDicts.top().isEmpty() && mCurrentKey == "Tracks")
	{
		if(mCurrentDict.contains("Music Folder"))
		{
			QUrl url = QUrl::fromEncoded(mCurrentDict.value("Music Folder").toByteArray());
			mMusicFolder = url.toLocalFile().replace("//localhost/", "");
			uDebug("iTunesLibraryParser", mMusicFolder);
		}
		if(mCurrentDict.contains("Library Persistent ID"))
		{
			mLibraryID = mCurrentDict.value("Library Persistent ID").toString().trimmed();
			uDebug("iTunesLibraryParser", mLibraryID);
		}
	}

	if( localName == QString("dict") )
	{
		mDicts.pop();
		if( mDicts.top() == QString("Tracks") )
			proccessSong(mCurrentDict);

		mCurrentDict.clear();
	}

	return true;
};

bool iTunesLibraryParser::endDocument()
{
	return true;
};

//#include <taglib.h>
//#include <fileref.h>
//#include <tstring.h>
//#include <tag.h>
//#include <id3v2framefactory.h>

/*
 * Possible Keys
 * =============
 * Track ID
 * Name
 * Artist
 * Album
 * Album Artist
 * Artwork Count
 * Genre
 * Kind
 * Size
 * Total Time
 * Disc Number
 * Disc Count
 * Track Number
 * Track Count
 * Track Type
 * Year
 * Date Modified
 * Date Added
 * Bit Rate
 * Sample Rate
 * Play Count
 * Play Date
 * Play Date UTC
 * File Type
 * File Creator
 * Location
 * File Folder Count
 * Library Folder Count
 * Compilation
 * Persistent ID
 */
void iTunesLibraryParser::proccessSong(const QMap<QString, QVariant>& keyPairs)
{
	// Get the path to the file
	QUrl url = QUrl::fromEncoded(keyPairs.value("Location").toByteArray());
	QString path = url.toLocalFile(); // QUrl::fromPercentEncoding( url.toEncoded(QUrl::RemoveScheme) );
	path = path.replace("//localhost/", "");
	path = path.replace(mMusicFolder, "/media/utopia/Music/");
	path = uApp->makePathCaseSensitive(path);

	// Check the file exists
	/*if(!QFile(path).exists())
	{
		QMessageBox::information(0, uApp->applicationName(), QObject::tr("File not found. We will skip adding this song.\n%1").arg(path));
		return;
	}*/
	/*
	Utopia::SongFile file;
	file.setPath(path);
	if(keyPairs.value("Kind").toString() == "MPEG audio file")
		file.setFormat("mp3");

	if(!uApp->metaBase()->containsArtistName(keyPairs.value("Artist").toString()))
	{
		uApp->metaBase()->addBlock( Utopia::Artist(keyPairs.value("Artist").toString()) );
	}

	Utopia::Artist artist = uApp->metaBase()->artistFromName(keyPairs.value("Artist").toString());

	Utopia::Album album;
	if(!uApp->metaBase()->containsAlbumTitle(keyPairs.value("Album").toString()))
	{
		album.addAlbumTitle( keyPairs.value("Album").toString() );
		album.addArtist(artist.id());
		if(keyPairs.value("Compilation").toString() == "true")
			album.setCompilation(true);
		album.setReleaseDate( QDate(keyPairs.value("Year").toInt(), 1, 1) );
		uApp->metaBase()->addBlock( album );
	}

	album = uApp->metaBase()->albumFromTitle(keyPairs.value("Album").toString());
	album.addTrack(0, keyPairs.value("Track Number").toInt(), keyPairs.value("Disc Number").toInt());
	uApp->metaBase()->updateBlock( album );
	*/
	/*
	if( mFiles.contains( keyPairs.value("Name").toString().trimmed() ) )
	{
		path = mFiles2.at( mFiles.indexOf( keyPairs.value("Name").toString().trimmed() ) );
	}

	uDebug("iTunesLibraryParser", tr("File: %1").arg(path));

	TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding( TagLib::String::UTF8 );

	TagLib::FileRef f( path.toUtf8().data() );

	if(f.isNull())
	{
		std::cerr << "Error reading file: " << path.toUtf8().data() << std::endl;
		return;
	}
	if(!f.tag())
	{
		std::cerr << "Error reading tag: " << path.toUtf8().data() << std::endl;
		return;
	}

	f.tag()->setTitle( TagLib::String(std::string(keyPairs.value("Name").toString().trimmed().toUtf8().data()), TagLib::String::UTF8) );
	f.tag()->setArtist( TagLib::String(std::string(keyPairs.value("Artist").toString().trimmed().toUtf8().data()), TagLib::String::UTF8) );
	f.tag()->setAlbum( TagLib::String(std::string(keyPairs.value("Album").toString().trimmed().toUtf8().data()), TagLib::String::UTF8) );
	f.tag()->setComment( TagLib::String("Music tagged with Utopia Player") );
	f.tag()->setGenre( TagLib::String(std::string(keyPairs.value("Genre").toString().trimmed().toUtf8().data()), TagLib::String::UTF8) );
	f.tag()->setYear( keyPairs.value("Year").toInt() );
	f.tag()->setTrack( keyPairs.value("Track Number").toInt() );

	f.save();

	uDebug("iTunesLibraryParser", tr("Wrote tag: %1").arg( keyPairs.value("Name").toString() ));
	*/
};
