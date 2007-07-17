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

#ifndef __TagEditBasic_h__
#define __TagEditBasic_h__

#include "ui_TagEditBasic.h"

namespace MetaData { class Tag; };

class TagEditBasic : public QWidget
{
	Q_OBJECT

public:
	TagEditBasic(QWidget *parent = 0);
	TagEditBasic(MetaData::Tag *tag, QWidget *parent = 0);

public slots:
	void loadTagData(MetaData::Tag *tag);

protected:
	Ui::TagEditBasic ui;
};

#endif // __TagEditBasic_h__
