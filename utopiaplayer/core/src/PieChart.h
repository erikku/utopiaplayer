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

#ifndef __PieChart_h__
#define __PieChart_h__

#include <QtCore/QList>
#include <QtGui/QWidget>
#include <QtGui/QImage>
#include <QtGui/QColor>

class PieChart : public QWidget
{
	Q_OBJECT

public:
	PieChart(QWidget *parent = 0);

	virtual QSize sizeHint() const;

public slots:
	void addElement(float percentage, const QColor& color = QColor(Qt::black));

protected:
	void generateChart();

	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *event);

	QImage mChart;

protected:
	QList<QColor> mColors;
	QList<float> mPercentages;
};

#endif // __PieChart_h__
