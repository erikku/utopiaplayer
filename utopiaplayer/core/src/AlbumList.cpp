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
 * @file AlbumList.cpp Implementation of the AlbumList class.
 */

#include "AlbumList.h"

#include <QtGui/QAction>
#include <QtGui/QHeaderView>
#include <QtSql/QSqlRelation>
#include <QtSql/QSqlRelationalDelegate>

/**
 * @brief Creates a QTableView to display and handle the list of songs.
 * AlbumList is inhirited from DatabaseList to provide a list of the albums
 * in the database and provide hooks for various functions to perform on the albums.
 * @param parent The parent QWidget object that this instance of AlbumList belongs to.
 */
AlbumList::AlbumList(QWidget *parent) : DatabaseList(parent)
{
	//setItemDelegate(new QSqlRelationalDelegate(mDatabaseModel));

	// Point it to the un_albums table
	mDatabaseModel->setTable("un_albums");

	// Set the table relations
	mDatabaseModel->setRelation(4, QSqlRelation());

	// Populate the table model
	refreshTable();

	// Register the headers
	registerHeaderField(QString::fromUtf8("ID"));
	registerHeaderField(QString::fromUtf8("アルバム"), tr("Original Album"));
	registerHeaderField(QString::fromUtf8("Album"), tr("Transliterated Album"));
	registerHeaderField(QString::fromUtf8("ReleaseDate"), tr("Release Date"));
	registerHeaderField(QString::fromUtf8("Cover"), tr("Cover File Path"));

	// Tell the header to show the context menu
	horizontalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);

	QAction* item = new QAction(QIcon(":/32x32/edit.png"), tr("&Edit Album..."), this);
	//connect(, SLOT(editAlbum()));
	addAction(item);
	setContextMenuPolicy(Qt::ActionsContextMenu);
};
