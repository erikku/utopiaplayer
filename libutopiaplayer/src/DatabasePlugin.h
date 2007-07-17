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
 * @file DatabasePlugin.h The base class defining database engines/plugins
 */

#ifndef __DatabasePlugin_h__
#define __DatabasePlugin_h__

#include <QtCore/QObject>

class DatabasePlugin : public QObject
{
	Q_OBJECT

public:
	virtual ~DatabasePlugin() {};

	virtual bool isConnected() { return false; };
	
	virtual QWidget* configurationWidget() = 0;

public slots:
	virtual void openConnection(const QString profileName &);
	
	write(Song*);
	write(Artist*);
	write(Album*);
	write(Genre*);
	
	merge(Song*, Song*, Song*);
	merge(Artist*, Artist*, Artist*);
	merge(Album*, Album*, Album*);
	merge(Genre*, Genre*, Genre*);
	
	update();
	remove();
	
	QList<UtopiaObject*> find(const QRegExp &, UtopiaObjects objects);

	Song*	fetch();
	Song*	fetch(const QString title &);
	Artist*	fetch();
	Album*	fetch();
	Genre*	fetch();

protected:
};

#define UTOPIA_OBJECTS_MIN 0
#define UTOPIA_OBJECTS_MAX 3

// UtopiaModules
// Music - 0-3
// Manga
// Anime

enum UtopiaObjects
{
	UN_SONG = 0,
	UN_ARTIST,
	UN_ALBUM,
	UN_GENRE
};

#endif // __DatabasePlugin_h__
