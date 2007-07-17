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

#include "xmlrubyhandler.h"

XmlRubyHandler::XmlRubyHandler()
{
	mText.clear();
	mRuby.clear();
	mColor.clear();
	currentText = QString("");
	currentRuby = QString("");
	currentColor.clear();
	currentElement.clear();
};

bool XmlRubyHandler::startDocument()
{
	currentElement.clear();
	currentElement.push(QString::fromUtf8("BASE"));
	
	mText.clear();
	mRuby.clear();
	mColor.clear();
	currentText = QString("");
	currentRuby = QString("");
	currentColor.clear();
	currentColor.push( QColor("#000000") );
	
	return true;
};

bool XmlRubyHandler::startElement( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts )
{
	currentElement.push(qName);
	
	if( ( ( qName == "font" && !atts.value("color").isEmpty() ) || qName == "ruby") && !currentText.isEmpty() )
	{
		mText << currentText;
		mRuby << currentRuby;
		mColor << currentColor.top();
		currentText = QString("");
		currentRuby = QString("");
	}

	if(!atts.value("color").isEmpty())
		currentColor.push( QColor( atts.value("color") ) );
	
	return true;
};

bool XmlRubyHandler::characters( const QString & ch )
{
	if( currentElement.top() == QString::fromUtf8("rp") || currentElement.top() == QString::fromUtf8("ruby") )
		return true;
	
	if( currentElement.top() == QString::fromUtf8("rt") )
	{
		currentRuby += ch;
		return true;
	}
	
	currentText += ch;
	
	return true;
};

bool XmlRubyHandler::endElement( const QString & namespaceURI, const QString & localName, const QString & qName )
{
	currentElement.pop();

	if( ( qName == QString::fromUtf8("ruby") || qName == QString::fromUtf8("font") ) && !currentText.isEmpty() )
	{
		mText << currentText;
		mRuby << currentRuby;
		mColor << currentColor.top();
		currentText = QString("");
		currentRuby = QString("");
	}

	if( qName == QString::fromUtf8("font") )
		currentColor.pop();
	
	return true;
};

bool XmlRubyHandler::endDocument()
{
	if( !currentText.isEmpty() )
	{
		mText << currentText;
		mRuby << currentRuby;
		mColor << currentColor.top();
	}
	
	return true;
};
