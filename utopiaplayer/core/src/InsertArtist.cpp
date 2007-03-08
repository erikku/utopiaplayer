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

#include <QtCore/QSettings>
#include <QtGui/QLineEdit>
#include <QtGui/QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include "InsertArtist.h"

InsertArtist::InsertArtist(QWidget* parent) : QWidget(parent)
{
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Dialog);
	setFixedSize(451, 141);

	ui.setupUi(this);

	connect(ui.OKButton, SIGNAL(clicked()), this, SLOT(insert()));
	connect(ui.CancelButton, SIGNAL(clicked()), this, SLOT(close()));
};

void InsertArtist::insert()
{
	QSqlQuery query;
	query.prepare( QString::fromUtf8("INSERT INTO `un_artists` (`アーチスト`, `Artist`) VALUES (?, ?)") );
	query.addBindValue( QVariant(ui.KanjiArtistEdit->text()) );
	query.addBindValue( QVariant(ui.RomajiArtistEdit->text()) );
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
