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
 * @file QRubyMessageBox.cpp The class implementation for QRubyMessageBox
 */

#include "QRubyMessageBox.h"
#include "QRubyLabel.h"

#include <QtCore/QString>
#include <QtCore/QSize>

#include <QtGui/QStyle>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QApplication>

QRubyMessageBox::QRubyMessageBox(QWidget *parent) : QDialog(parent)
{
	mButton0 = 0; mButton1 = 0; mButton2 = 0;

	mIconType = QRubyMessageBox::NoIcon;
	mIcon = new QLabel(this);
	mMessageLayout->addWidget(mIcon);

	mMessage = new QRubyLabel(this);
	mMessageLayout->addWidget(mMessage);

	// Setup the layout
	mDialogLayout = new QVBoxLayout(this);
	mMessageLayout = new QHBoxLayout;
	mDialogLayout->addLayout(mMessageLayout);
	mButtonLayout = new QHBoxLayout;
	mDialogLayout->addLayout(mButtonLayout);
	mButtonLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	mButton0 = new QPushButton;
	mButtonLayout->addWidget(mButton0);
	mButton0->hide();
	mButton1 = new QPushButton;
	mButtonLayout->addWidget(mButton1);
	mButton1->hide();
	mButton2 = new QPushButton;
	mButtonLayout->addWidget(mButton2);
	mButton2->hide();
	mButtonLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
};

QRubyMessageBox::QRubyMessageBox(const QString &caption, const QString &text, Icon icon, int button0, int button1, int button2, QWidget *parent, Qt::WFlags f) : QDialog(parent)
{
	mButton0 = 0; mButton1 = 0; mButton2 = 0;

	// Set the dialog caption
	setWindowTitle(caption);

	// Setup the layout
	mDialogLayout = new QVBoxLayout(this);
	mMessageLayout = new QHBoxLayout;
	mDialogLayout->addLayout(mMessageLayout);
	mButtonLayout = new QHBoxLayout;
	mDialogLayout->addLayout(mButtonLayout);
	mButtonLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));

	// Set the message icon
	mIconType = icon;
	mIcon = new QLabel;
	if(icon > 0 && icon < 5)
		mIcon->setPixmap( standardIcon(icon) );
	mMessageLayout->addWidget(mIcon);

	// Set the message text
	mMessage = new QRubyLabel(text);
	mMessageLayout->addWidget(mMessage);

	// Set our button types/numbers
	mButtonType0 = button0;
	mButtonType1 = button1;
	mButtonType2 = button2;

	// Create our buttons
	switch(button0 & QRubyMessageBox::ButtonMask)
	{
		case QRubyMessageBox::Ok:
			mButton0 = new QPushButton(tr("&OK"));
			break;
		case QRubyMessageBox::Cancel:
			mButton0 = new QPushButton(tr("&Cancel"));
			break;
		case QRubyMessageBox::Yes:
			mButton0 = new QPushButton(tr("&Yes"));
			break;
		case QRubyMessageBox::No:
			mButton0 = new QPushButton(tr("&No"));
			break;
		case QRubyMessageBox::Abort:
			mButton0 = new QPushButton(tr("&Abort"));
			break;
		case QRubyMessageBox::Retry:
			mButton0 = new QPushButton(tr("&Retry"));
			break;
		case QRubyMessageBox::Ignore:
			mButton0 = new QPushButton(tr("&Ignore"));
			break;
		case QRubyMessageBox::YesAll:
			mButton0 = new QPushButton(tr("&Yes to all"));
			break;
		case QRubyMessageBox::NoAll:
			mButton0 = new QPushButton(tr("&No to all"));
			break;
		default:
			mButton0 = new QPushButton;
			mButton0->hide();
			break;
	}

	Q_ASSERT(mButton0);

	if(button0 & QRubyMessageBox::FlagMask == QRubyMessageBox::Escape)
		mButton0->setShortcut( QKeySequence(Qt::Key_Escape) );

	if(button0 & QRubyMessageBox::FlagMask == QRubyMessageBox::Default)
		mButton0->setDefault(true);

	connect(mButton0, SIGNAL(clicked()), this, SLOT(buttonClicked()));

	mButtonLayout->addWidget(mButton0);

	mButtonLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));

	setFixedSize (sizeHint());
};

QRubyMessageBox::~QRubyMessageBox()
{
	delete mMessage;
	delete mIcon;

	if(mButton0)
		delete mButton0;

	if(mButton1)
		delete mButton1;

	if(mButton2)
		delete mButton2;

	delete mMessageLayout;
	delete mButtonLayout;
	delete mDialogLayout;
};

QString QRubyMessageBox::text() const
{
	Q_ASSERT(mMessage);

	return mMessage->text();
};

void QRubyMessageBox::setText(const QString &text)
{
	Q_ASSERT(mMessage);

	mMessage->setText(text);
};

QRubyMessageBox::Icon QRubyMessageBox::icon() const
{
	return (QRubyMessageBox::Icon)mIconType;
};

void QRubyMessageBox::setIcon(Icon icon)
{
	Q_ASSERT(mIcon);

	mIcon->setPixmap( standardIcon(icon) );
};

QPixmap QRubyMessageBox::iconPixmap() const
{
	Q_ASSERT(mIcon);

	return QPixmap(*mIcon->pixmap());
};

void QRubyMessageBox::setIconPixmap(const QPixmap &icon)
{
	Q_ASSERT(mIcon);

	mIcon->setPixmap(icon);
};

QString QRubyMessageBox::buttonText(int button) const
{
	if(mButton0 != 0 && mButtonType0 == button)
		return mButton0->text();

	if(mButton1 != 0 && mButtonType1 == button)
		return mButton1->text();

	if(mButton2 != 0 && mButtonType2 == button)
		return mButton2->text();

	return QString();
};

void QRubyMessageBox::setButtonText(int button, const QString &text)
{
	if(mButton0 != 0 && mButtonType0 == button)
	{
		mButton0->setText(text);
		mButton0->show();
	}

	if(mButton1 != 0 && mButtonType1 == button)
	{
		mButton1->setText(text);
		mButton1->show();
	}

	if(mButton2 != 0 && mButtonType2 == button)
	{
		mButton2->setText(text);
		mButton2->show();
	}
};

Qt::TextFormat QRubyMessageBox::textFormat() const
{
	Q_ASSERT(mMessage);

	return mMessage->textFormat();
};

void QRubyMessageBox::setTextFormat(Qt::TextFormat format)
{
	Q_ASSERT(mMessage);

	mMessage->setTextFormat(format);
};

int QRubyMessageBox::information(QWidget *parent, const QString &caption, const QString& text, int button0, int button1, int button2)
{
	return QRubyMessageBox(caption, text, QRubyMessageBox::Information, button0, button1, button2, parent).exec();
};

int QRubyMessageBox::information(QWidget *parent, const QString &caption, const QString& text, const QString& button0Text, const QString& button1Text, const QString& button2Text, int defaultButtonNumber, int escapeButtonNumber)
{
	int btn0 = 0, btn1 = 1, btn2 = 2;

	if(defaultButtonNumber = 0)
		btn0 |= QRubyMessageBox::Default;

	if(defaultButtonNumber = 1)
		btn1 |= QRubyMessageBox::Default;

	if(defaultButtonNumber = 2)
		btn2 |= QRubyMessageBox::Default;

	if(escapeButtonNumber = 0)
		btn0 |= QRubyMessageBox::Escape;

	if(escapeButtonNumber = 1)
		btn1 |= QRubyMessageBox::Escape;

	if(escapeButtonNumber = 2)
		btn2 |= QRubyMessageBox::Escape;

	QRubyMessageBox dialog(caption, text, QRubyMessageBox::Information, btn0, btn1, btn2, parent);
	dialog.setButtonText(0, button0Text);
	dialog.setButtonText(1, button1Text);
	dialog.setButtonText(2, button2Text);

	return dialog.exec();
};

int QRubyMessageBox::question(QWidget *parent, const QString &caption, const QString& text, int button0, int button1, int button2) { return 0; };

int QRubyMessageBox::question(QWidget *parent, const QString &caption, const QString& text, const QString& button0Text, const QString& button1Text, const QString& button2Text, int defaultButtonNumber, int escapeButtonNumber) { return 0; };

int QRubyMessageBox::warning(QWidget *parent, const QString &caption, const QString& text, int button0, int button1, int button2) { return 0; };

int QRubyMessageBox::warning(QWidget *parent, const QString &caption, const QString& text, const QString& button0Text, const QString& button1Text, const QString& button2Text, int defaultButtonNumber, int escapeButtonNumber) { return 0; };

int QRubyMessageBox::critical(QWidget *parent, const QString &caption, const QString& text, int button0, int button1, int button2) { return 0; };

int QRubyMessageBox::critical(QWidget *parent, const QString &caption, const QString& text, const QString& button0Text, const QString& button1Text, const QString& button2Text, int defaultButtonNumber, int escapeButtonNumber) { return 0; };

void QRubyMessageBox::about(QWidget *parent, const QString &caption, const QString& text) { };

QSize QRubyMessageBox::sizeHint() const
{
	return minimumSize();
};

QPixmap QRubyMessageBox::standardIcon(Icon icon)
{
	switch(icon)
	{
		case Information:
			return QApplication::style()->standardPixmap(QStyle::SP_MessageBoxInformation);
			break;
		case Warning:
			return QApplication::style()->standardPixmap(QStyle::SP_MessageBoxWarning);
			break;
		case Critical:
			return QApplication::style()->standardPixmap(QStyle::SP_MessageBoxCritical);
			break;
		case Question:
			return QApplication::style()->standardPixmap(QStyle::SP_MessageBoxQuestion);
			break;
	}

	return QPixmap();
};

void QRubyMessageBox::buttonClicked()
{
	QPushButton* button = (QPushButton*)sender();
	Q_ASSERT(button);

	if(button == mButton0)
		done(mButtonType0);

	if(button == mButton1)
		done(mButtonType1);

	if(button == mButton2)
		done(mButtonType2);
};
