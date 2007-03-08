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
