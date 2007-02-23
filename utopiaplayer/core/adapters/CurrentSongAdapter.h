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

#ifndef __CurrentSongAdapter_h__
#define __CurrentSongAdapter_h__

#include <QtDBus/QDBusAbstractAdaptor>

class CurrentSongAdaptor : public QDBusAbstractAdaptor
{
	Q_OBJECT
	Q_CLASSINFO("D-Bus Interface", "com.emotionalcoder.DBus.CurrentSong")
	Q_PROPERTY(QString album READ album)

public:
	CurrentSongAdaptor(QObject *parent) : QDBusAbstractAdaptor(parent) { };

	QString album() { return QString::fromUtf8("恋の花"); };
	QString artist() { return QString(); };
	int bitrate() { return 0; };
	int currentTime() { return 0; };
	QString genre() { return QString(); };
	QString path() { return QString(); };
	QString title() { return QString(); };
	int totalTime() { return 0; };
	int track() { return 0; };
	QString type() { return QString(); };
	QString version() { return QString(); };
	int year() { return 0; };
	int volume() { return 0; };
	int rating() { return 0; };
	int sampleRate() { return 0; };
	int score() { return 0; };
	int count() { return 0; };
};

#endif // __CurrentSongAdapter_h__
