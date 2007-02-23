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

#ifndef __ProgressSlider_h__
#define __ProgressSlider_h__

#include "Slider.h"

#include <QtCore/QMap>
#include <QtGui/QImage>

class ProgressSlider : public Slider
{
	Q_OBJECT

public:
	ProgressSlider(QWidget *parent = 0);

	virtual QSize sizeHint() const;

protected:
	void generateSliderImage(const QString& id, const QColor& borderColor, const QColor& color0, const QColor& color1);
	void generateSliderImages();

	virtual void paintEvent(QPaintEvent *event);

	QMap<QString, QImage> mBar;
	QMap<QString, QImage> mButton;
};

#endif // __ProgressSlider_h__
