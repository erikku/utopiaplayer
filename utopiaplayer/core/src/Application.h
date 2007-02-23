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

#ifndef __Application_h__
#define __Application_h__

// Qt4 includes
#include <QtCore/QDir>
#include <QtCore/QMap>
#include <QtGui/QApplication>

namespace Utopia
{
	class MetaBase;
};

class QSettings;
class MainWindow;
class SongManager;
class DeviceManager;
class PluginManager;

class AudioThread;

/**
 * @brief This class starts and stops the application.
 */
class Application : public QApplication
{
    Q_OBJECT

public:
	Application(int argc, char *argv[]);
	~Application();

    void Init();

	Utopia::MetaBase* metaBase() const;

	MainWindow* mainWindow() const;
	SongManager* songManager() const;
	DeviceManager* deviceManager() const;
	PluginManager* pluginManager() const;

	QDir settingsDir() const;
	QSettings* settings() const;

	AudioThread* audioThread() const;

	static QStringList listRecursiveDirectoryContents(const QDir& dir, const QStringList& nameFilters = QStringList() << "*", QDir::Filters filters = QDir::Files, QDir::SortFlags sort = QDir::Name);
	static QString makePathCaseSensitive(const QString& path);

	QIcon icon(const QString& name);

public slots:
	void loadPlugins();
	void setupWizard();

protected:
	Utopia::MetaBase *mMetaBase;

	MainWindow    *mMainWindow;
	SongManager   *mSongManager;
	DeviceManager *mDeviceManager;
	PluginManager *mPluginManager;

	QDir mSettingsDir;
	QSettings *mSettings;

	AudioThread *mAudioThread;

	QMap<QString, QIcon> mIconCache;
};

//#define uApp ( reinterpret_cast<Application*>( KApplication::kApplication() ) )
#define uApp ( reinterpret_cast<Application*>( QApplication::instance() ) )

#endif // __Application_h__
