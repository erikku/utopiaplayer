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

#include <QtCore/QProcess>
#include <QtCore/QPluginLoader>
#include <QtGui/QMessageBox>
#include <QtCore/QTextCodec>
#include <QtCore/QDir>
#include <QtGui/QIcon>
#include <QtGui/QFont>
#include <QtGui/QStyleFactory>
#include <iostream>

// UtopiaPlayer includes
#include "UtopiaPlayer.h"

#include "Application.h"

#include <utopiadb/blockparser.h>
#include <utopiadb/xmlmetabase.h>
#include "SongManager.h"
#include "DeviceManager.h"
#include "PluginManager.h"
#include "SettingsManager.h"
#include "GUIManager.h"
#include "AudioThread.h"
#include "Login.h"

#include "VolumePlugin.h"
#include "MainWindow.h"
#include "CurrentSongAdapter.h"
#include <QtDBus/QDBusConnection>

#include "OutputInterface.h"

Application::Application(int argc, char *argv[]) : QApplication(argc, argv)
{
	connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));

	setApplicationName("Utopia Player");
	setOrganizationName("Utopia Player Team");
	setOrganizationDomain("code.google.com");

	mMetaBase = 0;
	mSongManager = 0;
	mDeviceManager = 0;
	mPluginManager = 0;
 	mSettingsManager = 0;
};

QIcon Application::icon(const QString& name, bool useCache)
{
	if(useCache)
		if(mIconCache.contains(name))
			return mIconCache.value(name);

	QIcon nIcon;
	QList<int> sizes;
	sizes << 16 << 22 << 32 << 48 << 64 << 128;

	QString fileName;
	QString searchPath = QDir::cleanPath(mIconSearchPath.first());

	bool foundIcon = false;

	if( QDir(searchPath).exists() )
	{
		foreach(int size, sizes)
		{
			fileName = QDir::cleanPath(searchPath + "/" + QString::number(size) + "x" + QString::number(size) + "/" + name + ".png" );

			if(QFile(fileName).exists())
			{
				nIcon.addFile(fileName, QSize(size, size), QIcon::Normal, QIcon::On);
				foundIcon = true;
			}
		}
	}

	if(!foundIcon)
	{
		for(int i = 1; i < mIconSearchPath.count(); i++)
		{
			searchPath = QDir::cleanPath(mIconSearchPath.at(i) + "/" + "crystalsvg");
			if( !QDir(searchPath).exists() )
				continue;

			foreach(int size, sizes)
			{
				fileName = QDir::cleanPath(searchPath + "/" + QString::number(size) + "x" + QString::number(size) + "/" + name + ".png" );

				if(QFile(fileName).exists())
				{
					nIcon.addFile(fileName, QSize(size, size), QIcon::Normal, QIcon::On);
					i = mIconSearchPath.count();
					foundIcon = true;
				}
			}
		}
	}

	if(!foundIcon)
	{
		if(name == "mimetypes/unknown")
			return QIcon();

		nIcon = icon("mimetypes/unknown");
	}

	if(useCache)
		mIconCache[name] = nIcon;

	return nIcon;
};

Application::~Application()
{
	((XmlMetaBase*)mMetaBase)->toFile( mSettingsDir.absoluteFilePath("utopiadb") );

	delete mMetaBase;
	delete mSongManager;
	delete mDeviceManager;
	delete mPluginManager;
	delete mSettingsManager;

	Utopia::BlockParser::cleanupParsers();
};

void Application::Init(StartupMode mode)
{
	mStartupMode = mode;

	loadSettings();
	checkArgs();
	loadCore();

	if(mStartupMode != Minimal)
	{
		//loadPlugins();
		loadGUI();
		displayGUI();
	}
};

Utopia::MetaBase* Application::metaBase() const
{
	return mMetaBase;
};

MainWindow* Application::mainWindow() const
{
	return mMainWindow;
};

GUIManager* Application::guiManager() const
{
	return mGUIManager;
};

SongManager* Application::songManager() const
{
	return mSongManager;
};

DeviceManager* Application::deviceManager() const
{
	return mDeviceManager;
};

PluginManager* Application::pluginManager() const
{
	return mPluginManager;
};

QDir Application::settingsDir() const
{
	return mSettingsDir;
};

AudioThread* Application::audioThread() const
{
	return mAudioThread;
};

SettingsManager* Application::settingsManager() const
{
	return mSettingsManager;
};

void Application::loadSettings()
{
	mSettingsDir = QDir::home();
#if defined(Q_WS_WIN)
	mSettingsDir.cd("Application Data");
	mSettingsDir.mkdir("Utopia Player");
	mSettingsDir.cd("Utopia Player");
#else
	mSettingsDir.mkdir(".utopiaplayer");
	mSettingsDir.cd(".utopiaplayer");
#endif

	mSettingsManager = new SettingsManager( mSettingsDir.absoluteFilePath("settings.ini") );
};

void Application::checkArgs()
{
	QStringList args = arguments();
	
	if( args.contains("--disable-style") )
	{
		mSettingsManager->setDisableStyle(true);
	}
};

void Application::loadCore()
{
	Utopia::BlockParser::initParsers();
	
	if( !mSettingsManager->disableStyle() )
	{
		QStyle *style = 0;

		style = QStyleFactory::create( mSettingsManager->style() );

		if(style)
			setStyle(style);
			
		if( mSettingsManager->contains("Palettes/Dark") )
		{
			setPalette( mSettingsManager->value("Palettes/Dark").value<QPalette>() );
			/*QPalette palette = mSettingsManager->value("Palettes/Dark").value<QPalette>();
			QByteArray base64Palette;
			{
				QDataStream stream(&base64Palette, QIODevice::WriteOnly);
				stream << palette;
			}
			std::cout << "Size: " << base64Palette.size() << std::endl;
			base64Palette = base64Palette.toBase64();
			std::cout << "Size: " << base64Palette.size() << std::endl;
			QString dark2 = QString::fromAscii(base64Palette.data(), base64Palette.size());
			std::cout << "Palette: " << dark2.toAscii().data() << std::endl;*/
		}
		else
		{
			QPalette palette;
			{
				QString dark2(
				"AQH//wAAwMAAAAAAAQH//zAwMDAwMAAAAQH//wAAAAAAAAAAAQH//zQ0NDQ0NAAAAQH//"
				"2BgYGBgYAAAAQH//0BAQEBAQAAAAQH//wAAwMAAAAAAAQH//wAAwMAAAAAAAQH//wAAwM"
				"AAAAAAAQH//ygoKCgoKAAAAQH//xAQEBAQEAAAAQH//0BAQEBAQAAAAQH//wAAwMAAAAA"
				"AAQH//0BAQEBAQAAAAQH//wAAAADu7gAAAQH//1JSGBiLiwAAAQH//yAgICAgIAAAAQH/"
				"/wAAQEAAAAAAAQH//yAgICAgIAAAAQH//wAAAAAAAAAAAQH//yAgICAgIAAAAQH//yAgI"
				"CAgIAAAAQH//yAgICAgIAAAAQH//wAAQEAAAAAAAQH//wAAYGAAAAAAAQH//wAAQEAAAA"
				"AAAQH//xgYFxcYGAAAAQH//xAQEBAQEAAAAQH//yAgICAgIAAAAQH//wAAQEAAAAAAAQH"
				"//wAAAAAAAAAAAQH//wAAAADu7gAAAQH//1JSGBiLiwAAAQH//xAQEBAQEAAAAQH//wAA"
				"gIAAAAAAAQH//zAwMDAwMAAAAQH//yAgICAgIAAAAQH//zAwMDAwMAAAAQH//0BAQEBAQ"
				"AAAAQH//zAwMDAwMAAAAQH//wAAgIAAAAAAAQH//wAAgIAAAAAAAQH//wAAgIAAAAAAAQ"
				"H//ygoKCgoKAAAAQH//xAQEBAQEAAAAQH//zAwMDAwMAAAAQH//wAAgIAAAAAAAQH//yA"
				"gICAgIAAAAQH//wAAAADu7gAAAQH//1JSGBiLiwAAAQH//yAgICAgIAAA");
				QByteArray newPal = QByteArray::fromBase64(dark2.toAscii());
				QDataStream stream(&newPal, QIODevice::ReadOnly);
				stream >> palette;
			}
			setPalette(palette);
		}
	}

	mMetaBase = Utopia::XmlMetaBase::fromFile( mSettingsDir.absoluteFilePath("utopiadb") );

#if defined(Q_WS_WIN)
	mIconSearchPath << QString(applicationDirPath() + "/icons");
#else
	mIconSearchPath << QString(QString(UTOPIAPLAYER_PREFIX) + "/share/utopiaplayer/icons");
	QProcess kde_config;
	kde_config.start("kde-config", QStringList() << "--path" << "icon");
	if(kde_config.waitForStarted(3000))
	{
		if(kde_config.waitForFinished(5000))
		{
			QStringList newPaths = QString::fromLocal8Bit(kde_config.readAll()).split(":");
			foreach(QString iconPath, newPaths)
			{
				if( QDir( QDir::cleanPath(iconPath.trimmed()) ).exists() )
					mIconSearchPath << QDir::cleanPath( iconPath.trimmed() );
			}
		}
	}
#endif

	if(mStartupMode != Minimal)
	{
		mSongManager = new SongManager;
		mDeviceManager = new DeviceManager;
		mPluginManager = new PluginManager;

		/*
		new CarAdaptor(car);
    	QDBusConnection connection = QDBusConnection::sessionBus();
    	connection.registerObject("/Car", car);
    	connection.registerService("com.trolltech.CarExample");
		*/

		//new CurrentSongAdaptor(this);
		//QDBusConnection::sessionBus().registerObject("/CurrentSong", this);
		//QDBusConnection::sessionBus().registerService("net.emotional-coder.UtopiaPlayer");
	}
};

void Application::loadPlugins()
{
	mDeviceManager->registerPlugin(new VolumePlugin);
	std::cout << "Found Plugin \"Volume\" (Built-In)" << std::endl;

	// Do our static plugins
	foreach(QObject *object, QPluginLoader::staticInstances())
	{
		if( mPluginManager->registerPlugin(object) )
			std::cout << "Found Plugin \"" << qobject_cast<PluginInterface*>(object)->name().toLocal8Bit().data() << "\" (Built-In)" << std::endl;
		else
			QMessageBox::critical(0, applicationName(), tr("Error loading plugin!"));
	}

#if defined(Q_WS_WIN)
	QString pluginDir = applicationDirPath() + QDir::separator() + "plugins";
#else
	QString pluginDir = QString("share") + QDir::separator() + "utopiaplayer" + QDir::separator() + "plugins";
	pluginDir = QString(UTOPIAPLAYER_PREFIX) + QDir::separator() + pluginDir;
#endif

	QStringList pluginFiles = listRecursiveDirectoryContents( QDir(pluginDir) );

	foreach(QString fileName, pluginFiles)
	{
		QPluginLoader loader( QDir::toNativeSeparators(fileName) );
		if( mPluginManager->registerPlugin(loader.instance()) )
			std::cout << "Found Plugin \"" << qobject_cast<PluginInterface*>( loader.instance() )->name().toLocal8Bit().data() << "\"" << std::endl;
		else
			QMessageBox::critical(0, applicationName(), tr("Error loading plugin: %1").arg(loader.errorString()));
	}

	if(mSettingsManager->contains("General/OutputPlugin"))
	{
		mPluginManager->setCurrentOutputPlugin(mSettingsManager->value("General/OutputPlugin").toString());
	}
};

void Application::loadGUI()
{
	setWindowIcon( icon("apps/utopiaplayer") );

	mMainWindow = new MainWindow;
};

void Application::displayGUI()
{
	setupWizard();
	mMainWindow->show();
};

QStringList Application::listRecursiveDirectoryContents(const QDir& dir, const QStringList& nameFilters, QDir::Filters filters, QDir::SortFlags sort)
{
	QStringList subdirs = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, sort);
	QStringList contents = nameFilters.count() < 1 ? dir.entryList(filters, sort) : dir.entryList(nameFilters, filters, sort);

	for(int i = 0; i < contents.count(); i++)
	{
		contents.replace(i, dir.absolutePath() + QDir::separator() + contents.at(i) );
	}

	QDir newDir;

	for(int i = 0; i < subdirs.count(); i++)
	{
		newDir = dir;
		newDir.cd(subdirs.at(i));
		contents << listRecursiveDirectoryContents(newDir, nameFilters, filters, sort);
	}

	return contents;
};

QString Application::makePathCaseSensitive(const QString& path)
{
	QStringList elements = path.split(QDir::separator());
	QStringList newPath;
	QString prefix;

	QStringList contents;
	QMap<QString, QString> pathLookup;

	if(elements.first().isEmpty())
	{
		elements.removeAt(0);
		prefix = QDir::separator();
	}

	for(int i = 0; i < elements.count(); i++)
	{
		pathLookup.clear();

		// Check our current path still exists
		if( !QFile(prefix + newPath.join(QDir::separator())).exists() )
			return QString();

		// Get the contents of our current path and turn them into a lookup map
		contents = QDir(prefix + newPath.join(QDir::separator())).entryList(QDir::AllEntries, QDir::Name);
		foreach(QString chunk, contents)
		{
			pathLookup[chunk.toLower()] = chunk;
		}
		contents.clear();

		// Ensure it found our element in the list
		if(!pathLookup.contains(elements.at(i).toLower()))
			return QString();

		newPath << pathLookup.value(elements.at(i).toLower());
	}

	if( QFile(prefix + newPath.join(QDir::separator())).exists() )
		return prefix + newPath.join(QDir::separator());

	return QString();
};

void Application::setupWizard()
{
	if( mSettingsManager->value("General/LastUsedVersion").toString() != UTOPIAPLAYER_VERSION)
	{
		QString message;
		if(UTOPIAPLAYER_OFFICIAL)
		{
			message = tr("Please note that %1 currently only supports OGG and MP3 audio. MP3 audio <b>DOES</b> work. Please install the proper packages for MP3 support. Contact your distro (not us) for help with this. <b>DO NOT</b> bug us about MP3 support issues.").arg(applicationName());
		}
		else
		{
			message = tr("<b>THIS IS AN UNOFFICIAL VERSION OF %1.</b><br/><br/><b>DO NOT</b> use your main music collection with this version of %2. We <b>WILL NOT BE RESPONSIBLE</b> for any loss of data from using an unofficial release of %2. This includes versions from SVN, betas, release canidates, previews, alphas, and any version with patches (like what package maintainers like to do). <b>DO NOT</b> send us bugs, emails, chat messages, etc. bitching about the fact you <b>IGNORED THIS AND YOUR DATA IS NOW GONE</b>.").arg(applicationName().toUpper()).arg(applicationName());
		}
		QMessageBox::warning(0, tr("New Version Information (Version %1)").arg(QString::fromUtf8(UTOPIAPLAYER_VERSION)), message);

		// Save the new version number
		mSettingsManager->setValue("General/LastUsedVersion", UTOPIAPLAYER_VERSION);
	}
};
