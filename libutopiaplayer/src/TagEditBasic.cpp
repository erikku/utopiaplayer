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
*  MERCHANTagILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
*  GNU General Public License for more details.                                *
*                                                                              *
*  You should have received a copy of the GNU General Public License           *
*  along with this program; if not, write to the                               *
*  Free Software Foundation, Inc.,                                             *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                   *
\******************************************************************************/

#include "TagEditBasic.h"
#include "Tag.h"

TagEditBasic::TagEditBasic(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
};

TagEditBasic::TagEditBasic(MetaData::Tag *tag, QWidget *parent)
{
	ui.setupUi(this);
	loadTagData(tag);
};

void TagEditBasic::loadTagData(MetaData::Tag *tag)
{
	if(!tag)
		return;

	ui.Title->setText( tag->title() );
	ui.Artist->setText( tag->artist() );
	ui.Album->setText( tag->album() );
	ui.Comment->setText( tag->comment() );
	ui.Genre->lineEdit()->setText( tag->genre() );
	ui.Track->setValue( tag->track() );
	ui.Year->setValue( tag->year() );
};
