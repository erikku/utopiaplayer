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

#include "VolumeSlider.h"

#include <QtGui/QLinearGradient>
#include <QtGui/QPainterPath>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPen>

VolumeSlider::VolumeSlider(QWidget *parent) : Slider(parent)
{
	generateSliderImages();
};

QSize VolumeSlider::sizeHint() const
{
	return QSize(96, 24);
};

QImage VolumeSlider::generateSliderImage(const QColor& borderColor, const QColor& color0, const QColor& color1) const
{
	QSize sliderSize = QSize(width() - (margin() * 2), height() - (margin() * 2));

	QImage sliderImage = QImage(sliderSize, QImage::Format_ARGB32);
	sliderImage.fill( QColor(0, 0, 0, 0).rgba() );

	QPainter sliderPainter(&sliderImage);

	QLinearGradient sliderGradient(0, 0, width(), 0);
	sliderGradient.setColorAt(0, color0);
	sliderGradient.setColorAt(1, color1);

	QPolygonF area;
	area << QPointF(0, sliderSize.height()) << QPointF(sliderSize.width(), sliderSize.height())
		 << QPointF(sliderSize.width(), 0)  << QPointF(0, sliderSize.height() - (sliderSize.height()/3));

	QPainterPath path;
	path.addPolygon(area);
	path.closeSubpath();

	QPen pen(borderColor, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

	sliderPainter.setRenderHint(QPainter::Antialiasing);
	sliderPainter.setBrush(sliderGradient);
	sliderPainter.setPen(pen);
	sliderPainter.drawPath(path);

	return sliderImage;
};

void VolumeSlider::generateSliderImages()
{
	mBorderSlider = generateSliderImage( palette().brush(QPalette::Active, QPalette::Highlight).color(), QColor(Qt::transparent), QColor(Qt::transparent) );
	mActiveSlider = generateSliderImage( QColor(Qt::transparent), palette().brush(QPalette::Active, QPalette::Dark).color(), palette().brush(QPalette::Active, QPalette::Highlight).color() );
	mInactiveSlider = generateSliderImage( QColor(Qt::transparent), palette().brush(QPalette::Inactive, QPalette::Dark).color(), palette().brush(QPalette::Inactive, QPalette::Highlight).color() );
	mDisabledSlider = generateSliderImage( QColor(Qt::transparent), palette().brush(QPalette::Disabled, QPalette::Dark).color(), palette().brush(QPalette::Disabled, QPalette::Highlight).color() );
	mBackgroundSlider = generateSliderImage( QColor(Qt::transparent), palette().brush(QPalette::Active, QPalette::Window).color(), palette().brush(QPalette::Active, QPalette::Button).color() );

	mSliderFont = font();
	float size = mBackgroundSlider.height() - (mBackgroundSlider.height()/2) - 0.5f;
	mSliderFont.setPixelSize( (int)size );
};

void VolumeSlider::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);

	// Draw the background for the slider
	painter.drawImage(QPoint(margin(), margin()), mBackgroundSlider);

	float sliderValue = mActiveSlider.width() * ( value() - minimum() ) / ( maximum() - minimum() );

	// Calculate from the slider value how much of the slider to draw
	QRectF area(0, 0, sliderValue, mActiveSlider.height());

	// Only draw the value bar if we have over 0 width (otherwise it will draw the whole bar)
	if( (int)sliderValue > 0 )
	{
		// Draw the active or inactive slider depending on if the window is active
		if( !isEnabled() )
		{
			painter.drawImage(QPoint(margin(), margin()), mDisabledSlider, area);
		}
		else if( isActiveWindow() )
		{
			painter.drawImage(QPoint(margin(), margin()), mActiveSlider, area);
		}
		else
		{
			painter.drawImage(QPoint(margin(), margin()), mInactiveSlider, area);
		}
	}

	// Draw the border for the slider
	painter.drawImage(QPoint(margin(), margin()), mBorderSlider);

	// Draw the text
	painter.setFont(mSliderFont);
	painter.setBrush( palette().brush(QPalette::WindowText) );
	painter.drawText( margin(), margin() + mSliderFont.pixelSize(), tr("%1%").arg( (int)(100 * ( value() - minimum() ) / ( maximum() - minimum() )) ) );
};
