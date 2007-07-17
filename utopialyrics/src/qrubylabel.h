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
 * @file QRubyLabel.h The class definition for QRubyLabel
 * @todo Add setAlignment, see Qt::Alignment, QSpacerItem
 * @toto Add setTextColor and setRubyColor, see QPalette::ColorRole, QPalette::setColor, and QWidget::setPalette
 * @todo Add setBackgroundColor, see above
 * @todo Make it work good with QTableWidget, adding size hints/minimums, a border style (for when selected) and some way to edit it, we also need tooltips/statustips (this should be more like a subclass).
 */

#ifndef __QRubyLabel_h__
#define __QRubyLabel_h__

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QFont>
#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>

/**
 * @brief The QRubyLabel class provides a QLabel capable of displaying ruby text
 *
 */
class QRubyLabel : public QWidget
{
	Q_OBJECT

public:
	QRubyLabel(QWidget *parent = 0);
	QRubyLabel(const QString&, QWidget* = 0);
	QRubyLabel(const QStringList&, QWidget* = 0);

	QFont textFont() const;
	QFont rubyFont() const;

	QString text() const;

	int margin() const;
	int spacing() const;
	
	Qt::TextFormat textFormat() const;

public slots:
	void clear();

	void setTextFont(const QFont&);
	void setRubyFont(const QFont&);

	void setText(const QString&);
	void appendText(const QString&);

	void setText(const QStringList&);
	void appendText(const QStringList&);

	void setMargin(int);
	void setSpacing(int);
	
	void setTextFormat(Qt::TextFormat);

protected:
	QGridLayout *labelGrid;
	QHBoxLayout *labelLayout;
	QSpacerItem *topSpacer;
	QSpacerItem *leftSpacer;
	QSpacerItem *rightSpacer;
	QSpacerItem *bottomSpacer;

	QList<QVBoxLayout*> itemLayouts;
	QList<QLabel*> textWidgets;
	QList<QLabel*> rubyWidgets;

	QFont mTextFont;
	QFont mRubyFont;
	
	Qt::TextFormat mTextFormat;
	
	void insertText(const QString&, const QColor& color = QColor("#000000"));
	void insertRuby(const QString&, const QColor& color = QColor("#000000"));

	void init();
};

#endif // __QRubyLabel_h__
