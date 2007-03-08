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
 * @file MainWindow.h The Main Window definition
 */

#ifndef __MainWindow_h__
#define __MainWindow_h__

// Qt includes
#include <QtCore/QSize>
#include <QtGui/QMainWindow>

class QWidget;
class QVBoxLayout;
class QScrollArea;

class VerseEdit;

class UtopiaLyricsSettings;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

	virtual QSize sizeHint() const;

public slots:
	void adjustScrollArea();
	void moveUp(int verseNumber);
	void insertUp(int verseNumber);
	void deleteVerse(int verseNumber);
	void insertDown(int verseNumber);
	void moveDown(int verseNumber);

protected:
	void setupActions();
	void setupScrollArea();
	void connectVerseButtons(VerseEdit *verse);

	virtual void resizeEvent(QResizeEvent *event);

	QWidget *verseWidget;
	QVBoxLayout *verseLayout;
	QScrollArea *scrollArea;
};

#endif // __MainWindow_h__
