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

#include "Application.h"
#include "AlbumList.h"
#include "SongList.h"
#include "SongListWindow.h"
#include "OptionsDialog.h"
#include "PluginManager.h"

#include "InsertAlbum.h"
#include "InsertArtist.h"
#include "InsertGenre.h"

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QDockWidget>
#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtGui/QStatusBar>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTableView>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>
#include <QtGui/QTextBrowser>
#include <QtGui/QTreeView>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFileDialog>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QListWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QSplitter>
#include <QtGui/QSystemTrayIcon>

#include "SaveTagsThread.h"
//#include <id3v2framefactory.h>

#include "OutputInterface.h"
#include <QtGui/QTableView>
#include <QtGui/QTableWidgetItem>

//#include <kaboutdialog.h>
//#include <kicon.h>

SongListWindow::SongListWindow() : QMainWindow(0, 0)
{
    // Code here.
	srand((unsigned)time(0));
	connect(uApp->pluginManager(), SIGNAL(finishedSong(const QString&)), this, SLOT(playRandomTrack()));

	mTrayIcon = new QSystemTrayIcon(QIcon(":/16x16/player_play.png"));
	mTrayIcon->setToolTip(tr("Welcome to UtopiaPlayer"));
	QMenu* mTrayMenu = new QMenu(tr("&Tray"));
	mTrayMenu->addAction(QIcon(":/16x16/fileclose.png"), tr("&Quit"), uApp, SLOT(quit()), tr("Ctrl+Q"));
	mTrayIcon->setContextMenu(mTrayMenu);
	mTrayIcon->show();
	connect(mTrayIcon, SIGNAL(activated(int)), this, SLOT(trayIconClicked(int)));
};

SongListWindow::~SongListWindow()
{
	// Code here.
};

void SongListWindow::createMainLayout()
{
	mMasterWidget = new QWidget(this);
	mMasterLayout = new QVBoxLayout(mMasterWidget);
	mMasterLayout->setMargin(0);

	mMainListWidget = new QWidget(mMasterWidget);
	mMainListLayout = new QVBoxLayout(mMainListWidget);
	mMainListLayout->setMargin(0);
	mMasterLayout->addWidget(mMainListWidget);

	setCentralWidget(mMasterWidget);
};

void SongListWindow::createSidebars()
{
	mLibraryDock = new QDockWidget(this);
	mLibraryDock->setWindowTitle("Source");
	mLibraryDock->setAllowedAreas(Qt::DockWidgetAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea));
	QTreeWidget* mSourceView = new QTreeWidget(mLibraryDock);
	mLibraryDock->setWidget(mSourceView);
	addDockWidget(Qt::LeftDockWidgetArea, mLibraryDock);

	mCoverDock = new QDockWidget(this);
	mCoverDock->setWindowTitle("Album Cover");
	mCoverDock->setAllowedAreas(Qt::DockWidgetAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea));
	QLabel* mCoverLabel = new QLabel(mCoverDock);
	mCoverDock->setWidget(mCoverLabel);
	addDockWidget(Qt::LeftDockWidgetArea, mCoverDock);
	mCoverDock->resize(mCoverDock->width(), mCoverDock->width());
};

void SongListWindow::createSliders()
{
	QWidget* mProgressWidget = new QWidget(mMainListWidget);
	QHBoxLayout* mProgressLayout = new QHBoxLayout(mProgressWidget);

	QLabel* mClockLabel = new QLabel(mProgressWidget);
	mClockLabel->setPixmap(QPixmap(":/16x16/clock.png"));
	mProgressLayout->addWidget(mClockLabel);

	QProgressBar* mSongProgress = new QProgressBar(mProgressWidget);
	mSongProgress->setTextVisible(false);
	mProgressLayout->addWidget(mSongProgress);

	QLabel* mVolumeLabel = new QLabel(mProgressWidget);
	mVolumeLabel->setPixmap(QPixmap(":/16x16/kmix.png"));
	mProgressLayout->addWidget(mVolumeLabel);

	mVolumeSlider = new QSlider(mProgressWidget);
	mVolumeSlider->setMinimum(0);
	mVolumeSlider->setMaximum(100);
	mVolumeSlider->setValue(100);
	mVolumeSlider->setPageStep(10);
	mVolumeSlider->setSingleStep(10);
	mVolumeSlider->setToolTip(QString("Volume: ") + QString::number(mVolumeSlider->value()) + "%"); 
	connect(mVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(adjustVolume(int)));
	mVolumeSlider->setOrientation(Qt::Horizontal);
	mVolumeSlider->setFixedWidth(100);
	mProgressLayout->addWidget(mVolumeSlider);

	mMainListLayout->addWidget(mProgressWidget);
};

void SongListWindow::createFilter()
{
	mFilterSplitter = new QSplitter(mMainListWidget);
	mFilterSplitter->setOrientation(Qt::Vertical);

	mFilterWidget = new QWidget(mFilterSplitter);
	QHBoxLayout* mFilterLayout = new QHBoxLayout(mFilterWidget);

	QListWidget* mGenreFilter = new QListWidget(mFilterWidget);
	mFilterLayout->addWidget(mGenreFilter);
	QListWidget* mArtistFilter = new QListWidget(mFilterWidget);
	mFilterLayout->addWidget(mArtistFilter);
	QListWidget* mAlbumFilter = new QListWidget(mFilterWidget);
	mFilterLayout->addWidget(mAlbumFilter);

	mFilterSplitter->addWidget(mFilterWidget);

	mMainListLayout->addWidget(mFilterSplitter);
};

void SongListWindow::createSongList()
{
	mSongList = new SongList(mFilterSplitter);
	mSongList->setObjectName("SongList");
	mFilterSplitter->addWidget(mSongList);

	mAlbumList = new AlbumList;
	mAlbumList->setObjectName("AlbumList");
};

void SongListWindow::createToolbars()
{
	// Main Toolbar
	mMainToolbar = new QToolBar(tr("&Main Toolbar"));
	mMainToolbar->addAction(QIcon(":/32x32/cdtrack.png"), tr("&Album List..."), this, SLOT(showAlbumList()));
	mMainToolbar->addAction(QIcon(":/32x32/vcard.png"), tr("A&rtist List..."), this, SLOT(insertArtist()));
	mMainToolbar->addAction(QIcon(":/32x32/document.png"), tr("&Genre List..."), this, SLOT(insertGenre()));
	mMainToolbar->addSeparator();
	mMainToolbar->addAction(QIcon(":/32x32/button_ok.png"), tr("&Request Song"), this, SLOT(queueSong()));
	mMainToolbar->addAction(QIcon(":/32x32/find.png"), tr("&Find Song..."), this, SLOT(findSong()));
	QAction* act = mMainToolbar->addAction(QIcon(":/32x32/filter.png"), tr("&Filter..."), this, SLOT(filterSongs()));
	act->setCheckable(true);

	// Edit Toolbar
	mEditToolbar = new QToolBar(tr("&Edit Toolbar"));
	mEditToolbar->addAction(QIcon(":/32x32/filenew.png"), tr("New &Song..."), this, SLOT(insertSong()));
	mEditToolbar->addAction(QIcon(":/32x32/edit.png"), tr("&Edit Song..."), this, SLOT(editSong()));
	mEditToolbar->addAction(QIcon(":/32x32/editdelete.png"), tr("&Delete Song"), this, SLOT(deleteSong()));

	// Play Toolbar
	mPlayToolbar = new QToolBar(tr("&Radio Controls"));
	mPlayToolbar->addAction(QIcon(":/32x32/player_start.png"), tr("&Previous Track"), this, SLOT(previousTrack()));
	//mPlayToolbar->addAction(QIcon(":/32x32/player_stop.png"), tr("&Stop Track"), uApp->pluginManager()->currentOutputPlugin(), SLOT(stop()));
	mPlayToolbar->addAction(QIcon(":/32x32/player_pause.png"), tr("&Pause Track"), this, SLOT(pauseTrack()));
	//mPlayToolbar->addAction(KIcon("utopia_play"), tr("&Play Track"), this, SLOT(playTrack()));
	mPlayToolbar->addAction(QIcon(":/32x32/player_end.png"), tr("&Next Track"), this, SLOT(nextTrack()));
	mPlayToolbar->addSeparator();
	mPlayToolbar->addAction(QIcon(":/32x32/decrypted.png"), tr("&Unlock Radio"), this, SLOT(lockRadio()));
	mPlayToolbar->addAction(QIcon(":/32x32/player_playlist.png"), tr("View &Radio Queue..."), this, SLOT(radioQueue()));
	mPlayToolbar->addAction(QIcon(":/32x32/contents.png"), tr("&User List..."), this, SLOT(userList()));
	act = mPlayToolbar->addAction(QIcon(":/32x32/roll.png"), tr("&Random Play"), this, SLOT(toggleRandom()));
	act->setCheckable(true);
	act->setChecked(true);
	mPlayToolbar->addAction(QIcon(":/32x32/configure.png"), tr("&Configure Radio..."), this, SLOT(radioOptions()));

    addToolBar(mMainToolbar);
	addToolBar(mEditToolbar);
	addToolBar(mPlayToolbar);
};

void SongListWindow::createMenus()
{
	// Create MenuBar
	mMenuBar = new QMenuBar(this);
	setMenuBar(mMenuBar);

	// File Menu
	QMenu* mFileMenu = mMenuBar->addMenu(tr("&File"));
	mFileMenu->addAction(QIcon(":/16x16/fileclose.png"), tr("&Close"), this, SLOT(close()), tr("Ctrl+W"));
	// Edit Menu
	QMenu* mEditMenu = mMenuBar->addMenu(tr("&Edit"));
	mEditMenu->addAction(QIcon(":/16x16/editcut.png"), tr("Cu&t"), this, SLOT(close()), tr("Ctrl+X"));
	mEditMenu->addAction(QIcon(":/16x16/editcopy.png"), tr("&Copy"), this, SLOT(close()), tr("Ctrl+C"));
	mEditMenu->addAction(QIcon(":/16x16/editpaste.png"), tr("&Paste"), this, SLOT(close()), tr("Ctrl+V"));
	// Records Menu
	mMenuBar->addMenu(tr("&Radio"));
	// Records Menu
	QMenu* mRecordsMenu = mMenuBar->addMenu(tr("&Records"));
	mRecordsMenu->addAction(QIcon(":/16x16/reload.png"), tr("&Refresh Database"), this, SLOT(updateDatabase()), tr("F5"));
	mRecordsMenu->addAction(QIcon(":/16x16/edit.png"), tr("&Save all tags..."), this, SLOT(saveTags()));

	// View Menu
	QMenu* mViewMenu = mMenuBar->addMenu(tr("&Settings"));
	QMenu* mToggleDockViewMenu = mViewMenu->addMenu(tr("&Docks"));
	mToggleToolbarViewMenu = mViewMenu->addMenu(tr("&Toolbars"));
	mViewMenu->addSeparator();
	mViewMenu->addAction(QIcon(":/16x16/configure.png"), tr("&Configure UtopiaPlayer..."), this, SLOT(showOptions()));
	// View Menu
	mMenuBar->addMenu(tr("&View"));

	// Help Menu
	//QMenu* mHelpMenu = mMenuBar->addMenu(tr("&Help"));
	//mHelpMenu->addAction(QIcon(":/16x16/help.png"), tr("&UtopiaPlayer &Handbook..."), this, SLOT(showHandbook()), tr("F1"));
	//mHelpMenu->addSeparator();
	//mHelpMenu->addAction(QIcon(":/16x16/configure.png"), tr("&About UtopiaPlayer..."), this, SLOT(showAboutDialog()));

	// Register our toolbars
	RegisterToolBar(mMainToolbar);
	RegisterToolBar(mEditToolbar);
	RegisterToolBar(mPlayToolbar);

	// Fix the names for saving and restoring states
	mMainToolbar->setObjectName("MainToolbar");
	mEditToolbar->setObjectName("EditToolbar");
	mPlayToolbar->setObjectName("RadioControls");

	mLibraryDock->setObjectName("SourceDock");
	QAction* act = mLibraryDock->toggleViewAction();
	act->setText("&Source");
	mToggleDockViewMenu->addAction(act);

	mCoverDock->setObjectName("CoverDock");
	act = mCoverDock->toggleViewAction();
	act->setText("&Album Cover");
	mToggleDockViewMenu->addAction(act);
};

void SongListWindow::createStatusbar()
{

	// Create StatusBar
	mStatusBar = new QWidget(mMasterWidget);
	mStatusBarLayout = new QHBoxLayout(mStatusBar);
	mStatusBarLayout->setMargin(0);
	mMasterLayout->addWidget(mStatusBar);

	mStatusLabel = new QLabel("Welcome to UtopiaPlayer");
	mStatusLabel->setSizePolicy(QSizePolicy::Expanding, mStatusLabel->sizePolicy().verticalPolicy());
	mStatusBarLayout->addWidget(mStatusLabel);
	QLabel* mPlayerLabel = new QLabel();
	//mPlayerLabel->setPixmap(KIcon("utopia_play").pixmap(16, 16));
	mStatusBarLayout->addWidget(mPlayerLabel);
	QLabel* mRandomLabel = new QLabel();
	mRandomLabel->setPixmap(QPixmap(":/16x16/roll.png"));
	mStatusBarLayout->addWidget(mRandomLabel);
	QLabel* mConnectionLabel = new QLabel();
	mConnectionLabel->setPixmap(QPixmap(":/16x16/connect_established.png"));
	mStatusBarLayout->addWidget(mConnectionLabel);

	//setStatusBar(mStatusBar);
};

void SongListWindow::restoreSettings()
{
	QSettings settings;
	if(settings.value("SongListWindow/Size").toSize().width() > 0 && settings.value("SongListWindow/Size").toSize().height() > 0)
		resize(settings.value("SongListWindow/Size").toSize());
	else
    	resize(800, 600);

	if(settings.value("SongListWindow/Position").toPoint().x() >= 0 && settings.value("SongListWindow/Position").toPoint().y() >= 0)
		move(settings.value("SongListWindow/Position").toPoint());
	else
    	CenterWindow(this);

	mSongList->restoreSettings();
	mAlbumList->restoreSettings();

	if(!settings.value("SongListWindow/State").toByteArray().isEmpty())
		restoreState(settings.value("SongListWindow/State").toByteArray());

	if(!settings.value("SongListWindow/SplitterState").toByteArray().isEmpty())
		mFilterSplitter->restoreState(settings.value("SongListWindow/SplitterState").toByteArray());

	mSplitterState = mFilterSplitter->saveState();

	mFilterWidget->hide();
};


void SongListWindow::CreateInterface()
{
	setUpdatesEnabled(false);

	createMainLayout();
	createSidebars();
	createSliders();
	createFilter();
	createSongList();
	createToolbars();
	createMenus();
	createStatusbar();
	restoreSettings();

	QSqlDatabase db = QSqlDatabase::database();
	setWindowTitle(QString("UtopiaPlayer - Song Database [" + db.hostName() + "]"));

	mSongList->show();

	setUpdatesEnabled(true);
};

void SongListWindow::showAboutDialog()
{
	//(new KAboutDialog)->show();
};

void SongListWindow::RegisterToolBar(QToolBar* Toolbar)
{
	for (std::vector<QToolBar*>::iterator i = mRegisteredToolBars.begin(); i != mRegisteredToolBars.end(); i++ )
	{
		if (*i == Toolbar)
			throw std::string("Toolbar " + std::string(Toolbar->windowTitle().toAscii().data()) + " already registered!");
	}
	
	QAction* toggleViewAction = Toolbar->toggleViewAction();
	toggleViewAction->setText(Toolbar->windowTitle());
	toggleViewAction->setToolTip(tr("Toggle visibility of ToolBar '") + Toolbar->windowTitle() + "'");
	toggleViewAction->setStatusTip(tr("Toggle visibility of ToolBar '") + Toolbar->windowTitle() + "'");
	
	mToggleToolbarViewMenu->addAction(toggleViewAction);
	
    addToolBar(Toolbar);
	mRegisteredToolBars.push_back(Toolbar);
};

QSize SongListWindow::sizeHint() const
{
    return QSize(800, 600);
};

void SongListWindow::CenterWindow(QWidget* window)
{
    QDesktopWidget* mDesktop = QApplication::desktop();
    QRect mScreen = mDesktop->screenGeometry(mDesktop->primaryScreen());
    int iWindowX = ((mScreen.width() - window->width()) / 2) + mScreen.x();
    int iWindowY = ((mScreen.height() - window->height()) / 2) + mScreen.y();
    window->move(iWindowX, iWindowY);

    return;
};

void SongListWindow::saveTags()
{
	//TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding( TagLib::String::UTF8 );

	QSqlQuery query(QString::fromUtf8("SELECT * FROM `un_songs`"));

	QProgressBar* mTagProgress = new QProgressBar;
	mTagProgress->setMaximum( query.size() );
	mTagProgress->resize(640, 30);
	CenterWindow(mTagProgress);
	mTagProgress->show();

	SaveTagsThread* save = new SaveTagsThread(QSqlDatabase());

	connect(save, SIGNAL(valueChanged(int)), mTagProgress, SLOT(setValue(int)));
	connect(save, SIGNAL(finished()), mTagProgress, SLOT(close()));

	save->start();
/*

	QSettings settings;
	QString mMusicDirectory = settings.value("General/MusicDirectory").toString();
	int mUseKanji = settings.value("General/UseKanji").toInt();

	QSqlQuery query(QString::fromUtf8("SELECT * FROM `un_songs`"));

	QProgressBar* mTagProgress = new QProgressBar;
	mTagProgress->setMaximum( query.size() );
	mTagProgress->resize(640, 30);
	SongListWindow::CenterWindow(mTagProgress);
	mTagProgress->show();

	int count = 0;

    while (query.next())
	{
		count++;

		mTagProgress->setValue(count);
		mTagProgress->update();

		QString title;
		QString album;
		QString artist;
		QString genre;

		std::cout << "Song " << query.record().value( QString::fromUtf8("ID") ).toInt() << std:: endl;

		QSqlQuery qartist(QString::fromUtf8("SELECT * FROM `un_artists` WHERE `ID` = '") + query.record().value( QString::fromUtf8("Artist") ).toString() + QString::fromUtf8("'"));
		QSqlQuery qalbum(QString::fromUtf8("SELECT * FROM `un_albums` WHERE `ID` = '") + query.record().value( QString::fromUtf8("Album") ).toString() + QString::fromUtf8("'"));
		QSqlQuery qgenre(QString::fromUtf8("SELECT * FROM `un_genres` WHERE `ID` = '") + query.record().value( QString::fromUtf8("Genre") ).toString() + QString::fromUtf8("'"));

		qartist.next();
		qalbum.next();
		qgenre.next();

		if(mUseKanji == Qt::Checked)
		{
			title = query.record().value( QString::fromUtf8("タイトル") ).toString();
			artist = qartist.record().value( QString::fromUtf8("アーチスト") ).toString();
			album = qalbum.record().value( QString::fromUtf8("アルバム") ).toString();
			genre = qgenre.record().value( QString::fromUtf8("ジャンル") ).toString();
		}
		else
		{
			title = query.record().value( QString::fromUtf8("Title") ).toString();
			artist = qartist.record().value( QString::fromUtf8("Artist") ).toString();
			album = qalbum.record().value( QString::fromUtf8("Album") ).toString();
			genre = qgenre.record().value( QString::fromUtf8("Genre") ).toString();
		}

		QString path = mMusicDirectory + query.record().value( QString::fromUtf8("Path") ).toString();

		TagLib::FileRef f( path.toUtf8().data() );

		std::cout << title.toUtf8().data() << " - ";
		std::cout << artist.toUtf8().data() << std::endl;
		f.tag()->setTitle( TagLib::String(title.toUtf8().data(), TagLib::String::UTF8) );
		f.tag()->setArtist( TagLib::String(artist.toUtf8().data(), TagLib::String::UTF8) );
		f.tag()->setAlbum( TagLib::String(album.toUtf8().data(), TagLib::String::UTF8) );
		f.tag()->setComment( TagLib::String("Music from Utopia Network <www.utopia.net>\nTagged with UtopiaPlayer, Copyright (C) 2006 John Eric Martin <cpuwhiz105@users.sourceforge.net>", TagLib::String::UTF8) );
		f.tag()->setGenre( TagLib::String(genre.toUtf8().data(), TagLib::String::UTF8) );
		f.tag()->setYear( qalbum.record().value( QString::fromUtf8("ReleaseDate") ).toDate().year() );
		f.tag()->setTrack( query.record().value( QString::fromUtf8("Track") ).toInt() );

		if(!f.save())
			std::cout << "FAIL!" << std::endl;
	}

	std::cout << "Finished Tags!!!" << std::endl;

	delete mTagProgress;*/
};

void SongListWindow::refreshOptions()
{
	emit optionsChanged();
};

void SongListWindow::showOptions()
{
	mOptionsDialog = new OptionsDialog();
	connect(mOptionsDialog, SIGNAL(optionsChanged()), this, SLOT(refreshOptions()));
	CenterWindow(mOptionsDialog);
	mOptionsDialog->show();
};

void SongListWindow::insertSong()
{
};

void SongListWindow::insertArtist()
{
	mInsertArtist = new InsertArtist(this);
	connect(mInsertArtist, SIGNAL(updateDatabase()), this, SLOT(updateDatabase()));
	//CenterWindow(mInsertArtist);
	mInsertArtist->show();
};

void SongListWindow::showAlbumList()
{
	mInsertAlbum = new InsertAlbum(this);
	connect(mInsertAlbum, SIGNAL(updateDatabase()), this, SLOT(updateDatabase()));
	mInsertAlbum->show();
//	if(mAlbumList->isVisible())
//		mAlbumList->hide();
//	else
//		mAlbumList->show();
};

void SongListWindow::filterSongs()
{
	if(mFilterWidget->isVisible())
	{
		mSplitterState = mFilterSplitter->saveState();
		mFilterWidget->hide();
	}
	else
	{
		mFilterWidget->show();
	}
};

void SongListWindow::insertAlbum()
{
	mInsertAlbum = new InsertAlbum();
	connect(this, SIGNAL(optionsChanged()), mInsertAlbum, SLOT(refreshOptions()));
	connect(mInsertAlbum, SIGNAL(updateDatabase()), this, SLOT(updateDatabase()));
	CenterWindow(mInsertAlbum);
	mInsertAlbum->show();
};

void SongListWindow::insertGenre()
{
	mInsertGenre = new InsertGenre();
	connect(mInsertGenre, SIGNAL(updateDatabase()), this, SLOT(updateDatabase()));
	CenterWindow(mInsertGenre);
	mInsertGenre->show();
};

void SongListWindow::updateDatabase()
{
	mSongList->refreshTable();
	mAlbumList->refreshTable();
};

void SongListWindow::saveSettings()
{
	QSettings settings;
	settings.setValue("SongListWindow/Size", size());
	settings.setValue("SongListWindow/Position", pos());
	settings.setValue("AlbumListWindow/Size", mAlbumList->size());
	settings.setValue("AlbumListWindow/Position", mAlbumList->pos());

	mSongList->saveSettings();
	mAlbumList->saveSettings();

	mFilterWidget->show();
	settings.setValue("SongListWindow/State", saveState());

	if(mFilterWidget->isVisible())
		settings.setValue("SongListWindow/SplitterState", mFilterSplitter->saveState());
	else
		settings.setValue("SongListWindow/SplitterState", mSplitterState);
};

void SongListWindow::playTrack()
{
	QSettings settings;

	//PluginManager::currentOutputPlugin()->play( mSongList->item( mSongList->selectedIndexes().first().row(), 8 )->text() );
	//PluginManager::currentOutputPlugin()->play( QString::fromUtf8("/mnt/utopia/music/HIGH and MIGHTY COLOR/一輪の花/01 一輪の花.mp3") );

	//if(mSongList->selectedRows().size() > 0)
		//uApp->pluginManager()->currentOutputPlugin()->play( settings.value("General/MusicDirectory").toString() + mSongList->getSongAtRow(mSongList->selectedRows()[0]) );
};

void SongListWindow::pauseTrack()
{
	//if(uApp->pluginManager()->currentOutputPlugin()->isPaused())
		//uApp->pluginManager()->currentOutputPlugin()->unpause();
	//else
		//uApp->pluginManager()->currentOutputPlugin()->pause();
};

void SongListWindow::nextTrack()
{
	// TODO - Fix me
	playRandomTrack();
};

void SongListWindow::playRandomTrack()
{
	QSettings settings;
	int rnum = rand() % (mSongList->rowCount() - 1);
	//uApp->pluginManager()->currentOutputPlugin()->play( settings.value("General/MusicDirectory").toString() + mSongList->getSongAtRow( rnum ) );
	//std::cout << "Track: " << rnum << " of " << mSongList->rowCount() << std::endl;
};

void SongListWindow::adjustVolume(int volume)
{
	//uApp->pluginManager()->currentOutputPlugin()->setVolume((float)volume/100);
	mVolumeSlider->setToolTip(QString("Volume: ") + QString::number(mVolumeSlider->value()) + "%");
};

void SongListWindow::cleanup()
{
	mSongList->clearTable();
	mAlbumList->clearTable();
};

void SongListWindow::trayIconClicked(int reason)
{
	if(reason == QSystemTrayIcon::DoubleClick)
		show();
	if(reason == QSystemTrayIcon::Trigger)
	{
		if(isVisible())
			hide();
		else
			show();
	}

	//mTrayIcon->showMessage("trayIconClicked(int)", tr("The tray icon has been clicked!"));
};
