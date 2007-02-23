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

#ifndef __iPodNotes_h__
#define __iPodNotes_h__

#include <QtGui/QWidget>
#include <QtGui/QTabWidget>

class QLabel;
class QTextEdit;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QTreeWidgetItem;

class iPodNotes : public QWidget
{
	Q_OBJECT

public:
	iPodNotes(QWidget *parent = 0);

	bool changed() const;

	QString title() const;
	QString currentFilePath() const;

	QTreeWidgetItem *treeItem();

public slots:
	void capacity();
	void updateTitle();
	void load(const QString& file_path);
	void save(const QString& file_path = QString());

	void setTreeItem(QTreeWidgetItem *item);

protected:
	QString mOriginalTitle;
	QString mOriginalContents;

	int mTabIndex;
	QString mFilePath;
	QLabel *mCapacity;
	QTextEdit *mTextEdit;
	QLineEdit *mTitleEdit;
	QTreeWidgetItem *mTreeItem;
};

#endif // __iPodNotes_h__
