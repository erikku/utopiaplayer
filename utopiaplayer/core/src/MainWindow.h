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

#ifndef __MainWindow_h__
#define __MainWindow_h__

// Qt includes
#include <QtCore/QList>
#include <QtGui/QMainWindow>

class QLabel;
class QTimer;
class QWidget;
class QLineEdit;
class QTabWidget;
class QTreeWidget;
class QDockWidget;
class QHBoxLayout;
class QVBoxLayout;
class QTreeWidgetItem;
class iTunesLibraryImportExport;

class Device;
class ArtLabel;
class ProgressSlider;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	virtual ~MainWindow();

	QTreeWidgetItem* currentSourceSelection() const;

	QTabWidget* tabWidget();
	QTreeWidget* sourceView();

	virtual QSize sizeHint() const;

public slots:
	void updateTime();
	void showOptions();
	void refreshSourceList();
	void showDeviceContextMenu(const QPoint& position);
	void resizeSourceList();

	void addStatusWidget(QWidget *widget);
	void removeStatusWidget(QWidget *widget);

	void rapidFire(const QString& location);

signals:
	void closeTab();

protected slots:
	void rotateStatus();
	void utopiaDBImport();
	void showOptionsDialog();

	void addDevice(Device *device);
	void removeDevice(Device *device);

protected:
	void closeEvent(QCloseEvent *event);

	void setupActions();
	void createMainLayout();
	void createSidebars();
	void createMainSongList();
	void createStatusbar();
	void createMenus();

	void loadSettings();
	void saveSettings();

	QWidget     *mMasterWidget;
	QVBoxLayout *mMasterLayout;
	QWidget     *mMainListWidget;
	QVBoxLayout *mMainListLayout;

	// Sidebars
	QDockWidget *mLibraryDock;
	QTreeWidget *mSourceView;
	QDockWidget *mCoverDock;
	ArtLabel    *mCoverLabel;

	// Statusbar
	int mStatusIndex;
	QWidget     *mStatusBar;
	QLabel      *mPlayerLabel;
	QLabel      *mStatusLabel;
	QTimer      *mStatusTimer;
	QHBoxLayout *mStatusBarLayout;
	QList<QWidget*> mStatusWidgets;
	iTunesLibraryImportExport *iTunes;

	ProgressSlider *mProgressSlider;

	QLineEdit *mRapidEdit;
	QTabWidget *mSongTabs;
};

#endif // __MainWindow_h__
