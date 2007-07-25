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

#include "MainWindow.h"
#include "Application.h"
#include "DeviceManager.h"
#include "PluginManager.h"
#include "SettingsManager.h"
#include "DeviceInterface.h"
#include "MainTabWidget.h"
#include "ArtLabel.h"
#include "Device.h"
#include "iTunesLibraryImportExport.h"

#include "ComponentList.h"
#include "AddRemoveTestDialog.h"

#include <utopiadb/metabase.h>

// Qt includes
#include <QtCore/QTimer>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTextEdit>
#include <QtGui/QProgressBar>

// KDE includes
//#include <kmultitabbar.h>
//#include <ktabwidget.h>

#include <QtGui/QToolButton>
//#include <kiconloader.h>

//#include <kmenu.h>
//#include <kmenubar.h>
//#include <khelpmenu.h>

//#include <klocalizedstring.h>
//#include <kmessagebox.h>
//#include <kstdaction.h>
//#include <kaction.h>
//#include <kicon.h>

//#include <kurl.h>
//#include <khtmlview.h>
//#include <khtml_part.h>

//#include <kapplication.h>

#include "UtopiaDBImportOptions.h"
#include "ProgressSlider.h"
#include "VolumeSlider.h"
#include "PieChart.h"
#include "OptionsDialog.h"

MainWindow::MainWindow() : QMainWindow()
{
	setObjectName(QLatin1String("MainWindow"));

	createMainLayout();
	createSidebars();
	createMainSongList();
	createStatusbar();
	createMenus();

	setupActions();

	setWindowTitle( uApp->applicationName() );

	loadSettings();
	
	ComponentList *list = new ComponentList(0);
	AddRemoveTestDialog *dialog = new AddRemoveTestDialog(0);
	connect(dialog, SIGNAL(add(const QString&)), list, SLOT(addItem(const QString&)));
	connect(dialog, SIGNAL(remove(const QString&)), list, SLOT(removeItem(const QString&)));
	list->show();
	dialog->show();
};

MainWindow::~MainWindow()
{
	delete iTunes;
};

void MainWindow::setupActions()
{
	//KStdAction::quit(kapp, SLOT(quit()), actionCollection());
};

void MainWindow::showOptions()
{
	OptionsDialog *mOptionsDialog = new OptionsDialog();
	//connect(mOptionsDialog, SIGNAL(optionsChanged()), this, SLOT(refreshOptions()));
	//CenterWindow(mOptionsDialog);
	mOptionsDialog->show();
};

void MainWindow::createMainLayout()
{
	mMasterWidget = new QWidget(this);
	mMasterLayout = new QVBoxLayout(mMasterWidget);
	mMasterLayout->setMargin(3);
	mMasterLayout->setSpacing(3);

	mMainListWidget = new QWidget(mMasterWidget);
	mMainListLayout = new QVBoxLayout(mMainListWidget);
	mMainListLayout->setMargin(0);
	mMasterLayout->addWidget(mMainListWidget);

	/*
	KMultiTabBar* mTabBar = new KMultiTabBar(KMultiTabBar::Vertical, this);
	mTabBar->setStyle(KMultiTabBar::KDEV3ICON);
	mTabBar->setPosition(KMultiTabBar::Left);
	mMasterLayout->addWidget(mTabBar);

	mTabBar->appendTab(KIcon("juk").pixmap(16, 16), 1, tr("Tab 1"));
	mTabBar->appendTab(KIcon("juk").pixmap(16, 16), 2, tr("Tab 2"));
	mTabBar->setTab(1, true);
	*/

	setCentralWidget(mMasterWidget);
};

void MainWindow::resizeSourceList()
{
	mSourceView->resizeColumnToContents(0);
};

QTreeWidgetItem* MainWindow::currentSourceSelection() const
{
	if(!mSourceView->selectedItems().count())
		return 0;

	return mSourceView->selectedItems().at(0);
};

void MainWindow::closeEvent(QCloseEvent *event)
{
	saveSettings();

	QMainWindow::closeEvent(event);
};

QTreeWidget* MainWindow::sourceView()
{
	return mSourceView;
};

void MainWindow::refreshSourceList()
{
	//mSourceView->clear();
	QList<QTreeWidgetItem*> items = uApp->deviceManager()->deviceItems();
	mSourceView->addTopLevelItems(items);
	mSourceView->expandAll();
};

#include "sha1.h"
#include <QtGui/QMessageBox>
#include <utopiadb/blockparser.h>

void MainWindow::createSidebars()
{
	/*QFile file("/media/windows/Documents and Settings/Eric/My Documents/My Music/iTunes/iTunes Music Library.xml");
	file.open(QIODevice::ReadOnly);

	QXmlInputSource source(&file);
	iTunesLibraryParser handler;

	QXmlSimpleReader xmlReader;
	xmlReader.setContentHandler(&handler);
	xmlReader.setErrorHandler(&handler);
	xmlReader.parse(&source);*/

	mLibraryDock = new QDockWidget(this);
	mLibraryDock->setWindowTitle(tr("Source"));
	mLibraryDock->setObjectName(QLatin1String("SourceDock"));
	mLibraryDock->setAllowedAreas(Qt::DockWidgetAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea));
	mSourceView = new QTreeWidget(mLibraryDock);
	mSourceView->setItemHidden(mSourceView->headerItem(), true);
	mSourceView->setContextMenuPolicy(Qt::ActionsContextMenu);
	mSourceView->addAction( new QAction(QIcon("configure"), tr("Manage &Volumes..."), 0) );
	resizeSourceList();
	connect(mSourceView, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(resizeSourceList()));
	connect(mSourceView, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(resizeSourceList()));
	mSourceView->setAlternatingRowColors(true);
	mSourceView->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(mSourceView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showDeviceContextMenu(const QPoint&)));
	mLibraryDock->setWidget(mSourceView);
	addDockWidget(Qt::LeftDockWidgetArea, mLibraryDock);

	connect(uApp->deviceManager(), SIGNAL(deviceAdded(Device*)), this, SLOT(addDevice(Device*)));
	connect(uApp->deviceManager(), SIGNAL(deviceRemoved(Device*)), this, SLOT(removeDevice(Device*)));

	mCoverDock = new QDockWidget(this);
	mCoverDock->setWindowTitle(tr("Album Cover"));
	mCoverDock->setObjectName(QLatin1String("CoverDock"));
	mCoverDock->setAllowedAreas(Qt::DockWidgetAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea));
	mCoverLabel = new ArtLabel(mCoverDock);

	QPixmap noart(":/noart.png");
	QPixmap alpha = noart.alphaChannel();
	noart.fill( palette().brush(QPalette::Active, QPalette::Text).color() );
	noart.setAlphaChannel(alpha);
	mCoverLabel->setPixmap( noart );

	mCoverDock->setWidget(mCoverLabel);
	addDockWidget(Qt::LeftDockWidgetArea, mCoverDock);

	float samples[15] = { 5, 10, 44, 56, 51, 45, 789, 12, 1, 4, 66, 678, 13, 454, 4 };
	uchar digest[20];
	sha1_csum((uchar*)samples, sizeof(float)*15, digest);

	uchar digest2[20];
	float sample;
	sha1_context ctx;
    sha1_starts(&ctx);
	for(int i = 0; i < 16; i++)
	{
		sample = samples[i];
    	sha1_update(&ctx, (unsigned char*)&sample, sizeof(float));
	}
    sha1_finish(&ctx, digest2);

	//if( memcmp(digest, digest2, sizeof(uchar)*20) == 0);
		//QMessageBox::information(0, uApp->applicationName(), tr("They match! %1").arg(QByteArray((char*)digest, 20).toBase64().data()));
};

void MainWindow::showOptionsDialog()
{
	OptionsDialog *dialog = new OptionsDialog;
	dialog->show();
};

void MainWindow::createMainSongList()
{
	mProgressSlider = new ProgressSlider(mMasterWidget);
	mProgressSlider->setValue(50);
	mMasterLayout->addWidget(mProgressSlider);

	mRapidEdit = new QLineEdit;
	connect(mRapidEdit, SIGNAL(textChanged(const QString&)), this, SLOT(rapidFire(const QString&)));
	mMasterLayout->addWidget(mRapidEdit);

	QTimer *timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	timer->start(250);

	mSongTabs = new MainTabWidget(mMasterWidget);

	QToolButton *removeButton = new QToolButton( mSongTabs );
    removeButton->setIcon( uApp->icon("actions/tab_remove") );
    removeButton->adjustSize();
    removeButton->setToolTip(tr("Close the current tab"));
	connect(removeButton, SIGNAL(clicked()), this, SIGNAL(closeTab()));
	mSongTabs->setCornerWidget(removeButton, Qt::TopRightCorner);

	//mSongTabs->setHoverCloseButton(true);
	//mSongTabs->setTabCloseActivatePrevious(true);
	//mSongTabs->setTabReorderingEnabled(true);
	QListWidget *list = new QListWidget;
	QList<Utopia::Artist> artists = uApp->metaBase()->artists();
	QStringList artistNames;
	for(int i = 0; i < artists.count(); i++)
	{
		foreach(QString name, artists.at(i).artistNames())
		{
			artistNames << name;
		}
	}
	artistNames.sort();
	list->addItems(artistNames);

	mSongTabs->addTab(list, uApp->icon("filesystems/folder_sound"), tr("Music [%1]").arg("Untitled Volume"));
	mSongTabs->addTab(new QWidget, uApp->icon("filesystems/folder_video"), tr("Videos [%1]").arg(QString::fromUtf8("エリックのiPod")));
	mMasterLayout->addWidget(mSongTabs);
};

QTabWidget* MainWindow::tabWidget()
{
	return mSongTabs;
};

void MainWindow::createStatusbar()
{
	mStatusIndex = 0;
	mStatusTimer = new QTimer;
	connect(mStatusTimer, SIGNAL(timeout()), this, SLOT(rotateStatus()));

	// Create StatusBar
	mStatusBar = new QWidget(mMasterWidget);
	mStatusBarLayout = new QHBoxLayout(mStatusBar);
	mStatusBarLayout->setMargin(0);
	mStatusBarLayout->setSpacing(0);
	mMasterLayout->addWidget(mStatusBar);

	// Add content to the statusbar
	mPlayerLabel = new QLabel();
	mPlayerLabel->setPixmap(uApp->icon("actions/player_play").pixmap(16, 16));
	mStatusBarLayout->addWidget(mPlayerLabel);

	/*mStatusProgress = new QProgressBar;
	mStatusProgress->setMinimum(0);
	mStatusProgress->setMaximum(0);
	mStatusProgress->reset();
	mStatusBarLayout->addWidget(mStatusProgress);*/

	VolumeSlider *slider = new VolumeSlider();
	slider->setValue(95);
	connect((QObject*)slider, SIGNAL(valueChanged(int)), (QObject*)uApp->pluginManager(), SLOT(setVolume(int)));
	mStatusBarLayout->addWidget(slider);

	mStatusLabel = new QLabel(tr("Welcome to Utopia Player"));
	mStatusLabel->setSizePolicy(QSizePolicy::Expanding, mStatusLabel->sizePolicy().verticalPolicy());
	addStatusWidget(mStatusLabel);

	QLabel *mStatusLabel2 = new QLabel(tr("Player Stopped!!!"));
	mStatusLabel2->setSizePolicy(QSizePolicy::Expanding, mStatusLabel->sizePolicy().verticalPolicy());
	addStatusWidget(mStatusLabel2);
};

void MainWindow::createMenus()
{
	QMenuBar* mMenuBar = new QMenuBar(this);

	iTunes = new iTunesLibraryImportExport;

	QMenu* mFileMenu = new QMenu(tr("&File"), this);
	QMenu *mImportMenu = new QMenu(tr("&Import"));
	QAction *action = mImportMenu->addAction(tr("UtopiaDB XML..."));
	connect(action, SIGNAL(triggered()), this, SLOT(utopiaDBImport()));
	mImportMenu->addAction(iTunes->importAction());
	mFileMenu->addMenu(mImportMenu);
	QMenu *mExportMenu = new QMenu(tr("&Export"));
	action = mExportMenu->addAction(tr("UtopiaDB XML..."));
	mExportMenu->addAction(iTunes->exportAction());
	mFileMenu->addMenu(mExportMenu);
	mFileMenu->addSeparator();
	action = mFileMenu->addAction(tr("E&xit"));
	action->setIcon( uApp->icon("actions/exit") );
	connect(action, SIGNAL(triggered()), uApp, SLOT(quit()));
	mMenuBar->addMenu(mFileMenu);

	QMenu *mSettingsMenu = new QMenu(tr("&Settings"), this);
	mSettingsMenu->addAction(uApp->icon("actions/configure"), tr("&Configure Utopia Player..."), this, SLOT(showOptions()));
	mMenuBar->addMenu(mSettingsMenu);

	QMenu *mViewMenu = new QMenu(tr("&View"), this);
	QMenu *dockMenu = new QMenu(tr("&Docks"), this);
	dockMenu->addAction(mLibraryDock->toggleViewAction());
	dockMenu->addAction(mCoverDock->toggleViewAction());
	mViewMenu->addMenu(dockMenu);
	mMenuBar->addMenu(mViewMenu);

	setMenuBar(mMenuBar);
};

void MainWindow::loadSettings()
{
	if( uApp->settingsManager()->contains("MainWindow/Layout") )
		restoreState( uApp->settingsManager()->value("MainWindow/Layout").toByteArray() );
	if( uApp->settingsManager()->contains("MainWindow/Size") )
		resize( uApp->settingsManager()->value("MainWindow/Size").toSize() );
	if( uApp->settingsManager()->contains("MainWindow/Position") )
		move( uApp->settingsManager()->value("MainWindow/Position").toPoint() );
	if( uApp->settingsManager()->contains("MainWindow/State") )
		setWindowState( (Qt::WindowStates) uApp->settingsManager()->value("MainWindow/State").toInt() );
};

void MainWindow::utopiaDBImport()
{
	(new UtopiaDBImportOptions)->show();
};

void MainWindow::saveSettings()
{
	 uApp->settingsManager()->setValue("MainWindow/Layout", saveState());
	 uApp->settingsManager()->setValue("MainWindow/State", (int)windowState());
	 uApp->settingsManager()->setValue("MainWindow/Size", size());
	 uApp->settingsManager()->setValue("MainWindow/Position", pos());
};

QSize MainWindow::sizeHint() const
{
	return QSize(800, 600);
};

void MainWindow::showDeviceContextMenu(const QPoint& position)
{
	QList<QAction*> actions;

	// Get the item we clicked on
	QTreeWidgetItem *device = mSourceView->itemAt(position);
	if(!device)
		return;

	// Traverse up until we get to the top item in the chain
	QTreeWidgetItem *parentDevice = device;
	while(parentDevice->parent())
		parentDevice = parentDevice->parent();

	DeviceInterface *plugin = uApp->deviceManager()->devicePluginFromTreeItem(parentDevice);
	if(plugin)
		actions << plugin->contextMenu(parentDevice, device);

	if(actions.count() > 0)
		QMenu::exec(actions, mSourceView->mapToGlobal(position));
};

void MainWindow::addStatusWidget(QWidget *widget)
{
	if(!widget)
		return;

	mStatusWidgets << widget;

	mStatusBarLayout->insertWidget(mStatusBarLayout->indexOf(mPlayerLabel)+1, widget);

	if( mStatusWidgets.count() <= 1 )
	{
		mStatusIndex = mStatusWidgets.indexOf(widget);
	}
	else
	{
		mStatusIndex = mStatusWidgets.indexOf(widget) - 1;
		while(mStatusIndex < 0)
			mStatusIndex += mStatusWidgets.count();
	}

	rotateStatus();
	mStatusTimer->stop();
	mStatusTimer->start(3000);
};

void MainWindow::removeStatusWidget(QWidget *widget)
{
	if( !mStatusWidgets.contains(widget) )
		return;

	widget->hide();

	int index = mStatusWidgets.indexOf(widget);

	if(mStatusIndex == index)
	{
		rotateStatus();
		mStatusTimer->stop();
		mStatusTimer->start(3000);
	}

	mStatusWidgets.removeAt(index);
};

void MainWindow::rotateStatus()
{
	// Don't bother rotating if there is only one widget
	if( mStatusWidgets.count() <= 1 )
	{
		mStatusTimer->stop();
		return;
	}

	foreach(QWidget *widget, mStatusWidgets)
	{
		widget->hide();
	}

	// Remove the current status widget
	// mStatusBarLayout->removeWidget(mStatusWidgets.at(mStatusIndex));

	mStatusIndex++;

	while(mStatusIndex >= mStatusWidgets.count())
		mStatusIndex -= mStatusWidgets.count();

	// Insert the new widget onto the status bar
	// mStatusBarLayout->insertWidget(mStatusBarLayout->indexOf(mPlayerLabel)+1, mStatusWidgets.at(mStatusIndex));
	mStatusWidgets.at(mStatusIndex)->show();
};

void MainWindow::updateTime()
{
	mProgressSlider->setMinimum(0);
	mProgressSlider->setMaximum(uApp->pluginManager()->totalTime());
	mProgressSlider->setValue(uApp->pluginManager()->currentTime());
};

void MainWindow::addDevice(Device *device)
{
	mSourceView->addTopLevelItem( device->baseItem() );
};

void MainWindow::removeDevice(Device *device)
{
};

void MainWindow::rapidFire(const QString& location)
{
	if(location.isEmpty())
		return;

	mRapidEdit->setText( QString() );

	QUrl url(location);

	if(!url.isValid())
		url = QUrl::fromLocalFile(location);

	QStringList cover = url.toLocalFile().split("/");
	cover.removeLast();
	cover.append( QString("cover.png") );

	if( QFile(cover.join("/")).exists() )
	{
		uInfo("MainWindow", tr("Loading cover: %1").arg( cover.join("/") ));
		mCoverLabel->setPixmap( QPixmap(cover.join("/")) );
	}

	uApp->pluginManager()->play(location);
};
