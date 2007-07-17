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

/**
 * @file MainWindow.cpp The Main Window implementation
 */

// Utopia Lyrics includes
#include "mainwindow.h"
#include "verseedit.h"

#include <iostream>

// Qt includes
#include <QtGui/QApplication>
#include <QtGui/QVBoxLayout>
#include <QtGui/QSpacerItem>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QAction>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
	setObjectName(QLatin1String("MainWindow"));
	setWindowTitle( tr("Utopia Lyrics") );

	setupActions();
	setupScrollArea();
};

void MainWindow::setupScrollArea()
{
	scrollArea = new QScrollArea(this);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	verseWidget = new QWidget(scrollArea);
	verseLayout = new QVBoxLayout(verseWidget);
	verseLayout->setMargin(0);

	for(int i = 0; i < 4; i++)
	{
		VerseEdit *verse = new VerseEdit;
		verse->setText(QString::number(i));
		verse->setVerseNumber(i + 1);
		connectVerseButtons(verse);
		verseLayout->addWidget(verse);
	}

	scrollArea->setWidget(verseWidget);

	setCentralWidget(scrollArea);
};

void MainWindow::connectVerseButtons(VerseEdit *verse)
{
	connect(verse, SIGNAL(textChanged()), this, SLOT(adjustScrollArea()));
	connect(verse, SIGNAL(moveUp(int)), this, SLOT(moveUp(int)));
	connect(verse, SIGNAL(insertUp(int)), this, SLOT(insertUp(int)));
	connect(verse, SIGNAL(deleteVerse(int)), this, SLOT(deleteVerse(int)));
	connect(verse, SIGNAL(insertDown(int)), this, SLOT(insertDown(int)));
	connect(verse, SIGNAL(moveDown(int)), this, SLOT(moveDown(int)));
};

void MainWindow::moveUp(int verseNumber)
{
	if(verseNumber < 2)
		return;

	VerseEdit *item  = (VerseEdit*)verseLayout->takeAt(verseNumber - 1)->widget();
	VerseEdit *other = (VerseEdit*)verseLayout->takeAt(verseNumber - 2)->widget();
	item->setVerseNumber(item->verseNumber() - 1);
	other->setVerseNumber(other->verseNumber() + 1);

	verseLayout->insertWidget(verseNumber - 2, item);
	verseLayout->insertWidget(verseNumber - 1, other);
};

void MainWindow::insertUp(int verseNumber)
{
	VerseEdit *item;

	item = new VerseEdit;
	item->setVerseNumber(verseNumber);
	connectVerseButtons(item);
	verseLayout->insertWidget(verseNumber - 1, item);

	for(int i = verseNumber; i < verseLayout->count(); i++)
	{
		item  = (VerseEdit*)verseLayout->itemAt(i)->widget();
		item->setVerseNumber(item->verseNumber() + 1);
	}

	adjustScrollArea();
};

void MainWindow::deleteVerse(int verseNumber)
{
	VerseEdit *item;

	delete verseLayout->takeAt(verseNumber - 1)->widget();

	for(int i = verseNumber - 1; i < verseLayout->count(); i++)
	{
		item  = (VerseEdit*)verseLayout->itemAt(i)->widget();
		item->setVerseNumber(item->verseNumber() - 1);
	}

	adjustScrollArea();
};

void MainWindow::insertDown(int verseNumber)
{
	VerseEdit *item;

	item = new VerseEdit;
	item->setVerseNumber(verseNumber);
	connectVerseButtons(item);
	verseLayout->insertWidget(verseNumber, item);

	for(int i = verseNumber + 1; i < verseLayout->count(); i++)
	{
		item  = (VerseEdit*)verseLayout->itemAt(i)->widget();
		item->setVerseNumber(item->verseNumber() + 1);
	}

	adjustScrollArea();
};

void MainWindow::moveDown(int verseNumber)
{
	if(!verseLayout->itemAt(verseNumber))
		return;

	VerseEdit *item  = (VerseEdit*)verseLayout->takeAt(verseNumber - 1)->widget();
	VerseEdit *other = (VerseEdit*)verseLayout->takeAt(verseNumber - 1)->widget();
	item->setVerseNumber(item->verseNumber() + 1);
	other->setVerseNumber(other->verseNumber() - 1);

	verseLayout->insertWidget(verseNumber - 1, item);
	verseLayout->insertWidget(verseNumber - 1, other);
};

void MainWindow::setupActions()
{
	QAction *action;

	action = new QAction( QIcon("color_all"), tr("All Artists"), 0 );
	action->setShortcut( Qt::CTRL+Qt::Key_1 );
	action->setWhatsThis(tr("Make the selected text or the text after the cursor for all the artists."));
	connect(action, SIGNAL(triggered()), this, SLOT(insertColor()));
};

void MainWindow::insertColor()
{
};

void MainWindow::resizeEvent(QResizeEvent *event)
{
	QMainWindow::resizeEvent(event);

	adjustScrollArea();
};

void MainWindow::adjustScrollArea()
{
	if(verseLayout->count() < 1)
		return;

	//verseWidget->resize(scrollArea->maximumViewportSize().width() - scrollArea->verticalScrollBar()->sizeHint().width(),
	//	( verseLayout->itemAt(0)->widget()->sizeHint().height() * verseLayout->count() ) + ( (verseLayout->count() - 1) * 6 ) );

	int desiredHeight = (verseLayout->count() - 1) * 6;

	for(int i = 0; i < verseLayout->count(); i++)
	{
		desiredHeight += verseLayout->itemAt(i)->widget()->sizeHint().height();
	}

	verseWidget->resize(scrollArea->maximumViewportSize().width() - scrollArea->verticalScrollBar()->sizeHint().width(), desiredHeight);
};

QSize MainWindow::sizeHint() const
{
	return QSize(990, 740);
};
