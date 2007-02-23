// Copyright (C) 2006 John Eric Martin

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
