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

#ifndef __SettingsManager_h__
#define __SettingsManager_h__

#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QSettings>

class SettingsManager
{
public:
	SettingsManager(const QString& settingsFile);
	~SettingsManager();
	
	QString style() const;
	void setStyle(const QString& style);
	
	bool disableStyle();
	void setDisableStyle(bool val);

	QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
	void setValue(const QString& key, const QVariant& value);

	bool contains(const QString& key) const;

protected:
	QSettings *mSettings;
	
	bool mDisableStyle;
};

#endif // __SettingsManager_h__
