/******************************************************************************\
* QLanguageLearning Library                                                    *
* Copyright (C) 2006 John Eric Martin <cpuwhiz105@users.sourceforge.net>       *
*                                                                              *
* This program is free software; you can redistribute it and/or modify         *
* it under the terms of the GNU General Public License as published by         *
* the Free Software Foundation; either version 2 of the License, or            *
* (at your option) any later version.                                          *
*                                                                              *
* This program is distributed in the hope that it will be useful,              *
* but WITHOUT ANY WARRANTY; without even the implied warranty of               *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
* GNU General Public License for more details.                                 *
*                                                                              *
* You should have received a copy of the GNU General Public License            *
* along with this program; if not, write to the Free Software                  *
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   *
\******************************************************************************/

// TODO: Add tooltip support
// TODO: Add the ability to horizontally (and maybe vertically) align by setting
// the sizers to minimum instead of expanding.
// TODO: Incase in a frame widget to simulate a label's frame
// TODO: Word wrapping

#include "qrubylabel.h"
#include "xmlrubyhandler.h"

void QRubyLabel::init()
{
	mTextFormat = Qt::AutoText;

	labelGrid = new QGridLayout(this);
	labelGrid->setMargin(0);
	labelGrid->setSpacing(0);

	labelLayout = new QHBoxLayout;
	labelLayout->setMargin(0);
	labelLayout->setSpacing(0);

	topSpacer    = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
	leftSpacer   = new QSpacerItem(0, 0, QSizePolicy::Minimum);
	rightSpacer  = new QSpacerItem(0, 0, QSizePolicy::Expanding);
	bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

	labelGrid->addItem(topSpacer,    0, 1);
	labelGrid->addItem(leftSpacer,   1, 0);
	labelGrid->addItem(labelLayout,  1, 1);
	labelGrid->addItem(rightSpacer,  1, 2);
	labelGrid->addItem(bottomSpacer, 2, 1);

	QFont font;
	font.setPointSize(6);
	setRubyFont(font);
	font.setPointSize(9);
	setTextFont(font);
	
	clear();
};

QRubyLabel::QRubyLabel(QWidget *parent) : QWidget(parent)
{
	init();
};

QRubyLabel::QRubyLabel(const QString& text, QWidget *parent) : QWidget(parent)
{
	init();
	setText(text);
};

QRubyLabel::QRubyLabel(const QStringList& text, QWidget *parent) : QWidget(parent)
{
	init();
	setText(text);
};

QFont QRubyLabel::textFont() const
{
	return mTextFont;
};

QFont QRubyLabel::rubyFont() const
{
	return mRubyFont;
};

QString QRubyLabel::text() const
{
	QString string("");
	
	for (int i = 0; i < textWidgets.size(); i++)
	{
		if(textWidgets.at(i)->text().isEmpty())
			string += textWidgets.at(i)->text();
		else
			string += QString::fromUtf8("<ruby><rb>") + textWidgets.at(i)->text() + QString::fromUtf8("</rb><rp>（</rp><rt>") +
					rubyWidgets.at(i)->text() + QString::fromUtf8("</rt><rp>）</rp></ruby>");
	}

	return string;
};

int QRubyLabel::margin() const
{
	return labelGrid->margin();
};

int QRubyLabel::spacing() const
{
	return labelGrid->spacing();
};

void QRubyLabel::clear()
{
	for(int i = 0; i < textWidgets.size(); i++)
	{
		itemLayouts.at(i)->removeWidget(textWidgets.at(i));
		delete textWidgets.at(i);
	}
	textWidgets.clear();
	
	for(int i = 0; i < rubyWidgets.size(); i++)
	{
		itemLayouts.at(i)->removeWidget(rubyWidgets.at(i));
		delete rubyWidgets.at(i);
	}
	rubyWidgets.clear();

	for(int i = 0; i < itemLayouts.size(); i++)
	{
		delete itemLayouts.at(i);
	}
	itemLayouts.clear();
};

void QRubyLabel::setTextFont(const QFont& font)
{
	mTextFont = font;
	
	for (int i = 0; i < textWidgets.size(); i++)
	{
		textWidgets.at(i)->setFont(mTextFont);
	}
};

void QRubyLabel::setRubyFont(const QFont& font)
{
	mRubyFont = font;
	
	for (int i = 0; i < rubyWidgets.size(); i++)
	{
		rubyWidgets.at(i)->setFont(mRubyFont);
	}
};

void QRubyLabel::setText(const QString& item)
{
	clear();
	appendText(item);
};

void QRubyLabel::insertText(const QString& string = QString(""), const QColor& color)
{
	QVBoxLayout *item = new QVBoxLayout;
	QLabel* label;

	if(color.name() != "#000000")
		label = new QLabel("<font color=\"" + color.name() + "\">" + string + "</font>", this);
	else
		label = new QLabel(string, this);

	label->setFont(mTextFont);
	label->setTextFormat(mTextFormat);
	label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

	/*
	if(itemLayouts.count() % 2)
		label->setBackgroundRole(QPalette::Window);
	else
		label->setBackgroundRole(QPalette::AlternateBase);
	label->setAutoFillBackground(true);
	*/

	textWidgets.append(label);
	itemLayouts.append(item);
	
	item->addWidget(label);
	labelLayout->addItem(item);
};

void QRubyLabel::insertRuby(const QString& string = QString(""), const QColor& color)
{
	QVBoxLayout *item = itemLayouts.at( itemLayouts.count() - 1 );
	QLabel* label;

	if(string.isEmpty())
	{
		label = new QLabel("", this);
	}
	else
	{
		if(color.name() != "#000000")
			label = new QLabel("<font color=\"" + color.name() + "\">" + string + "</font>", this);
		else
			label = new QLabel(string, this);
	}

	label->setFont(mRubyFont);
	label->setTextFormat(mTextFormat);
	label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

	/*
	if(itemLayouts.count() % 2)
		label->setBackgroundRole(QPalette::Window);
	else
		label->setBackgroundRole(QPalette::AlternateBase);
	label->setAutoFillBackground(true);
	*/

	rubyWidgets.append(label);
	item->insertWidget(0, label);
};

void QRubyLabel::appendText(const QString& item)
{
	XmlRubyHandler handler;
	QXmlInputSource source;
	source.setData(QString::fromUtf8("<?xml version='1.0' encoding='UTF-8'?><text>") + item + QString::fromUtf8("</text>"));
	QXmlSimpleReader reader;
	reader.setContentHandler( &handler );
	
	reader.parse( source );
	
	if(handler.mText.size() != handler.mRuby.size())
		return;
	
	for (int i = 0; i < handler.mText.size(); i++)
	{
		insertText(handler.mText.at(i), handler.mColor.at(i));
		insertRuby(handler.mRuby.at(i), handler.mColor.at(i));
	}
};

void QRubyLabel::setText(const QStringList& items)
{
	clear();
	appendText(items.join(QString()));
};

void QRubyLabel::appendText(const QStringList& items)
{
	appendText(items.join(QString()));
};

void QRubyLabel::setMargin(int value)
{
	labelLayout->setMargin(value);
};

void QRubyLabel::setSpacing(int value)
{
	labelLayout->setSpacing(value);
};

Qt::TextFormat QRubyLabel::textFormat() const
{
	return mTextFormat;
};;

void QRubyLabel::setTextFormat(Qt::TextFormat format)
{
	mTextFormat = format;
		
	for (int i = 0; i < textWidgets.size(); i++)
	{
		textWidgets.at(i)->setTextFormat(mTextFormat);;
	}
	
	for (int i = 0; i < rubyWidgets.size(); i++)
	{
		rubyWidgets.at(i)->setTextFormat(mTextFormat);;
	}
};

#include "qrubylabel.moc"
