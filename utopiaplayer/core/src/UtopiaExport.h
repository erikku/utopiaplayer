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

/**
 * @file UtopiaExport.h The utopia XML export functions
 */

#ifndef __UtopiaExport_h__
#define __UtopiaExport_h__

#include <QtCore/QObject>

class OutputPlugin
{
public:
	OutputPlugin(const QString&) {};

	virtual void write()
	{
		this->writeHeader():
		this->writeSongs():
		this->writeAlbums():
		this->writePlaylists():
		this->writeFooter():
	};

	//virtual void registerPlugin(QMenu*) = 0;
protected:
    virtual void writeHeader() = { };
	virtual void writeSongs() = { };
	virtual void writeAlbums() = { };
	virtual void writePlaylists() = { };
	virtual void writeFooter() = { };

private:
	QStringList mDocument;
};

void OutputPlugin::writeHeader()
{
	QSqlQuery query("LOCK TABLES `un_songs` WRITE, `un_albums` WRITE, `un_artists` WRITE, `un_genres` WRITE");

	mDocument << "<?xml version='1.0' encoding='UTF-8' ?>" << endl;
	mDocument << "<utopiadb version='0.1'>" << endl;
};

void OutputPlugin::writeSongs()
{
	QSqlQuery query("SELECT * FROM `un_songs`");

	while(query.next())
	{
		QString id = query.record().value( QString::fromUtf8("ID") ).toString();
		QString title_en = query.record().value( QString::fromUtf8("Title") ).toString();
		QString title_ja = query.record().value( QString::fromUtf8("タイトル") ).toString();
		QString artistref = query.record().value( QString::fromUtf8("Artist") ).toString();
		QString albumref = query.record().value( QString::fromUtf8("Album") ).toString();
		QString track = query.record().value( QString::fromUtf8("Track") ).toString();
		QString genreref = query.record().value( QString::fromUtf8("Genre") ).toString();
		QString rating = query.record().value( QString::fromUtf8("Rating") ).toString();
		QString count = query.record().value( QString::fromUtf8("TimesPlayed") ).toString();
		QString lastplayed = query.record().value( QString::fromUtf8("LastPlayed") ).toString();
		QString random = query.record().value( QString::fromUtf8("Random") ).toString();
		QString bitrate = query.record().value( QString::fromUtf8("Bitrate") ).toString();
		QString length = query.record().value( QString::fromUtf8("Length") ).toString();
		QString file = query.record().value( QString::fromUtf8("Path") ).toString();
		
		QString title_ja = query.record().value( QString::fromUtf8("タイトル") ).toString();
		
		mDocument << "  <song>" << endl;
		mDocument << "    <ids>" << endl;
		mDocument << "      <id><system>0x12EF</system><song>0x34CD</song></id>" << endl;
		mDocument << "    </ids>" << endl;
		if(!title_en.isEmpty())
		{
			mDocument << "    <title lang='en_US'>" + title_en + "</title>";
		}
		if(!title_ja.isEmpty())
		{
			mDocument << "    <title lang='ja_JP'>" + title_ja + "</title>";
		}
		mDocument << "    <artistref>" << artistref << "</artistref>" << endl;
		mDocument << "    <albumref disc='1' track='" << track << "'>" << albumref << "</albumref>" << endl;
		mDocument << "    <genreref>" << genreref << "</genreref>" << endl;
		mDocument << "    <format>MPEG Layer 3</format>" << endl;
		mDocument << "    <rating>" + rating + "</rating>";
		mDocument << "    <playcount>" + count + "</playcount>";
		mDocument << "    <lastplayed>" + lastplayed + "</lastplayed>";
		mDocument << "    <random>" + random + "</random>";
		mDocument << "    <bitrate>" + bitrate + "</bitrate>";
		mDocument << "    <length>" + length + "</length>";
		mDocument << "    <file>" + file + "</file>";
		if(!title_en.isEmpty())
		{
			mDocument << "    <xml>" << title_en << ".xml</xml>" << endl;
		}
		else
		{
			mDocument << "    <xml>" << title_ja << ".xml</xml>" << endl;
		}
		mDocument << "  </song>" << endl;

		/*
		// Title
		QString title_en = query.record().value( QString::fromUtf8("Title") ).toString();
		mDocument << "      <title lang='en'>" + title_en + "</title>";
		QString title_ja = query.record().value( QString::fromUtf8("タイトル") ).toString();
		mDocument << "      <title lang='ja'>" + title_ja + "</title>";

		// Artist
		QSqlQuery artist("SELECT * FROM `un_artists` WHERE `ID` = '" +
			query.record().value( QString::fromUtf8("Artist") ).toString() + "' LIMIT 1");
		QString artist_en = artist.record().value( QString::fromUtf8("Artist") ).toString();
		mDocument << "      <artist lang='en'>" + artist_en + "</artist>";
		QString artist_ja = artist.record().value( QString::fromUtf8("アーチスト") ).toString();
		mDocument << "      <artist lang='ja'>" + artist_ja + "</artist>";

		// Album
		QSqlQuery album("SELECT * FROM `un_albums` WHERE `ID` = '" +
			query.record().value( QString::fromUtf8("Album") ).toString() + "' LIMIT 1");
		QString album_en = album.record().value( QString::fromUtf8("Album") ).toString();
		mDocument << "      <album lang='en'>" + album_en + "</album>";
		QString album_ja = album.record().value( QString::fromUtf8("アルバム") ).toString();
		mDocument << "      <album lang='ja'>" + album_ja + "</album>";

		// Genre
		QSqlQuery genre("SELECT * FROM `un_genres` WHERE `ID` = '" +
			query.record().value( QString::fromUtf8("Genre") ).toString() + "' LIMIT 1");
		QString genre_en = genre.record().value( QString::fromUtf8("Genre") ).toString();
		mDocument << "      <genre lang='en'>" + genre_en + "</genre>";
		QString genre_ja = genre.record().value( QString::fromUtf8("ジャンル") ).toString();
		mDocument << "      <genre lang='ja'>" + genre_ja + "</genre>";

		QString track = query.record().value( QString::fromUtf8("Track") ).toString();
		mDocument << "      <track>" + track + "</track>";
		QString random = query.record().value( QString::fromUtf8("Random") ).toString();
		mDocument << "      <random>" + random + "</random>";
		QString rating = query.record().value( QString::fromUtf8("Rating") ).toString();
		mDocument << "      <rating>" + rating + "</rating>";
		QString count = query.record().value( QString::fromUtf8("TimesPlayed") ).toString();
		mDocument << "      <count>" + count + "</count>";
		QString bitrate = query.record().value( QString::fromUtf8("Bitrate") ).toString();
		mDocument << "      <bitrate>" + bitrate + "</bitrate>";
		QString length = query.record().value( QString::fromUtf8("Length") ).toString();
		mDocument << "      <length>" + length + "</length>";
		QString format = QString("MPEG Layer 3");
		mDocument << "      <format>" + format + "</format>";
		QString file = query.record().value( QString::fromUtf8("Path") ).toString();
		mDocument << "      <file>" + file + "</file>";
		QString lyrics = query.record().value( QString::fromUtf8("Lyrics") ).toString();
		mDocument << "      <lyrics>" + lyrics + "</lyrics>";
		QString lastplayed = query.record().value( QString::fromUtf8("LastPlayed") ).toString();
		mDocument << "      <lastplayed>" + lastplayed + "</lastplayed>";
		mDocument << "    </song>";
		*/
	}
};

void OutputPlugin::writeAlbums()
{
	mDocument << "  <albums>";

	mDocument << "    <album>";
	mDocument << "      <artist lang='en'>" + artist_en + "</artist>";
	mDocument << "      <artist lang='ja'>" + artist_ja + "</artist>";
	mDocument << "      <album lang='en'>" + album_en + "</album>";
	mDocument << "      <album lang='ja'>" + album_ja + "</album>";
	mDocument << "      <tracks>" + tracks + "</tracks>";
	mDocument << "      <discs>" + discs + "</discs>";
	mDocument << "      <compilation>" + compilation + "</compilation>";
	mDocument << "      <date>" + date + "</date>";
	mDocument << "      <cover>" + cover + "</cover>";
	mDocument << "    </album>";

	mDocument << "  </albums>";
};

void OutputPlugin::writeFooter()
{
	mDocument << "</database>";

	QSqlQuery query("UNLOCK TABLES");
};


#endif // __UtopiaExport_h__
