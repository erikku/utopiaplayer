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

#include "ProgressSlider.h"

#include <QtGui/QPainter>
#include <QtGui/QPalette>

ProgressSlider::ProgressSlider(QWidget *parent) : Slider(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	generateSliderImages();
};

QSize ProgressSlider::sizeHint() const
{
	return QSize(200, 16);
};

void ProgressSlider::generateSliderImage(const QString& id, const QColor& borderColor, const QColor& color0, const QColor& color1)
{
	QSize barSize(width() - (margin() * 2), (height() - (margin() * 2)) / 2);
	QSize buttonSize(height() - (margin() * 2), height() - (margin() * 2));

	QRect barRect(0, 0, barSize.width(), barSize.height());
	QRect buttonRect(0, 0, buttonSize.width(), buttonSize.height());

	QImage barImage(barSize, QImage::Format_ARGB32);
	QImage buttonImage(buttonSize, QImage::Format_ARGB32);

	barImage.fill( QColor(0, 0, 0, 0).rgba() );
	buttonImage.fill( QColor(0, 0, 0, 0).rgba() );

	QPainter barPainter(&barImage);
	QPainter buttonPainter(&buttonImage);

	QLinearGradient sliderGradient(0, 0, width(), 0);
	sliderGradient.setColorAt(0, color0);
	sliderGradient.setColorAt(1, color1);

	QPen pen(borderColor, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

	barPainter.setRenderHint(QPainter::Antialiasing);
	barPainter.setBrush(sliderGradient);
	barPainter.setPen(pen);
	barPainter.drawRoundRect(barRect);//, 27, 27);

	buttonPainter.setRenderHint(QPainter::Antialiasing);
	buttonPainter.setBrush(sliderGradient);
	buttonPainter.setPen(pen);
	buttonPainter.drawEllipse(buttonRect);

	mBar[id] = barImage;

	if(id != QString("Background"))
		mButton[id] = buttonImage;
};

void ProgressSlider::generateSliderImages()
{
	generateSliderImage( "Border", palette().brush(QPalette::Active, QPalette::Highlight).color(), QColor(Qt::transparent), QColor(Qt::transparent) );
	generateSliderImage( "Active", QColor(Qt::transparent), palette().brush(QPalette::Active, QPalette::Dark).color(), palette().brush(QPalette::Active, QPalette::Highlight).color() );
	generateSliderImage( "Inactive", QColor(Qt::transparent), palette().brush(QPalette::Inactive, QPalette::Dark).color(), palette().brush(QPalette::Inactive, QPalette::Highlight).color() );
	generateSliderImage( "Disabled", QColor(Qt::transparent), palette().brush(QPalette::Disabled, QPalette::Dark).color(), palette().brush(QPalette::Disabled, QPalette::Highlight).color() );
	generateSliderImage( "Background", QColor(Qt::transparent), palette().brush(QPalette::Active, QPalette::Window).color(), palette().brush(QPalette::Active, QPalette::Button).color() );
};

void ProgressSlider::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	QPainter painter(this);

	// Draw the background for the slider
	painter.drawImage(QPoint(margin(), margin()), mBar["Background"]);

	float sliderValue = 0;

	if( ( maximum() - minimum() ) != 0 )
		sliderValue = mBar["Active"].width() * ( value() - minimum() ) / ( maximum() - minimum() );

	// Calculate from the slider value how much of the slider to draw
	QRectF area(0, 0, sliderValue, mBar["Active"].height());

	// Only draw the value bar if we have over 0 width (otherwise it will draw the whole bar)
	if( (int)sliderValue > 0 )
	{
		// Draw the active or inactive slider depending on if the window is active
		if( !isEnabled() )
		{
			painter.drawImage(QPoint(margin(), margin()), mBar["Disabled"], area);
		}
		else if( isActiveWindow() )
		{
			painter.drawImage(QPoint(margin(), margin()), mBar["Active"], area);
		}
		else
		{
			painter.drawImage(QPoint(margin(), margin()), mBar["Inactive"], area);
		}
	}

	// Draw the border for the slider
	painter.drawImage(QPoint(margin(), margin()), mBar["Border"]);
};
