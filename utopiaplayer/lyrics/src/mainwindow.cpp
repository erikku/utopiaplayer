/*************************************************************************\
*  UtopiaPlayer - A song manager and icecast streaming agent              *
*  Copyright (C) 2006 John Eric Martin <cpuwhiz105@users.sourceforge.net> *
*                                                                         *
*  This program is free software; you can redistribute it and/or modify   *
*  it under the terms of the GNU General Public License version 2 as      *
*  published by the Free Software Foundation.                             *
*                                                                         *
*  This program is distributed in the hope that it will be useful,        *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with this program; if not, write to the                          *
*  Free Software Foundation, Inc.,                                        *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
\*************************************************************************/

/**
 * @file MainWindow.cpp The Main Window implementation
 */

// Utopia Lyrics includes
#include "mainwindow.h"
#include "utopialyricssettings.h"
#include "verseedit.h"

#include <iostream>

// Qt includes
#include <QtGui/QVBoxLayout>
#include <QtGui/QSpacerItem>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>

// KDE includes
#include <klocalizedstring.h>
#include <kapplication.h>
#include <kstdaction.h>
#include <kaction.h>
#include <kicon.h>

MainWindow::MainWindow() : KMainWindow(0, 0)
{
	setObjectName(QLatin1String("MainWindow"));

	settings = UtopiaLyricsSettings::self();
	settings->readConfig();

	setupActions();
	setupGUI();
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
	KAction *a;

	KStdAction::openNew( this, SLOT( slotDocumentNew() ), actionCollection(), "file_new" )->setWhatsThis(i18n("Create a new document"));
	KStdAction::open( this, SLOT( slotDocumentOpen() ), actionCollection(), "file_open" )->setWhatsThis(i18n("Open an existing document for editing"));

	KStdAction::close( this, SLOT( slotDocumentClose() ), actionCollection(), "file_close" )->setWhatsThis(i18n("Close the current document"));

	a = new KAction( KIcon("color_all"), i18n("All Artists"), actionCollection(), "color_all" );
	a->setShortcut( Qt::CTRL+Qt::Key_1 );
	a->setWhatsThis(i18n("Make the selected text or the text after the cursor for all the artists."));
	connect( a, SIGNAL( triggered() ), this, SLOT( insertColor() ) );

	KStdAction::quit(kapp, SLOT(quit()), actionCollection());
};

void MainWindow::resizeEvent(QResizeEvent *event)
{
	KMainWindow::resizeEvent(event);

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

#include "mainwindow.moc"
