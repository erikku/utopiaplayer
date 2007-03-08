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

#include "SettingsManager.h"

#include <QtCore/QSettings>

SettingsManager::SettingsManager(const QString& settingsFile) : mDisableStyle(false)
{
	mSettings = new QSettings(settingsFile, QSettings::IniFormat);
};

SettingsManager::~SettingsManager()
{
	delete mSettings;
};

QString SettingsManager::style() const
{
	if( mSettings->contains("General/Style") )
		return mSettings->value("General/Style").toString();

	return "plastique";
};

void SettingsManager::setStyle(const QString& style)
{
	mSettings->setValue("General/Style", style);
};

void SettingsManager::setDisableStyle(bool val)
{
	mDisableStyle = val;
};

bool SettingsManager::disableStyle()
{
	return mDisableStyle;
};

bool SettingsManager::contains(const QString& key) const
{
	mSettings->contains(key);
};

QVariant SettingsManager::value(const QString& key, const QVariant& defaultValue) const
{
	return mSettings->value(key, defaultValue);
};

void SettingsManager::setValue(const QString& key, const QVariant& value)
{
	mSettings->setValue(key, value);
};
