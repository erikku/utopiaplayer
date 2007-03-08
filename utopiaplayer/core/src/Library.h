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

#ifndef __SongListWindow_h__
#define __SongListWindow_h__

// Qt Libs
#include <QtCore/QByteArray>
#include <QtGui/QMainWindow>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlRelationalDelegate>
#include <QtSql/QSqlDatabase>

// Pre-declared Qt widgets to keep compile times down
class QSqlRelationalTableModel;
class QStatusBar;
class QMenuBar;
class QMenu;
class QToolBar;
class QTableView;
class QDockWidget;
class QWidget;
class QVBoxLayout;
class QSplitter;
class QByteArray;

class AlbumList;

class OptionsDialog;
class InsertAlbum;
class InsertArtist;
class InsertGenre;

/**
 * @brief The class for the main application window.
 * The SongListWindow class displays a main window containing a list of
 * songs in the database and provides menu options, toolbar buttons, etc.
 * to add, edit, and delete song, album, artist, and genre entries. It also
 * provides access to the radio controls and settings.
 *
 * The mSongView widget links to the QSqlRelationalTableModel that provies
 * access to the song table. mSongView relates the artist, album, genre,
 * and rating to the respective tables and uses a QSqlRelationalDelegate
 * to create a combo box in which to select these items for a given song.
 */
class SongListWindow : public QMainWindow, public Singleton<SongListWindow>
{
    Q_OBJECT

public:
    SongListWindow();
    ~SongListWindow();

    void CreateInterface();

    QSize sizeHint() const;

    // Functions to handle Singleton use.
   	static SongListWindow& GetSingleton(void);
   	static SongListWindow* GetSingletonPtr(void);

	static void CenterWindow(QWidget* window);
protected:
	QSqlRelationalTableModel* mSongList;
	QTableView* mSongView;

	AlbumList* mAlbumList;

	QMenu* mToggleToolbarViewMenu;
	QStatusBar* mStatusBar;
	QMenuBar* mMenuBar;

	QToolBar* mMainToolbar;
	QToolBar* mEditToolbar;
	QToolBar* mPlayToolbar;

	QDockWidget* mLibraryDock;
	QDockWidget* mCoverDock;

	OptionsDialog* mOptionsDialog;
	InsertAlbum* mInsertAlbum;
	InsertArtist* mInsertArtist;
	InsertGenre* mInsertGenre;

	QWidget* mFilterWidget;
	QSplitter* mFilterSplitter;
	QByteArray mSplitterState;

	QWidget* mMainListWidget;
	QVBoxLayout* mMainListLayout;

	std::vector<QToolBar*> mRegisteredToolBars;

	void RegisterToolBar(QToolBar* Toolbar);

	void createMainLayout();
	void createSidebars();
	void createSliders();
	void createFilter();
	void createSongList();
	void createToolbars();
	void createMenus();
	void createStatusbar();
	void restoreSettings();

signals:
	void optionsChanged();

private slots:

public slots:
	void saveTags();
	void filterSongs();
	void showAlbumList();
	void saveSettings();
	void updateDatabase();
	void refreshOptions();
	void showOptions();
	void insertSong();
	void insertArtist();
	void insertAlbum();
	void insertGenre();
	void cleanup();
};

#endif // __SongListWindow_h__
