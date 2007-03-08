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

#ifndef __Slider_h__
#define __Slider_h__

#include <QtGui/QWidget>

class Slider : public QWidget
{
	Q_OBJECT

public:
	Slider(QWidget *parent = 0);

	int minimum() const;
	int maximum() const;
	int value() const;
	int margin() const;

public slots:
	void setMinimum(int min);
	void setMaximum(int max);
	void setValue(int value);
	void setMargin(int size);

signals:
	void valueChanged(int value);

protected:
	void calculateNewSliderValue(int x);

	virtual void generateSliderImages() { };

	virtual void resizeEvent(QResizeEvent *event);

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

	int mMin;
	int mMax;
	int mValue;
	int mMargin;
};

#endif // __Slider_h__
