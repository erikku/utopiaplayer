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

/**
 * @file UtopiaExport.h The utopia XML export functions
 */

#ifndef __UtopiaExport_h__
#define __UtopiaExport_h__

#include <QtCore/QObject>

// Utopia Player v0.1.0 (C) 2006 John Eric Martin / Licensed under the GPLv2 / System: 0x3D56 - ID: 0x34BB / System: 0x4CE9 - ID: 0x4F2A

QString UtopiaExport::writeSong(int id) const
{
	QSqlQuery squery( "SELECT * FROM un_songs WHERE ID = " + QString::number(id) );
	QString id = squery.record().value( QString::fromUtf8("ID") ).toString();
	QString title_en = squery.record().value( QString::fromUtf8("Title") ).toString();
	QString title_ja = squery.record().value( QString::fromUtf8("タイトル") ).toString();
	QString artistref = squery.record().value( QString::fromUtf8("Artist") ).toString();
	QString albumref = squery.record().value( QString::fromUtf8("Album") ).toString();
	QString track = squery.record().value( QString::fromUtf8("Track") ).toString();
	QString genreref = squery.record().value( QString::fromUtf8("Genre") ).toString();
	QString rating = squery.record().value( QString::fromUtf8("Rating") ).toString();
	QString lyrics = squery.record().value( QString::fromUtf8("Lyrics") ).toString();
	QString count = squery.record().value( QString::fromUtf8("TimesPlayed") ).toString();
	QString lastplayed = squery.record().value( QString::fromUtf8("LastPlayed") ).toString();
	bool random = squery.record().value( QString::fromUtf8("Random") ).toBool();
	QString bitrate = squery.record().value( QString::fromUtf8("Bitrate") ).toString();
	QString length = squery.record().value( QString::fromUtf8("Length") ).toString();
	QString file = squery.record().value( QString::fromUtf8("Path") ).toString();

	QSqlQuery arquery( "SELECT * FROM un_artists WHERE ID = " + QString::number(artistref) );
	QString arid = arquery.record().value( QString::fromUtf8("ID") ).toString();
	QString artist_en = arquery.record().value( QString::fromUtf8("Artist") ).toString();
	QString artist_ja = arquery.record().value( QString::fromUtf8("アーチスト") ).toString();

	QSqlQuery alquery( "SELECT * FROM un_albums WHERE ID = " + QString::number(albumref) );
	QString alid = alquery.record().value( QString::fromUtf8("ID") ).toString();
	QString album_en = alquery.record().value( QString::fromUtf8("Album") ).toString();
	QString album_ja = alquery.record().value( QString::fromUtf8("アルバム") ).toString();
	QString releasedate = alquery.record().value( QString::fromUtf8("ReleaseDate") ).toDate().toString(Qt::ISODate);
	QString cover = alquery.record().value( QString::fromUtf8("Cover") ).toString();

	QSqlQuery gquery( "SELECT * FROM un_genres WHERE ID = " + QString::number(genreref) );
	QString gid = alquery.record().value( QString::fromUtf8("ID") ).toString();
	QString genre_ja = alquery.record().value( QString::fromUtf8("ジャンル") ).toString();
	QString genre_en = alquery.record().value( QString::fromUtf8("Genre") ).toString();

	QString title;
	if(!title_ja.isEmpty())
		title = title_ja;
	else
		title = title_en;

	QString artist;
	if(!artist_ja.isEmpty())
		artist = artist_ja;
	else
		artist = artist_en;

	QString album;
	if(!album_ja.isEmpty())
		album = album_ja;
	else
		album = album_en;

	QStringList xmlFile;

	xmlFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	xmlFile << "<song version=\"0.1\">\n";
	xmlFile << "  <title>\n";
	if(!title_ja.isEmpty())
		xmlFile << "    <value lang=\"ja\">" + title_ja + "</value>\n";
	if(!title_en.isEmpty())
		xmlFile << "    <value lang=\"en\">" + title_en + "</value>\n";
	xmlFile << "  </title>\n";
	xmlFile << "  <artists>\n";
	xmlFile << "    <artist id="YUI">\n";
	if(!artist_ja.isEmpty())
		xmlFile << "      <value lang=\"ja\">" + artist_ja + "</value>\n";
	if(!artist_en.isEmpty())
		xmlFile << "      <value lang=\"en\">" + artist_en + "</value>\n";
	xmlFile << "    </artist>\n";
	xmlFile << "  </artists>\n";
	xmlFile << "  <year>" + releasedate + "</year>\n";
	xmlFile << "  <albums>\n";
	xmlFile << "    <album>\n";
	xmlFile << "      <track>" + track + "</track>\n";
	if(!album_ja.isEmpty())
		xmlFile << "      <value lang=\"ja\">" + album_ja + "</value>\n";
	if(!album_en.isEmpty())
		xmlFile << "      <value lang=\"en\">" + album_en + "</value>\n";
	xmlFile << "    </album>\n";
	xmlFile << "  <meta>\n";
	if(random)
		xmlFile << "    <tags>karaoke</tags>\n";
	xmlFile << "  </meta>\n";
	xmlFile << "  </albums>\n";
	xmlFile << "</song>\n";

	char* num = new char[3];
	sprintf(num, "%d2", track.number());
	QFile file(tr("%1/%2/%3 - %4.xml").arg(artist).arg(album).arg(num).arg(title));
};

#endif // __UtopiaExport_h__
