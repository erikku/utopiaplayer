/******************************************************************************\
*  Utopia Player - A cross-platform, multilingual, tagging media manager       *
*  Copyright (C) 2006-2007 John Eric Martin <cpuwhiz105@users.sourceforge.net> *
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

#ifndef __iTunesLibraryImportExport_h__
#define __iTunesLibraryImportExport_h__

#include "ImportExportInterface.h"

#include <QtCore/QStack>
#include <QtCore/QVariant>
#include <QtXml/QXmlDefaultHandler>

class iTunesLibraryImportExport : public ImportExportInterface
{
	Q_OBJECT

public:
	iTunesLibraryImportExport();
	virtual ~iTunesLibraryImportExport();

	virtual QAction* importAction();
	virtual QAction* exportAction();

	virtual QString pluginName() const { return tr("iTunesImportExport"); };

public slots:
	virtual void doImport();
	virtual void doExport();

protected:
	QAction *mImportAction;
	QAction *mExportAction;
};

class iTunesLibraryParser : public QXmlDefaultHandler
{
public:
	virtual bool startDocument();
	virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
	virtual bool characters(const QString& ch);
	virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);
	virtual bool endDocument();

protected:
	void proccessSong(const QMap<QString, QVariant>& keyPairs);

	QString mCurrentKey;

	QString mLibraryID;
	QString mMusicFolder;

	QStack<QString> mDicts;
	QStack<QString> mElements;
	QMap<QString, QVariant> mCurrentDict;
};

#endif // __iTunesLibraryImportExport_h__
