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

#include "FileList.h"
#include "FileProperties.h"
#include "Application.h"
#include "AudioFile.h"
#include "FileTypeFactory.h"
#include "Tag.h"

#include <QtCore/QUrl>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QRegExp>
#include <QtCore/QFileInfo>
#include <QtCore/QMimeData>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QTreeWidgetItem>

FileList::FileList(QWidget *parent) : QTreeWidget(parent)
{
	mFileTypeFactory = uApp->fileTypeFactory();

	setColumnCount(2);
	setAcceptDrops(true);

	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(handleItem(QTreeWidgetItem*)));
};

FileList::~FileList()
{
	foreach(AudioFile *file, mFiles.values())
		delete file;

	// delete mFileTypeFactory;
};

void FileList::dragEnterEvent(QDragEnterEvent *event)
{
	if( event->mimeData()->hasUrls() )
		event->acceptProposedAction();
};

void FileList::dragMoveEvent(QDragMoveEvent *event)
{
	if( event->mimeData()->hasUrls() )
		event->acceptProposedAction();
};

void FileList::dragLeaveEvent(QDragLeaveEvent *event)
{
	event->accept();
}

void FileList::dropEvent(QDropEvent *event)
{
	if( !event->mimeData()->hasUrls() )
		return;

	QString path;

	foreach(QUrl url, event->mimeData()->urls())
	{
		path = url.toLocalFile();

		if( path.isEmpty() )
			continue;

		if( QDir(path).exists() )
		{
			QStringList files = Application::listRecursiveDirectoryContents( QDir(path) );
			foreach(QString file, files)
			{
				addFile(file);
			}
			continue;
		}

		if( QFile(path).exists() )
		{
			addFile(path);
			continue;
		}

		uError("FileList", tr("File not found: %1").arg(path));
	}

	event->acceptProposedAction();
};

void FileList::handleItem(QTreeWidgetItem *item)
{
	( new FileProperties(mFiles[item]) )->show();
};

void FileList::addFile(const QString& file)
{
	QString mimeType, fileType = "Unknown", title = "File Not Loaded";

	uDebug("FileList", file);

	AudioFile *audioFile = mFileTypeFactory->getHandle(file);
	if(audioFile)
	{
		audioFile->load();
		if( audioFile->tags().count() )
			title = audioFile->tags().first()->album();
		fileType = audioFile->type();
		mimeType = audioFile->mimeType();
	}

	QFileInfo info(file);
	//QTreeWidgetItem *item = new QTreeWidgetItem( QStringList() << info.completeBaseName() << fileType );
	QTreeWidgetItem *item = new QTreeWidgetItem( QStringList() << title << fileType );

	//map[item] = url.toLocalFile();
	if( mimeType.isEmpty() )
		item->setIcon( 0, uApp->icon("mimetypes/unknown") );
	else
		item->setIcon( 0, uApp->icon("mimetypes/sound") );
		//item->setIcon( 0, uApp->icon("actions/reload") );

	mFiles[item] = audioFile;
	addTopLevelItem(item);
};
