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

/**
 * @file plugin.h The base class defining plugins
 */

#ifndef __Plugin_h__
#define __Plugin_h__

#include <QtCore/QString>
#include <QtCore/QPointer>
#include <QtCore/QStringList>
#include <QtCore/QtPlugin>
#include <QtGui/QWidget>
#include <QtGui/QIcon>

class PluginInterface
{
public:
	virtual ~PluginInterface() { };

	virtual QIcon icon() const { return QIcon(); };
	virtual QString name() const = 0;
	virtual QString version() const = 0;
	virtual QStringList authors() const = 0;
	virtual QString copyrightNotice() const = 0;

	virtual QPointer<QWidget> aboutDialog() const { return 0; };
	virtual bool hasAboutDialog() { return false; };

	virtual QPointer<QWidget> configDialog() const { return 0; };
	virtual bool hasConfigDialog() { return false; };
	
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual bool isLoaded() = 0;
};

Q_DECLARE_INTERFACE(PluginInterface, "com.googlecode.UtopiaPlayer.PluginInterface/0.1")

#endif // __Plugin_h__
