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

#ifndef __VolumeSlider_h__
#define __VolumeSlider_h__

#include "Slider.h"

#include <QtGui/QFont>
#include <QtGui/QImage>
#include <QtGui/QColor>

class VolumeSlider : public Slider
{
	Q_OBJECT

public:
	VolumeSlider(QWidget *parent = 0);

	virtual QSize sizeHint() const;

protected:
	QImage generateSliderImage(const QColor& borderColor, const QColor& color0, const QColor& color1) const;

	virtual void generateSliderImages();

	virtual void paintEvent(QPaintEvent *event);

	QFont mSliderFont;
	QImage mBorderSlider;
	QImage mActiveSlider;
	QImage mInactiveSlider;
	QImage mDisabledSlider;
	QImage mBackgroundSlider;
};

#endif // __VolumeSlider_h__
