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

#include <QtCore/QPluginLoader>
#include <QtGui/QMessageBox>
#include <QtCore/QTextCodec>
#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtGui/QIcon>
#include <QtGui/QFont>
#include <iostream>

// UtopiaPlayer includes
#include "UtopiaPlayer.h"

#include "Application.h"

#include <utopiadb/blockparser.h>
#include <utopiadb/xmlmetabase.h>
#include "SongManager.h"
#include "DeviceManager.h"
#include "PluginManager.h"
#include "AudioThread.h"
#include "Login.h"

#include "VolumePlugin.h"
#include "MainWindow.h"
#include "CurrentSongAdapter.h"
#include <QtDBus/QDBusConnection>

#include "OutputInterface.h"

Application::Application(int argc, char *argv[]) : QApplication(argc, argv), mPluginManager(0)
{
	Utopia::BlockParser::initParsers();

	mSettingsDir = QDir::home();
#if defined(Q_WS_WIN)
	mSettingsDir.cd("Application Data");
	mSettingsDir.mkdir("Utopia Player");
	mSettingsDir.cd("Utopia Player");
#else
	mSettingsDir.mkdir(".utopiaplayer");
	mSettingsDir.cd(".utopiaplayer");
#endif

	mSettings = new QSettings(mSettingsDir.absoluteFilePath("settings.ini"), QSettings::IniFormat);

	mMetaBase = Utopia::XmlMetaBase::fromFile( mSettingsDir.absoluteFilePath("utopiadb") );
	mSongManager = new SongManager;
	mDeviceManager = new DeviceManager;
	mPluginManager = new PluginManager;

	//mAudioThread = new AudioThread;
	//mAudioThread->start();

	connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));

	setOrganizationName( tr("Emotional Coder") );
	setOrganizationDomain( tr("www.emotionalcoder.net") );
	setApplicationName( tr("Utopia Player") );

	if( mSettings->contains("Palettes/Dark") )
		setPalette( mSettings->value("Palettes/Dark").value<QPalette>() );
	else
		setPalette( style()->standardPalette() );

	setupWizard();

	/*
	new CarAdaptor(car);
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/Car", car);
    connection.registerService("com.trolltech.CarExample");
	*/

	new CurrentSongAdaptor(this);
	QDBusConnection::sessionBus().registerObject("/CurrentSong", this);
	QDBusConnection::sessionBus().registerService("net.emotional-coder.UtopiaPlayer");
};

QIcon Application::icon(const QString& name)
{
	if(mIconCache.contains(name))
		return mIconCache.value(name);

	QIcon nIcon;
	QList<int> sizes;
	sizes << 16 << 22 << 32 << 48 << 64 << 128;

	foreach(int size, sizes)
	{
		QString fileName = QString("%1/%2/%3x%4/%5.png").arg(UTOPIAPLAYER_PREFIX).arg("share/utopiaplayer/icons").arg(size).arg(size).arg(name);
		if(QFile(fileName).exists())
			nIcon.addFile(fileName, QSize(size, size), QIcon::Normal, QIcon::On);
	}

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
	delete mSettings;

	Utopia::BlockParser::cleanupParsers();
};

void Application::Init()
{
	// Set the look of the Qt widgets
	//setStyle("Plastique");
	//setFont(QFont("Kochi Mincho", 11));

	setWindowIcon(QIcon(":/16x16/juk.png"));
	//setWindowIcon(KIcon("utopiaplayer"));

	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
	//new Login();

	mMainWindow = new MainWindow;

	loadPlugins();

	mMainWindow->show();
};

Utopia::MetaBase* Application::metaBase() const
{
	return mMetaBase;
};

MainWindow* Application::mainWindow() const
{
	return mMainWindow;
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

QSettings* Application::settings() const
{
	return mSettings;
};

AudioThread* Application::audioThread() const
{
	return mAudioThread;
};

void Application::loadPlugins()
{
	mDeviceManager->registerPlugin(new VolumePlugin);

	PluginInterface *plugin;

	// Do our static plugins
	foreach(QObject *object, QPluginLoader::staticInstances())
	{
		plugin = qobject_cast<PluginInterface*>(object);
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
		QPluginLoader loader(fileName);
		plugin = qobject_cast<PluginInterface*>( loader.instance() );
		if(plugin)
		{
			switch(plugin->pluginType())
			{
				case OutputPlugin:
					mPluginManager->addOutputPlugin( qobject_cast<OutputInterface*>(plugin) );
					break;
				case DevicePlugin:
					mDeviceManager->registerPlugin( qobject_cast<DeviceInterface*>(plugin) );
					break;
				default:
					QMessageBox::critical(0, applicationName(), tr("Error loading plugin <i>%1</i>: Unknown plugin type!").arg(plugin->pluginName()));
					break;
			}
			std::cout << "Added plugin" << qobject_cast<PluginInterface*>(plugin)->pluginName().toLocal8Bit().data() << std::endl;
		}
		else
		{
			QMessageBox::critical(0, applicationName(), tr("Error loading plugin: %1").arg(loader.errorString()));
		}
	}

	if(mSettings->contains("General/OutputPlugin"))
	{
		mPluginManager->setCurrentOutputPlugin(mSettings->value("General/OutputPlugin").toString());
	}
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
	if( mSettings->value("General/LastUsedVersion").toString() != UTOPIAPLAYER_VERSION)
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
		mSettings->setValue("General/LastUsedVersion", UTOPIAPLAYER_VERSION);
	}
};
