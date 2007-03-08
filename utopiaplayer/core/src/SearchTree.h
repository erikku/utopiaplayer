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

#ifndef __SearchTree_h__
#define __SearchTree_h__

#include <QtGui/QWidget>

class QHBoxLayout;
class QVBoxLayout;

class SearchEdit;

class QMimeData;
class QToolButton;
class QTreeWidget;
class QTreeWidgetItem;

class SearchTree : public QWidget
{
	Q_OBJECT

public:
	SearchTree(QWidget *parent = 0);
	~SearchTree();

	QTreeWidgetItem* itemFromPath(const QString& path);
	QString pathFromItem(QTreeWidgetItem *item, const QString& path = QString()) const;

public slots:
	void filter();
	void addItem(const QString& path);
	void addItems(const QStringList& paths);
	void removeItem(const QString& path);
	void removeItem(QTreeWidgetItem *item);
	void removeItems(const QStringList& paths);
	void removeItems(const QList<QTreeWidgetItem*>& items);

protected:
	QTreeWidgetItem* crawlDown(QTreeWidgetItem *item, const QStringList& path);

	void recursiveAdd(QTreeWidgetItem *item, const QStringList& path);
	void showItems(QTreeWidgetItem *item);
	bool filterItems(QTreeWidgetItem *item, const QString& search);

	QVBoxLayout *mMainLayout;
	QHBoxLayout *mSearchLayout;
	
	SearchEdit *mSearchEdit;
	QTreeWidget *mTreeWidget;
	QToolButton *mClearButton;
};

#endif // __SearchTree_h__
