/*************************************************************************\
*  UtopiaDB - A multimedia database application and library with a clean  *
*  API and lots of features, including multiple languages per entry.      *
*                                                                         *
*  Copyright (C) 2006-2007 John Eric Martin <john.eric.martin@gmail.com>  *
*                                                                         *
*  This program is free software; you can redistribute it and/or modify   *
*  it under the terms of the GNU General Public License version 2 as      *
*  published by the Free Software Foundation.                             *
*                                                                         *
*  This program is distributed in the hope that it will be useful,        *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with this program; if not, write to the                          *
*  Free Software Foundation, Inc.,                                        *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
\*************************************************************************/

/**
 * @file mood.h The Mood block class definition
 */

#ifndef __Mood_h__
#define __Mood_h__

#include <QtCore/QMap>

#include "utopiablock.h"

namespace Utopia
{

class MoodData : public QSharedData
{
public:
	QMap<QString, QString> mMood;
};

class Mood : public UtopiaBlock
{
public:
	Mood();
	Mood(const QMap<QString, QString>& moods);
	Mood(const QString& mood, const QString& lang = CURRENT_LANG);

	bool operator==(const Mood& block);
	bool operator!=(const Mood& block);

	QList<QString> langs() const;
	bool containsLang(const QString& lang = CURRENT_LANG);

	QList<QString> moods() const;
	bool containsMood(const QString& mood);
	QString mood(const QString& lang = CURRENT_LANG) const;

	virtual QStringList type() const { return QStringList() << "Mood" << UtopiaBlock::type(); };

	void add(const QString& mood, const QString& lang = CURRENT_LANG);
	void remove(const QString& mood = "", const QString& lang = CURRENT_LANG);

	virtual void clear();

	virtual QString xml(bool encased = true) const;

private:
	QSharedDataPointer<MoodData> d;
};

class MoodParser : public UtopiaBlockParser
{
public:
	MoodParser() : UtopiaBlockParser() { };

	virtual bool startDocument();
	virtual bool characters(const QString& ch);
};

}; // namespace Utopia

#endif // __Mood_h__
