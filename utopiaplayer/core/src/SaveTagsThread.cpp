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

#include "SaveTagsThread.h"

#include <iostream>
//#include <id3v2framefactory.h>

SaveTagsThread::SaveTagsThread(QSqlDatabase db)
{
	// Setup some taglib stuff
	//TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding( TagLib::String::UTF8 );
	
	database = db;
};

void SaveTagsThread::run()
{
	/*
	QSettings settings;
	QString mMusicDirectory = settings.value("General/MusicDirectory").toString();
	int mUseKanji = settings.value("General/UseKanji").toInt();

	QSqlQuery query(QString::fromUtf8("SELECT * FROM `un_songs`"), database);

	int count = 0;

    while (query.next())
	{
		emit valueChanged(++count);

		QString title;
		QString album;
		QString artist;
		QString genre;
		
		QSqlQuery qartist(QString::fromUtf8("SELECT * FROM `un_artists` WHERE `ID` = ") + query.record().value( QString::fromUtf8("Artist") ).toString() + QString::fromUtf8(""), database);
		QSqlQuery qalbum(QString::fromUtf8("SELECT * FROM `un_albums` WHERE `ID` = ") + query.record().value( QString::fromUtf8("Album") ).toString() + QString::fromUtf8(""), database);
		QSqlQuery qgenre(QString::fromUtf8("SELECT * FROM `un_genres` WHERE `ID` = ") + query.record().value( QString::fromUtf8("Genre") ).toString() + QString::fromUtf8(""), database);
		
		qartist.next();
		qalbum.next();
		qgenre.next();

		if(mUseKanji == Qt::Checked)
		{
			title = query.record().value( QString::fromUtf8("タイトル") ).toString();
			artist = qartist.record().value( QString::fromUtf8("アーチスト") ).toString();
			album = qalbum.record().value( QString::fromUtf8("アルバム") ).toString();
			genre = qgenre.record().value( QString::fromUtf8("ジャンル") ).toString();
		}
		else
		{
			title = query.record().value( QString::fromUtf8("Title") ).toString();
			artist = qartist.record().value( QString::fromUtf8("Artist") ).toString();
			album = qalbum.record().value( QString::fromUtf8("Album") ).toString();
			genre = qgenre.record().value( QString::fromUtf8("Genre") ).toString();
		}

		QString path = mMusicDirectory + query.record().value( QString::fromUtf8("Path") ).toString();

		TagLib::FileRef f( path.toUtf8().data() );

		f.tag()->setTitle( TagLib::String(std::string(title.toUtf8().data()), TagLib::String::UTF8) );
		f.tag()->setArtist( TagLib::String(std::string(artist.toUtf8().data()), TagLib::String::UTF8) );
		f.tag()->setAlbum( TagLib::String(std::string(album.toUtf8().data()), TagLib::String::UTF8) );
		f.tag()->setComment( TagLib::String("Music from Utopia Network <www.utopia.net>\nTagged with UtopiaPlayer, Copyright (C) 2006 John Eric Martin <cpuwhiz105@users.sourceforge.net>") );
		f.tag()->setGenre( TagLib::String(std::string(genre.toUtf8().data()), TagLib::String::UTF8) );
		f.tag()->setYear( qalbum.record().value( QString::fromUtf8("ReleaseDate") ).toDate().year() );
		f.tag()->setTrack( query.record().value( QString::fromUtf8("Track") ).toInt() );

		f.save();
		// orugooru オルゴール
	}
	*/
	emit finished();
};
