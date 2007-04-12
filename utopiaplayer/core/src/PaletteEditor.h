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

#ifndef __PaletteEditor_h__
#define __PaletteEditor_h__

#include "ui_PaletteEditor.h"

#include <QtGui/QPalette>

class PaletteEditor : public QWidget
{
	Q_OBJECT

public:
	PaletteEditor();

	QString exportPalette(const QPalette& pal) const;

protected slots:
	void save();
	void updateColor();
	void updatePalette();

protected:
	QPalette mPalette;
	Ui::PaletteEditor ui;

	QMap<QString, QGradient::Type> mGradType;
	QMap<QString, QGradient::Spread> mGradSpread;
	QMap<QString, Qt::BrushStyle> mBrushStyles;
	QMap<QString, QPalette::ColorRole>  mColorRoles;
	QMap<QString, QPalette::ColorGroup> mColorGroups;
	QMap<QPalette::ColorRole, QString>  mDescriptions;
};

#endif // __PaletteEditor_h__
