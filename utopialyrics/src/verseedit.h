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
 * @file VerseEdit.h The VerseEdit definition
 */

#ifndef __VerseEdit_h__
#define __VerseEdit_h__

#include <QtGui/QWidget>

class QLabel;
class QTextEdit;
class QGroupBox;
class QHBoxLayout;
class QVBoxLayout;

class VerseEdit : public QWidget
{
	Q_OBJECT

public:
	VerseEdit(QWidget *parent = 0, Qt::WFlags f = 0);

	virtual QSize sizeHint() const;

	int verseNumber();

public slots:
	void updatePreview();
	void setVerseNumber(int num);
	void setText(const QString& str);

protected slots:
	void s_moveUp();
	void s_insertUp();
	void s_deleteVerse();
	void s_insertDown();
	void s_moveDown();

signals:
	void textChanged();
	void moveUp(int);
	void insertUp(int);
	void deleteVerse(int);
	void insertDown(int);
	void moveDown(int);

protected:
	QString colorFromArtistNick(const QString& nick);
	void setupButtons();

	int mVerseNumber;
	QLabel *verseNumberLabel;

	QTextEdit *editWidget;

	QVBoxLayout *previewLayout;
	QGroupBox *previewWidget;

	QHBoxLayout *mainLayout;
};

#endif // __VerseEdit_h__
