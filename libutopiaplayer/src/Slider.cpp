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

#include "Slider.h"

#include <QtGui/QMouseEvent>

Slider::Slider(QWidget *parent) : QWidget(parent), mValue(0), mMargin(0), mMin(0), mMax(100)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	setValue(0);
};

int Slider::minimum() const
{
	return mMin;
};

void Slider::setMinimum(int min)
{
	mMin = min;
	if(mValue < mMin)
	{
		mValue = mMin;
		repaint();
		emit valueChanged(mValue);
	}
};

int Slider::maximum() const
{
	return mMax;
};

void Slider::setMaximum(int max)
{
	mMax = max;
	if(mValue > mMax)
	{
		mValue = mMax;
		repaint();
		emit valueChanged(mValue);
	}
};

int Slider::value() const
{
	return mValue;
};

void Slider::setValue(int value)
{
	if(value >= minimum() && value <= maximum())
	{
		mValue = value;
		repaint();

		int percent = 0;
		if( ( maximum() - minimum() ) != 0 )
			percent = (int)(100 * ( mValue - minimum() ) / ( maximum() - minimum() ));

		setToolTip( tr("Volume: %1%").arg(percent) );
		emit valueChanged(mValue);
	}
};

int Slider::margin() const
{
	return mMargin;
};

void Slider::setMargin(int size)
{
	mMargin = size;
	repaint();
};

void Slider::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	generateSliderImages();
};

void Slider::calculateNewSliderValue(int x)
{
	if(x < margin() || x > (width() - margin()))
		return;

	float sliderValue = ( ( (float)(x - margin()) / (float)(width() - margin()*2) ) * (float)(maximum() - minimum()) ) + minimum() + 0.5f;

	if(sliderValue > maximum())
		sliderValue = maximum();

	setValue((int)sliderValue);
};

void Slider::mousePressEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
	calculateNewSliderValue(event->x());
};

void Slider::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);
	calculateNewSliderValue(event->x());
};
