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
#include <QtCore/QtPlugin>

class PluginInterface
{
public:
	PluginInterface() : mLoaded(false) { };
	virtual ~PluginInterface() { };

	virtual QString name() const = 0;
	
	virtual void load() { mLoaded = true; };
	virtual void unload() { mLoaded = false; };
	virtual bool isLoaded() { return mLoaded; };

protected:
	bool mLoaded;
};

Q_DECLARE_INTERFACE(PluginInterface, "com.emotionalcoder.UtopiaPlayer.PluginInterface/0.1")

#endif // __Plugin_h__
