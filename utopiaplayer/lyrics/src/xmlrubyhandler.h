// Copyright (C) 2006 John Eric Martin

#ifndef __XmlRubyHandler_h__
#define __XmlRubyHandler_h__

#include <QtXml/QXmlDefaultHandler>
#include <QtCore/QStringList>
#include <QtCore/QStack>
#include <QtCore/QList>
#include <QtGui/QColor>

class XmlRubyHandler : public QXmlDefaultHandler
{
public:
	XmlRubyHandler();

    bool startDocument();
    bool startElement( const QString&, const QString&, const QString&, const QXmlAttributes& );

    bool characters( const QString& );

    bool endElement( const QString&, const QString&, const QString& );
    bool endDocument();

signals:
	void resultingText(const QStringList&, const QStringList&);
	
public:
	QStringList mText;
	QStringList mRuby;
	QList<QColor> mColor;
	
protected:
	
	QStack<QString> currentElement;
	
	QString currentText;
	QString currentRuby;
	QStack<QColor> currentColor;
};

#endif // __XmlRubyHandler_h__
