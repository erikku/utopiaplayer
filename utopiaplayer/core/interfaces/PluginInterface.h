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

/**
 * @file plugin.h The base class defining plugins
 */

#ifndef __Plugin_h__
#define __Plugin_h__

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QtPlugin>

typedef enum _PluginType
{
	OutputPlugin,
	DevicePlugin,
	MediaSourcePlugin,
	ImportExportPlugin
}PluginType;

class PluginInterface : public QObject
{
	Q_OBJECT

public:
	PluginInterface(QObject *parent = 0, const QStringList& args = QStringList()) : QObject(parent), mLoaded(false) { Q_UNUSED(args) };
	virtual ~PluginInterface() {};

	virtual bool isLoaded() { return mLoaded; };

	virtual QString    pluginName() const = 0;
	virtual PluginType pluginType() = 0;

public slots:
	virtual void load() { mLoaded = true; };
	virtual void unload() { mLoaded = false; };

protected:
	bool mLoaded;
};

#endif // __Plugin_h__
