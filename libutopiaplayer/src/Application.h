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

#ifndef __Application_h__
#define __Application_h__

// Qt4 includes
#include <QtCore/QDir>
#include <QtCore/QMap>
#include <QtCore/QStringList>
#include <QtGui/QApplication>

#include "Logger.h"

namespace Utopia
{
	class MetaBase;
};

class Logger;
class GUIManager;
class SettingsManager;
class MainWindow;
class SongManager;
class DeviceManager;
class PluginManager;
class PluginInterface;
class FileTypeFactory;

class AudioThread;

typedef enum StartupMode
{
	Auto,
	Minimal,
	Full
};

/**
 * @brief This class starts and stops the application.
 */
class Application : public QApplication
{
    Q_OBJECT

public:
	Application(int argc, char *argv[]);
	~Application();

    void Init(StartupMode mode = Auto);

	Utopia::MetaBase* metaBase() const;

	Logger* logger() const;
	MainWindow* mainWindow() const;
	GUIManager* guiManager() const;
	SongManager* songManager() const;
	DeviceManager* deviceManager() const;
	PluginManager* pluginManager() const;
	SettingsManager* settingsManager() const;
	FileTypeFactory* fileTypeFactory() const;

	QDir settingsDir() const;

	AudioThread* audioThread() const;

	static QStringList listRecursiveDirectoryContents(const QDir& dir, const QStringList& nameFilters = QStringList() << "*", QDir::Filters filters = QDir::Files, QDir::SortFlags sort = QDir::Name);
	static QString makePathCaseSensitive(const QString& path);

	QIcon icon(const QString& name, bool useCache = true);

public slots:
	void setupWizard();

protected:
	// Startup Sections
	void loadSettings();
	void checkArgs();
	void loadCore();
	void loadPlugins();
	void loadGUI();
	void displayGUI();

	// Startup Mode
	StartupMode mStartupMode;

	Utopia::MetaBase *mMetaBase;

	Logger        *mLogger;
	MainWindow    *mMainWindow;
	GUIManager    *mGUIManager;
	SongManager   *mSongManager;
	DeviceManager *mDeviceManager;
	PluginManager *mPluginManager;
	FileTypeFactory *mFileTypeFactory;

	QDir mSettingsDir;
	SettingsManager *mSettingsManager;

	AudioThread *mAudioThread;

	QStringList mIconSearchPath;
	QMap<QString, QIcon> mIconCache;
};

#define uApp ( reinterpret_cast<Application*>( QApplication::instance() ) )

#define uDebug(component, msg)    ( uApp->logger()->log(0, (component), (msg), __FILE__, __LINE__) )
#define uInfo(component, msg)     ( uApp->logger()->log(1, (component), (msg), __FILE__, __LINE__) )
#define uWarning(component, msg)  ( uApp->logger()->log(2, (component), (msg), __FILE__, __LINE__) )
#define uError(component, msg)    ( uApp->logger()->log(3, (component), (msg), __FILE__, __LINE__) )
#define uCritical(component, msg) ( uApp->logger()->log(4, (component), (msg), __FILE__, __LINE__) )
#define uFatal(component, msg)    ( uApp->logger()->log(5, (component), (msg), __FILE__, __LINE__) )

#endif // __Application_h__
