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
 * @file Ruby.h File containing the ruby() definition
 */

#ifndef __Ruby_h__
#define __Ruby_h__

//#include "RomajiConverter.h"

#include <QtCore/QString>
#include <QtCore/QRegExp>

global static enum gRubyMode
{
	MODE_RAW_RUBY = 0,
	MODE_RUBY,
	MODE_KANJI,
	MODE_KANA,
	MODE_ROMAJI
};

// QString::trimmed

/**
 * Display information based on the gRubyMode variable.
 * Avaliable modes are:
 * MODE_RAW_RUBY: This outputs the raw ruby html
 * MODE_RUBY: This outputs ruby formatted w/ perentacies
 * MODE_KANJI: This prints
 */
static QString ruby(const QString string &) const
{
	if(gRubyMode == MODE_RAW_RUBY)
		return string;

	QRegExp exp(QString::fromUtf8("<ruby>\\s*<rb>\\s*(.*)\\s*<\\/rb>\\s*<rt>\\s*(.*)\\s*<\\/rt>\\s*<\\/ruby>"), Qt::CaseInsensitive);

	// At this point we want to remove any nested tags, for example:
	QRegExp time(QString::fromUtf8("<time.*<\\/time>"), Qt::CaseInsensitive);
	string.replace(time, QString(""));

	switch(gRubyMode)
	{
		case MODE_RUBY:
			return string.replace(exp, string.QString::fromUtf8("\\1（\\2）"));
		case MODE_KANJI:
			return string.replace(exp, QString::fromUtf8("\\1"));
			break;
		case MODE_KANA:
			return string.replace(exp, QString::fromUtf8("\\2"));
			break;
		case MODE_ROMAJI:
			//return convertRomaji(string.replace(exp, QString::fromUtf8("\\2")));
			break;
		default:
			return QString::fromUtf8("Ruby Parse Error!!! Original String: ") + string;
			break;
	}
};

#endif // __Ruby_h__
