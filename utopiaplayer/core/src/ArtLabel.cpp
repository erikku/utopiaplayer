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

#include "ArtLabel.h"

#include <QtGui/QPainter>
#include <QtGui/QActionGroup>

ArtLabel::ArtLabel(QWidget *parent)
{
	setContextMenuPolicy(Qt::ActionsContextMenu);

	QActionGroup *group = new QActionGroup(0);
	QAction *action = new QAction( tr("&Current Song"), 0 );
	action->setCheckable(true);
	action->setChecked(true);
	group->addAction(action);
	addAction(action);
	action = new QAction( tr("&Selected Song"), 0 );
	action->setCheckable(true);
	group->addAction(action);
	addAction(action);
};

QPixmap ArtLabel::pixmap() const
{
	return mArt;
};

void ArtLabel::setPixmap(const QPixmap& pixmap)
{
	mArt = pixmap;
	cacheImage();
	repaint();
};

void ArtLabel::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(QPoint(0, 0), mBuffer);
};

void ArtLabel::resizeEvent(QResizeEvent *event)
{
	cacheImage();
};

void ArtLabel::cacheImage()
{
	QImage art = mArt.toImage();

	if(art.width() > width() || art.height() > height())
	{
		art = art.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}

	mBuffer = QImage(size(), QImage::Format_ARGB32);
	mBuffer.fill( QColor(0, 0, 0, 0).rgba() );

	QPainter painter(&mBuffer);
	painter.drawImage(QPointF((width() - art.width())/2, (height() - art.height())/2), art);
};

QSize ArtLabel::sizeHint() const
{
	return QSize(256, 256);
};
