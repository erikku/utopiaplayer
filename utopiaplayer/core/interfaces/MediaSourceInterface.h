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

#ifndef __MediaSourceInterface_h__
#define __MediaSourceInterface_h__

#include "Node.h"
#include "PluginInterface.h"

#include <QtCore/QUrl>

class MediaSourceInterface : public Node, PluginInterface
{
	Q_OBJECT

public:
	MediaSourceInterface(QObject *parent = 0, const QStringList& args = QStringList()) : Node(0, 1), PluginInterface(parent, args) { };
	~MediaSourceInterface() { };

	QUrl url() const;

	virtual NodeType type() = { return Source; };

public slots:
	virtual void setURL(const QUrl& url) { mCurrentURL = url; };

protected:
	QUrl mCurrentURL;
};

#endif // __MediaSourceInterface_h__
