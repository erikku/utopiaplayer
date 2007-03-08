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

#include <QtGui>
#include <QtGui/QIcon>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QRegExp>
#include <QtCore/QFile>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include "SongEdit.h"

SongEdit::SongEdit(QWidget* parent) : QWidget(parent)
{
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Dialog);
	setFixedSize(541, 481);

	ui.setupUi(this);

	connect(ui.OKButton, SIGNAL(clicked()), this, SLOT(insert()));
	connect(ui.CancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.BrowseButton, SIGNAL(clicked()), this, SLOT(browse()));
	connect(ui.AlbumCoverEdit, SIGNAL(textChanged(const QString &)), this, SLOT(refreshCover(const QString &)));

	ui.BrowseButton->setIcon(QIcon(":/16x16/fileopen.png"));

	refreshOptions();
};

void SongEdit::browse()
{
	QString WorkingCoverPath = QFileDialog::getOpenFileName(this, "Choose a album cover image", mCoversDirectory, "Images (*.png *.jpg)");
	QRegExp rx(mCoversDirectory + QString("(.*)$"));
	rx.exactMatch(WorkingCoverPath);
	ui.AlbumCoverEdit->setText(rx.cap(1));
	refreshCover(rx.cap(1));
};

void SongEdit::insert()
{
	QSqlQuery query;
	query.prepare( QString::fromUtf8("INSERT INTO `un_albums` (`アルバム`, `Album`, `ReleaseDate`, `Cover`) VALUES (?, ?, ?, ?)") );
	query.addBindValue( QVariant(ui.KanjiAlbumEdit->text()) );
	query.addBindValue( QVariant(ui.RomajiAlbumEdit->text()) );
	query.addBindValue( QVariant(ui.ReleaseDateEdit->date()) );
	query.addBindValue( QVariant(ui.AlbumCoverEdit->text()) );
	if( query.exec() )
	{
		close();
		emit updateDatabase();
	}
	else
	{
		QMessageBox::information(this, tr("UtopiaPlayer"),
			tr("The SQL query returned the following error:\n\n") + query.lastError().text() );
	}
};

void SongEdit::refreshCover(const QString & RelativeCoverPath)
{
	QFile file(mCoversDirectory + RelativeCoverPath);
	if(file.exists())
	{
		QPixmap cover(mCoversDirectory + RelativeCoverPath);
		ui.AlbumCover->setPixmap( cover.scaled ( 151, 151, Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
	}
};

void SongEdit::refreshOptions()
{
	QSettings settings;
	mCoversDirectory = settings.value("General/CoversDirectory").toString();
};
