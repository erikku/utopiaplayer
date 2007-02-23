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

#include "PieChart.h"

#include <QtGui/QPainter>

PieChart::PieChart(QWidget *parent) : QWidget(parent)
{
	generateChart();
};

QSize PieChart::sizeHint() const
{
	return QSize(300, 300);
};

void PieChart::addElement(float percentage, const QColor& color)
{
	mColors << color;
	mPercentages << ( percentage/100 );
	generateChart();
};

void PieChart::generateChart()
{
	mChart = QImage(size(), QImage::Format_ARGB32);
	mChart.fill(Qt::transparent);

	QPainter painter(&mChart);
	painter.setPen( QPen(Qt::NoPen) );

	QBrush brush(Qt::SolidPattern);

	QRadialGradient grad(QPointF(mChart.width()/2, mChart.height()/2), mChart.width() < mChart.height() ? mChart.width()/2 : mChart.height()/2);

	QRectF rect(0, 0, mChart.width(), mChart.height());
	int startAngle = 90 * 16;
	int spanAngle = 0;

	for(int i = 0; i < mPercentages.count(); i++)
	{
		if( mPercentages.at(i) <= 0.0f )
			continue;

		spanAngle = -(int)((mPercentages.at(i) * 5760) + 0.5f);

		grad.setColorAt(0, mColors.at(i));
		grad.setColorAt(1, QColor(0, 0, 0));
		painter.setBrush(grad);

		painter.drawPie(rect, startAngle, spanAngle);

		startAngle += spanAngle;

		if(startAngle > 5760)
			startAngle -= 5760;
	}
};

void PieChart::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	QPainter(this).drawImage(QPoint(0, 0), mChart);
};

void PieChart::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	generateChart();
};
