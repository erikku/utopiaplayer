#include "ipod.h"
#include "iPodNotes.h"
#include "MainWindow.h"
#include "Application.h"

#include <QtCore/QFile>
#include <QtCore/QRegExp>
#include <QtCore/QSettings>
#include <QtGui/QAction>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QListWidget>
#include <QtGui/QInputDialog>
#include <QtGui/QMessageBox>

#include "mhdb.h"

iPod::iPod(const QString& path, DeviceInterface *plugin, QObject *parent) : Device(plugin, parent), mPath(path)
{
	mNotesPath = mPath + QDir::separator() + "Notes";

	mBaseItem = new QTreeWidgetItem(QStringList() << name());
	mBaseItem->setIcon(0, uApp->icon("devices/ipod_unmount"));

	mMusicItem = new QTreeWidgetItem(QStringList() << tr("Music"));
	mMusicItem->setIcon(0, uApp->icon("filesystems/folder_sound"));
	mBaseItem->addChild( mMusicItem );

	mVideosItem = new QTreeWidgetItem(QStringList() << tr("Videos"));
	mVideosItem->setIcon(0, uApp->icon("filesystems/folder_video"));
	mBaseItem->addChild( mVideosItem );

	mNotesItem = new QTreeWidgetItem(QStringList() << tr("Notes"));
	mNotesItem->setIcon(0, uApp->icon("filesystems/folder_txt"));
	mBaseItem->addChild( mNotesItem );

	mImagesItem = new QTreeWidgetItem(QStringList() << tr("Images"));
	mImagesItem->setIcon(0, uApp->icon("filesystems/folder_image"));
	mBaseItem->addChild( mImagesItem );

	mPlaylistsItem = new QTreeWidgetItem(QStringList() << tr("Playlists"));
	mPlaylistsItem->setIcon(0, uApp->icon("filesystems/folder_favorite"));
	mBaseItem->addChild( mPlaylistsItem );
	/*
	QAction *action = new QAction(0);
	action->setSeparator(true);
	mVideoActions << action;

	action = new QAction(tr("&Sync"), 0);
	mVideoActions << action;
	*/

	QAction *action = new QAction(tr("&Edit..."), 0);
	action->setIcon(uApp->icon("actions/edit"));
	connect(action, SIGNAL(triggered(bool)), this, SLOT(showNoteEditor()));
	mNoteFileActions << action;

	action = new QAction(tr("&New Note..."), 0);
	action->setIcon(uApp->icon("actions/filenew"));
	connect(action, SIGNAL(triggered(bool)), this, SLOT(newNote()));
	mNoteFolderActions << action;
	action = new QAction(tr("New &Folder..."), 0);
	action->setIcon(uApp->icon("filesystems/folder"));
	connect(action, SIGNAL(triggered(bool)), this, SLOT(newNoteFolder()));
	mNoteFolderActions << action;

	connect(uApp->mainWindow(), SIGNAL(closeTab()), this, SLOT(closeTab()));

	loadConfig();
	saveConfig();
};

void iPod::newNote()
{
	QTreeWidgetItem *item = uApp->mainWindow()->currentSourceSelection();

	if(!item)
		return;

	if(mNotesMap.contains(item)) // We can't make a note inside a note!
		return;

	bool ok;
	QString name = QInputDialog::getText(0, tr("New Note"), tr("New note file name:"), QLineEdit::Normal, tr("Untitled Note"), &ok);
	if(!ok || name.isEmpty())
		return;

	QTreeWidgetItem *node = new QTreeWidgetItem(QStringList() << name, 0);
	node->setIcon( 0, uApp->icon("mimetypes/txt") );
	item->addChild(node);
	mNotesMap[node] = pathFromNode(node);
	sortNotesDirectory(item);

	QFile file(mNotesPath + QDir::separator() + pathFromNode(node));
	if( file.exists() )
	{
		QMessageBox::warning(0, uApp->applicationName(), tr("Notes file <i>%1</i> already exists!").arg(name));
		mNotesMap.remove(node);
		delete node;
		return;
	}
	if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
	{
		QMessageBox::warning(0, uApp->applicationName(), tr("Unable to open file <i>%1</i> for writing!").arg(name));
		mNotesMap.remove(node);
		delete node;
		return;
	}

	QByteArray data = tr("<?xml encoding=\"UTF-8\"?>\n<title>%1</title>\n%2").arg(name).arg(tr("Note contents goes here.")).toUtf8();

	if( data.count() != file.write( data ) )
	{
		QMessageBox::warning(0, uApp->applicationName(), tr("Error writing to file <i>%1</i>!").arg(name));
		mNotesMap.remove(node);
		delete node;
	}

	file.flush();
	file.close();
};

void iPod::newNoteFolder()
{
	QTreeWidgetItem *item = uApp->mainWindow()->currentSourceSelection();

	if(!item)
		return;

	if(mNotesMap.contains(item)) // We can't make a note folder inside a note!
		return;

	bool ok;
	QString name = QInputDialog::getText(0, tr("New Note Folder"), tr("New note folder name:"), QLineEdit::Normal, tr("Untitled Directory"), &ok);
	if(!ok || name.isEmpty())
		return;

	QTreeWidgetItem *node = new QTreeWidgetItem(QStringList() << name, 0);
	node->setIcon( 0, uApp->icon("filesystems/folder") );
	item->addChild(node);
	sortNotesDirectory(item);

	QDir dir(mNotesPath + QDir::separator() + pathFromNode(item));
	if( !dir.mkdir(name) )
	{
		QMessageBox::warning(0, uApp->applicationName(), tr("Error creating <i>%1</i> notes directory!").arg(name));
		delete node;
	}
};

QString iPod::pathFromNode(QTreeWidgetItem *node) const
{
	QTreeWidgetItem *item = node;
	QString path = item->text(0);

	item = item->parent();

	while(item && item != mNotesItem)
	{
		path = item->text(0) + QDir::separator() + path;
		item = item->parent();
	}

	return path;
};

void iPod::showNoteEditor()
{
	QTreeWidgetItem *item = uApp->mainWindow()->currentSourceSelection();

	if(!item)
		return;

	if(!mNotesMap.contains(item))
		return;

	iPodNotes *notes = new iPodNotes;
	mNoteTabs << notes;
	notes->setTreeItem(item);
	notes->load( mNotesPath + QDir::separator() + mNotesMap.value(item) );
	uApp->mainWindow()->tabWidget()->addTab(notes, uApp->icon("mimetypes/txt"), tr("Notes [%1]").arg(notes->title()));
};

void iPod::closeTab()
{
	QTabWidget *widget = uApp->mainWindow()->tabWidget();
	if(!widget)
		return;

	iPodNotes *note = (iPodNotes*)widget->currentWidget();

	if( !mNoteTabs.contains(note) )
		return;

	if( !note->changed() )
	{
		mNoteTabs.removeAt( mNoteTabs.indexOf(note) );
		delete 	note;
		return;
	}

	switch( QMessageBox::question(0, note->title(), tr("Save changes to the document?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes ) )
	{
		case QMessageBox::Yes:
			note->save();
		case QMessageBox::No:
			mNoteTabs.removeAt( mNoteTabs.indexOf(note) );
			delete 	note;
			return;
		default:
			return;
	}
};

void iPod::loadConfig()
{
	/*
	QFile deviceInfo(mPath + "/iPod_Control/iTunes/DeviceInfo");
	deviceInfo.open(QIODevice::ReadOnly);
	mDeviceInfo = deviceInfo.readAll();
	deviceInfo.close();
	*/
	/*
	QFile db(mPath + "/iPod_Control/iTunes/iTunesDB");
	db.open(QIODevice::ReadOnly);
	quint32 header;
	if( db.read((char*)&header, sizeof(quint32)) != sizeof(quint32) )
		return;
	mhdb *data = new mhdb;
	data->read(&db);
	data->show();
	db.close();
	
	QListWidget *list = new QListWidget;
	list->addItems( listRecursiveDirectoryContents(mPath, QStringList(), QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name) );
	list->show();
	*/

	/*
	QFile configFile( mPath + tr("/.utopiaplayer/volume.ini") );
	if(!configFile.exists())
		return;

	QSettings settings(mPath + tr("/.utopiaplayer/volume.ini"), QSettings::IniFormat);

	QString volumeName;
	if(settings.contains("General/Name"))
		mVolumeName = settings.value("General/Name").toString();
	else
		mVolumeName = tr("Untitled Volume");
	*/
	QStringList directories = uApp->listRecursiveDirectoryContents(mNotesPath, QStringList(), QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
	foreach(QString dir, directories)
	{
		addNoteDirectory(dir.replace(mNotesPath + QDir::separator(), ""));
	}

	QStringList files = uApp->listRecursiveDirectoryContents(mNotesPath, QStringList(), QDir::Files, QDir::Name);
	foreach(QString file, files)
	{
		addNoteFile(file.replace(mNotesPath + QDir::separator(), ""));
	}
};

void iPod::addNoteDirectory(const QString& dir)
{
	QTreeWidgetItem *item = mNotesItem;
	QTreeWidgetItem *newItem;
	QStringList elements = dir.split(QDir::separator());

	foreach(QString element, elements)
	{
		newItem = 0;
		for(int i = 0; i < item->childCount(); i++)
		{
			if( item->child(i)->text(0) == element )
			{
				newItem = item->child(i);
				break;
			}
		}

		// If we have not found the dir element, we need to add it and resort
		if(!newItem)
		{
			newItem = new QTreeWidgetItem(QStringList() << element);
			newItem->setIcon( 0, uApp->icon("filesystems/folder") );
			item->addChild(newItem);
			sortNotesDirectory(item);
		}

		item = newItem;
	}
};

void iPod::addNoteFile(const QString& file)
{
	QStringList elements = file.split(QDir::separator());
	QString fileName = elements.takeLast();
	QTreeWidgetItem *item = mNotesItem;

	foreach(QString element, elements)
	{
		for(int i = 0; i < item->childCount(); i++)
		{
			if( item->child(i)->text(0) == element )
			{
				item = item->child(i);
				break;
			}
		}
	}

	QString title = fileName.replace(QRegExp("\\..*$"), "");

	QFile in(mNotesPath + QDir::separator() + file);
	if(in.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString line = QString::fromUtf8( in.readLine().data() );

		QRegExp encodingHeader("^\\s*<\\?xml encoding=\\\".*\\\"\\?>\\s*$");
		if(encodingHeader.exactMatch(line))
			line = QString::fromUtf8( in.readLine().data() );

		QRegExp cheapHeader("^\\s*<title>(.*)</title>\\s*$");
		if(cheapHeader.exactMatch(line))
			title = cheapHeader.cap(1);

		in.close();
	}

	QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList() << title);
	newItem->setIcon( 0, uApp->icon("mimetypes/txt") );
	item->addChild(newItem);

	// This goes before sorting so it includes the file in the list of files and not in the list of directories
	mNotesMap[newItem] = file;

	sortNotesDirectory(item);
};

void iPod::sortNotesDirectory(QTreeWidgetItem *node)
{
	if(!node)
		return;

	QList<QTreeWidgetItem*> nodes = node->takeChildren();
	QMap<QString, QTreeWidgetItem*> folders, files;

	for(int i = 0; i < nodes.count(); i++)
	{
		if( mNotesMap.keys().contains(nodes.at(i)) )
			files[nodes.at(i)->text(0)] = nodes.at(i);
		else
			folders[nodes.at(i)->text(0)] = nodes.at(i);
    }

	QStringList fileKeys = files.keys(), folderKeys = folders.keys();

	qSort(folderKeys);
	qSort(fileKeys);

	foreach(QString key, folderKeys)
	{
		node->addChild( folders.value(key) );
	}

	foreach(QString key, fileKeys)
	{
		node->addChild( files.value(key) );
	}
};

QString iPod::name() const
{
	/*
	char *string = new char[510];

	QFile deviceInfo(mPath + "/iPod_Control/iTunes/DeviceInfo");
	deviceInfo.open(QIODevice::ReadOnly);

	deviceInfo.read(string, 2);
	deviceInfo.read(string, 510);
	QString iPodName = QString::fromUtf16( (ushort*)string );

	deviceInfo.read(string, 2);
	deviceInfo.read(string, 510);
	QString UserName = QString::fromUtf16( (ushort*)string );

	deviceInfo.read(string, 2);
	deviceInfo.read(string, 510);
	QString ComputerName = QString::fromUtf16( (ushort*)string );

	deviceInfo.close();
	delete[] string;

	return iPodName;
	*/
	return QString::fromUtf8("エリックのiPod");
};

void iPod::saveConfig()
{
	QString iPodName = QString::fromUtf8("エリックのiPod");
	QString UserName = QString::fromUtf8("エリック");
	QString ComputerName = QString::fromUtf8("Tiberius");

	ushort size;
	char *string;

	QFile deviceInfo(mPath + "/iPod_Control/iTunes/DeviceInfo");
	deviceInfo.open(QIODevice::WriteOnly);

	size = iPodName.length();
	deviceInfo.write((char*)&size,  2);
	string = (char*)calloc(1, 510);
	memcpy(string, iPodName.utf16(), iPodName.length() * 2);
	deviceInfo.write(string, 510);
	free(string);

	size = iPodName.length();
	deviceInfo.write((char*)&size,  2);
	string = (char*)calloc(1, 510);
	memcpy(string, iPodName.utf16(), iPodName.length() * 2);
	deviceInfo.write(string, 510);
	free(string);

	size = iPodName.length();
	deviceInfo.write((char*)&size,  2);
	string = (char*)calloc(1, 510);
	memcpy(string, iPodName.utf16(), iPodName.length() * 2);
	deviceInfo.write(string, 510);
	free(string);

	deviceInfo.close();
	/*
	QSettings settings(mPath + tr("/.utopiaplayer/volume.ini"), QSettings::IniFormat);

	settings.setValue("General/Name", mVolumeName);
	*/
};

QTreeWidgetItem* iPod::baseItem()
{
	return mBaseItem;
};

QList<QAction*> iPod::contextMenu(QTreeWidgetItem *item) const
{
	QList<QAction*> actions;

	if(mNotesMap.keys().contains(item))
		actions << mNoteFileActions;
	else
		actions << mNoteFolderActions;

	return actions;
};
