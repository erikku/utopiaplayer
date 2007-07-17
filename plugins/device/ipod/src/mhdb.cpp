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

#include <QtCore/QFile>

#include "mhdb.h"

mhdb::mhdb(QWidget *parent) : QWidget(parent)
{
	//setWindowModality(Qt::WindowModal);
	//setWindowFlags(Qt::Dialog);
	//setFixedSize(size());

	ui.setupUi(this);
};

static QString numberToHexString(qint64 number, int fieldWidth = 8)
{
	return QString("0x%1").arg(QString::number(number, 16).toUpper(), fieldWidth, '0');
};

bool mhdb::read(QFile *file)
{
	char *buffer;

	if( file->read((char*)&headerSize, 4) != 4 )
		return false;

	if( file->read((char*)&totalSize, 4) != 4 )
		return false;
	
	if( file->read((char*)&unk1, 4) != 4 )
		return false;

	if( file->read((char*)&versionNumber, 4) != 4 )
		return false;

	if( file->read((char*)&childCount, 4) != 4 )
		return false;

	if( file->read((char*)&id, 8) != 8 )
		return false;

	if( file->read((char*)&unk2, 4) != 4 )
		return false;

	if(versionNumber >= 0x11)
	{
		if( file->read((char*)&unk3, 8) != 8 )
			return false;
	}

	// Zero padding
	qint64 padding = headerSize - ( (versionNumber >= 0x11) ? 44 : 36 );
	buffer = new char[ padding ];
	if( file->read((char*)buffer, padding) != padding )
		return false;
	delete[] buffer;

	ui.headerSize->setText( QString::number(headerSize) + " bytes" );
	ui.totalSize->setText( QString::number(totalSize) + " bytes" );
	buffer = new char[3];
	sprintf(buffer, "%08x", unk1);
	ui.unk1->setText( "0x" + QString(buffer) );
	delete[] buffer;
	//buffer = new char[3];
	//sprintf(buffer, "%02x", versionNumber);
	//ui.versionNumber->setText( "0x" + QString(buffer) );
	//delete[] buffer;
	/// @TODO Inline this as QString numberToHexString(qint64 number, int fieldWidth) const;
	ui.versionNumber->setText( numberToHexString(versionNumber, 2) );
	ui.childCount->setText( QString::number(childCount) );
	ui.id->setText( "0x" + QString::number(id, 16) );
	buffer = new char[9];
	sprintf(buffer, "%08x", unk2);
	ui.unk2->setText( "0x" + QString(buffer) );
	delete[] buffer;
	if(versionNumber >= 0x11)
	{
		ui.unk3->setText( "0x" + QString::number(unk3, 16) );
	}
	else
	{
		ui.unk3->hide();
		ui.lbl_unk3->hide();
	}

	return true;
};

QStringList listRecursiveDirectoryContents(const QDir& dir, const QStringList& nameFilters, QDir::Filters filters, QDir::SortFlags sort)
{
	QStringList subdirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, sort);
	QStringList contents = dir.entryList(nameFilters, filters, sort);

	for(int i = 0; i < contents.count(); i++)
	{
		contents.replace(i, dir.absolutePath() + QDir::separator() + contents.at(i) );
	}

	QDir newDir;

	for(int i = 0; i < subdirs.count(); i++)
	{
		newDir = dir;
		newDir.cd(subdirs.at(i));
		contents << listRecursiveDirectoryContents(newDir, nameFilters, filters, sort);
	}

	return contents;
};
