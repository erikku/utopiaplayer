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

#include "iTunesImportOptions.h"
#include "iTunesLibraryPreParser.h"
#include "Application.h"

#include <QtGui/QFileDialog>

iTunesImportOptions::iTunesImportOptions(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	setFixedSize(size());
	setWindowFlags(Qt::Dialog);
	setWindowModality(Qt::WindowModal);
	setAttribute(Qt::WA_DeleteOnClose);

	ui.iTunesFolderBrowse->setIcon(uApp->icon("filesystems/folder_open"));
	ui.MusicFolderBrowse->setIcon(uApp->icon("filesystems/folder_open"));

	makePalette();

	connect(ui.iTunesFolderEdit, SIGNAL(textChanged(const QString&)), this, SLOT(preprocess(const QString&)));
	connect(ui.MusicFolderEdit, SIGNAL(textChanged(const QString&)), this, SLOT(checkpaths()));
	connect(ui.iTunesFolderBrowse, SIGNAL(clicked()), this, SLOT(browseLibrary()));
	connect(ui.MusicFolderBrowse, SIGNAL(clicked()), this, SLOT(browseMusic()));
	connect(ui.CancelButton, SIGNAL(clicked()), this, SLOT(close()));

	preprocess( QString() );
};

void iTunesImportOptions::browseMusic()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("The iTunes Music Folder..."));
	if(!path.isEmpty())
		ui.MusicFolderEdit->setText(path);
};

void iTunesImportOptions::browseLibrary()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("The iTunes Folder..."));
	if(!path.isEmpty())
		ui.iTunesFolderEdit->setText(path);
};

void iTunesImportOptions::preprocess(const QString& path)
{
	QString xmlFile = path + QDir::separator() + "iTunes Music Library.xml";

	if( QFile(xmlFile).exists() )
	{
		QFile file(xmlFile);
		file.open(QIODevice::ReadOnly);

		QXmlInputSource source(&file);
		iTunesLibraryPreParser handler;

		QXmlSimpleReader xmlReader;
		xmlReader.setContentHandler(&handler);
		xmlReader.setErrorHandler(&handler);
		xmlReader.parse(&source);

		ui.SongCountLabel->setText( tr("%1 Songs").arg(handler.songCount()) );
		ui.PlaylistCountLabel->setText( tr("%1 Playlists").arg(handler.playlistCount()) );

		ui.MusicFolderEdit->setText(handler.musicFolder());
		//handler.libraryID();

		ui.ImportButton->setEnabled(true);
	}
	else
	{
		ui.ImportButton->setEnabled(false);
		ui.SongCountLabel->setText( QString("File Not") );
		ui.PlaylistCountLabel->setText( QString("Found") );
	}

	checkpaths();
};

void iTunesImportOptions::checkpaths()
{
	QString xmlFile = ui.iTunesFolderEdit->text() + QDir::separator() + "iTunes Music Library.xml";

	if( QFile(xmlFile).exists() )
		ui.iTunesFolderEdit->setPalette(palette());
	else
		ui.iTunesFolderEdit->setPalette(mRedPalette);

	if( QDir(ui.MusicFolderEdit->text()).exists() )
		ui.MusicFolderEdit->setPalette(palette());
	else
		ui.MusicFolderEdit->setPalette(mRedPalette);
};

void iTunesImportOptions::makePalette()
{
	mRedPalette = palette();

	QBrush red_brush = mRedPalette.brush(QPalette::Disabled, ui.iTunesFolderEdit->foregroundRole());
	red_brush.setColor( QColor(128, 0, 0) );
	mRedPalette.setBrush(QPalette::Disabled, ui.iTunesFolderEdit->foregroundRole(), red_brush);
	red_brush = mRedPalette.brush(QPalette::Active, ui.iTunesFolderEdit->foregroundRole());
	red_brush.setColor( QColor(Qt::red) );
	mRedPalette.setBrush(QPalette::Active, ui.iTunesFolderEdit->foregroundRole(), red_brush);
	red_brush = mRedPalette.brush(QPalette::Inactive, ui.iTunesFolderEdit->foregroundRole());
	red_brush.setColor( QColor(192, 0, 0) );
	mRedPalette.setBrush(QPalette::Inactive, ui.iTunesFolderEdit->foregroundRole(), red_brush);
	red_brush = mRedPalette.brush(QPalette::Normal, ui.iTunesFolderEdit->foregroundRole());
	red_brush.setColor( QColor(Qt::red) );
	mRedPalette.setBrush(QPalette::Normal, ui.iTunesFolderEdit->foregroundRole(), red_brush);
};
