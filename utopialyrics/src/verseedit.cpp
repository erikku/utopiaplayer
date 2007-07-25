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
 * @file VerseEdit.cpp The VerseEdit implementation
 */

// Utopia Lyrics includes
#include "verseedit.h"
#include "qrubylabel.h"
#include "Application.h"

// Qt includes
#include <QtCore/QRegExp>
#include <QtGui/QIcon>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QGroupBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>

VerseEdit::VerseEdit(QWidget *parent, Qt::WFlags f) : QWidget(parent, f)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	mainLayout = new QHBoxLayout(this);

	editWidget = new QTextEdit;
	editWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	mainLayout->addWidget(editWidget);

	setupButtons();

	previewWidget = new QGroupBox;
	previewWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	previewWidget->setToolTip(tr("Preview"));
	mainLayout->addWidget(previewWidget);

	previewLayout = new QVBoxLayout;
	previewLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
	previewWidget->setLayout(previewLayout);

	connect(editWidget, SIGNAL(textChanged()), this, SLOT(updatePreview()));
};

QSize VerseEdit::sizeHint() const
{
	if(editWidget->toPlainText().isEmpty())
		return QSize(300, 150);
	else
	{
		QSize size(300, ( previewLayout->count() * previewLayout->itemAt(0)->widget()->sizeHint().height() ) +
			( (previewLayout->count() -1) * 6) );
		if(size.height() > 150)
			return size;
		else
			return QSize(300, 150);
	}
};

QString VerseEdit::colorFromArtistNick(const QString& nick)
{
	if(nick == "ai")
		return QString("aa00ff");
	if(nick == "iida")
		return QString("0000ff");

	return QString("ffffff");
};

void VerseEdit::updatePreview()
{
	/// @todo Wrap this around a one shot timer to keep from updating like crazy
	/// as we are entering text. 1-2 seconds should suffice.
	/// @todo Make sure it's valid before we clear the old stuff out and replace
	// Clear out the layout
	int max = (previewLayout->count() - 1);
	for(int i = 0; i < max; i++)
	{
		delete previewLayout->takeAt(0)->widget();
	}

	// Fix our string
	QString str = editWidget->toPlainText();

	// Replace ruby parenthesies with ruby tags
	str.replace(QRegExp("([\\x4E00-\\x9FFF]+)\\(([\\x3040-\\x309F\\x30A0-\\x30FF]+)\\)"), "<ruby><rb>\\1</rb><rt>\\2</rt></ruby>");
	// Replace | with <ks/>
	str.replace("|", "<ks/>");

	QString lastArtist = "";
	QRubyLabel *label;
	QStringList lines = str.split( QRegExp("[\\f\\n\\r]+") );
	for(int i = 0; i < lines.count(); i++)
	{
		if(!lastArtist.isEmpty())
			lines[i] = "{" + lastArtist + "}" + lines.at(i);

		lastArtist = "";

		QRegExp bracketRegExp("^([^\\{]*)\\{([a-zA-Z0-9,]*)\\}([^\\{]*)(.*)$");
		while( bracketRegExp.exactMatch(lines.at(i)) )
		{
			QStringList artists = bracketRegExp.cap(2).split(",");
			if( bracketRegExp.cap(2).toLower() == "all" || bracketRegExp.cap(2).isEmpty() )
			{
				lastArtist = "";
				lines[i] = bracketRegExp.cap(1) + bracketRegExp.cap(3) + bracketRegExp.cap(4);
			}
			else if(artists.count() > 1)
			{
				lastArtist = bracketRegExp.cap(2);
				/// @todo Add tooltips for the artists
				lines[i] = bracketRegExp.cap(1) + "<font color=\"#aaaaaa\">" + bracketRegExp.cap(3) + "</font>" + bracketRegExp.cap(4);
			}
			else
			{
				lastArtist = bracketRegExp.cap(2);
				QString color = colorFromArtistNick( bracketRegExp.cap(2) );
				lines[i] = bracketRegExp.cap(1) + "<font color=\"#" + color + "\">" + bracketRegExp.cap(3) + "</font>" + bracketRegExp.cap(4);
			} 
		}		
		uDebug("VerseEdit", lines.at(i));
		// Create and add our label(s)
		label = new QRubyLabel(lines.at(i));
		previewLayout->insertWidget((previewLayout->count() - 1), label);
	}

	emit textChanged();
};

int VerseEdit::verseNumber()
{
	return mVerseNumber;
};

void VerseEdit::setVerseNumber(int num)
{
	mVerseNumber = num;
	verseNumberLabel->setText( QString::number(num) );
};

void VerseEdit::setupButtons()
{
	QGridLayout *buttonStrip = new QGridLayout;
	QPushButton *button;

	buttonStrip->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 0);

	verseNumberLabel = new QLabel("0");
	verseNumberLabel->setAlignment(Qt::AlignHCenter);
	verseNumberLabel->setToolTip(tr("Verse Number"));
	buttonStrip->addWidget(verseNumberLabel, 1, 0, 1, 2);

	button = new QPushButton(uApp->icon("actions/up"), "");
	button->setToolTip(tr("Move Verse Up"));
	connect(button, SIGNAL(clicked()), this, SLOT(s_moveUp()));
	buttonStrip->addWidget(button, 2, 0);
	button = new QPushButton(uApp->icon("actions/filenew"), "");
	button->setToolTip(tr("Insert Verse Up"));
	connect(button, SIGNAL(clicked()), this, SLOT(s_insertUp()));
	buttonStrip->addWidget(button, 2, 1);
	button = new QPushButton(uApp->icon("actions/remove"), "");
	button->setToolTip(tr("Delete Verse"));
	connect(button, SIGNAL(clicked()), this, SLOT(s_deleteVerse()));
	buttonStrip->addWidget(button, 3, 0, 1, 2);
	button = new QPushButton(uApp->icon("actions/filenew"), "");
	button->setToolTip(tr("Insert Verse Down"));
	connect(button, SIGNAL(clicked()), this, SLOT(s_insertDown()));
	buttonStrip->addWidget(button, 4, 0);
	button = new QPushButton(uApp->icon("actions/down"), "");
	button->setToolTip(tr("Move Verse Down"));
	connect(button, SIGNAL(clicked()), this, SLOT(s_moveDown()));
	buttonStrip->addWidget(button, 4, 1);

	buttonStrip->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 5, 0);

	mainLayout->addLayout(buttonStrip);
};

void VerseEdit::setText(const QString& str)
{
	editWidget->setText(str);
};

void VerseEdit::s_moveUp() { emit moveUp(verseNumber()); };
void VerseEdit::s_insertUp() { emit insertUp(verseNumber()); };
void VerseEdit::s_deleteVerse() { emit deleteVerse(verseNumber()); };
void VerseEdit::s_insertDown() { emit insertDown(verseNumber()); };
void VerseEdit::s_moveDown() { emit moveDown(verseNumber()); };
