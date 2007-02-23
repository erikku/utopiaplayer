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
 * @file SongList.cpp Implementation of the SongList class.
 */

#include "SongList.h"

#include <QtCore/QSettings>
#include <QtCore/QSignalMapper>
#include <QtGui/QAction>
#include <QtGui/QHeaderView>
#include <QtSql/QSqlRelationalDelegate>
#include <iostream>

/**
 * @brief Creates a QTableView to display and handle the list of songs.
 * SongList is inhirited from DatabaseList to provide a list of the songs
 * in the database and provide hooks for various functions to perform on the songs.
 * @param parent The parent QWidget object that this instance of SongList belongs to.
 */
SongList::SongList(QWidget *parent) : DatabaseList(parent)
{
	//setItemDelegate(new QSqlRelationalDelegate(mDatabaseModel));

	// Point it to the un_songs table
	mDatabaseModel->setTable("un_songs");

	// Set the table relations
	mDatabaseModel->setRelation(3, QSqlRelation("un_artists", "ID", QString::fromUtf8("アーチスト")));
	mDatabaseModel->setRelation(4, QSqlRelation("un_albums", "ID", QString::fromUtf8("アルバム")));
	mDatabaseModel->setRelation(6, QSqlRelation("un_genres", "ID", QString::fromUtf8("ジャンル")));
	mDatabaseModel->setRelation(7, QSqlRelation("un_random", "ID", QString::fromUtf8("Random")));
	mDatabaseModel->setRelation(14, QSqlRelation("un_ratings", "ID", QString::fromUtf8("Rating")));

	// Populate the table model
	refreshTable();

	// Register the headers
	registerHeaderField(QString::fromUtf8("ID"));
	registerHeaderField(QString::fromUtf8("タイトル"), tr("Original Title"));
	registerHeaderField(QString::fromUtf8("Title"), tr("Transliterated Title"));
	registerHeaderField(QString::fromUtf8("アーチスト"), tr("Artist"));
	registerHeaderField(QString::fromUtf8("アルバム"), tr("Album"));
	registerHeaderField(QString::fromUtf8("Track"));
	registerHeaderField(QString::fromUtf8("ジャンル"), tr("Genre"));
	registerHeaderField(QString::fromUtf8("Random"), tr("Random Play"));
	registerHeaderField(QString::fromUtf8("Path"), tr("Music File Path"));
	registerHeaderField(QString::fromUtf8("Length"));
	registerHeaderField(QString::fromUtf8("TimesPlayed"), tr("Play Count"));
	registerHeaderField(QString::fromUtf8("Bitrate"));
	registerHeaderField(QString::fromUtf8("Lyrics"), tr("Lyrics File Path"));
	registerHeaderField(QString::fromUtf8("Artist"));
	registerHeaderField(QString::fromUtf8("Rating"));

	// Tell the header to show the context menu
	horizontalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);

	QAction* item = new QAction(QIcon(":/32x32/edit.png"), tr("&Edit Song..."), this);
	//connect(, SLOT(editSong()));
	addAction(item);
	setContextMenuPolicy(Qt::ActionsContextMenu);
};

QString SongList::getSongAtRow(int row) const
{
	Q_UNUSED(row)

	if(row < 0)
		return QString();

	std::cout << "Song: " << mDatabaseModel->data( mDatabaseModel->index(row, 8) ).toString().toUtf8().data() << std::endl;

	return mDatabaseModel->data( mDatabaseModel->index(row, 8) ).toString();
};

QList<int> SongList::selectedRows() const
{
	QList<int> rows;

	for(int i = 0; i < selectedIndexes().size(); i++)
	{
		rows << (selectedIndexes())[i].row();
	}

	return rows;
};
