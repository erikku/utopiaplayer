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

#include "SearchTree.h"
#include "SearchEdit.h"
#include "Application.h"

#include <QtCore/QMimeData>

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>

#include <QtGui/QTreeWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>

class SearchTreeWidget : public QTreeWidget
{
public:
	static QString pathFromItem(QTreeWidgetItem *item, const QString& path = QString())
	{
		if(!item)
			return path;

		QString workingPath = path;

		if(workingPath.isEmpty())
			workingPath = item->text(0);
		else
			workingPath += "/" + item->text(0);

		if(item->parent())
			workingPath = pathFromItem(item->parent()) + "/" + workingPath;
	
		return workingPath;
	};

protected:
	virtual QStringList mimeTypes() const
	{
		QStringList types = QTreeWidget::mimeTypes();
		types << "text/plain";
		
		return types;
	};
	
	virtual QMimeData* mimeData(const QList<QTreeWidgetItem*> items) const
	{
		QMimeData *mimeData = QTreeWidget::mimeData(items);
		QStringList itemPaths;
		QString currentPath;
	
		foreach(QTreeWidgetItem *item, items)
		{
			currentPath = pathFromItem(item);
			if(!currentPath.isEmpty())
				itemPaths << currentPath;
		}
	
		mimeData->setText(itemPaths.join(";"));

		return mimeData;
	};
};

SearchTree::SearchTree(QWidget *parent) : QWidget(parent)
{
	mMainLayout = new QVBoxLayout;
	mSearchLayout = new QHBoxLayout;

	mSearchEdit = new SearchEdit;
	mTreeWidget = new SearchTreeWidget;
	mClearButton = new QToolButton;
	mClearButton->setIcon( uApp->icon("actions/editclear") );
    mClearButton->setToolTip(tr("Clear the search box."));
    mClearButton->adjustSize();

	mSearchLayout->addWidget(mClearButton);
	mSearchLayout->addWidget(mSearchEdit);

	mMainLayout->addLayout(mSearchLayout);
	mMainLayout->addWidget(mTreeWidget);

	setLayout(mMainLayout);

	addItem("Splitters/Vertical Sizer");
	addItem("Panels/Album Info");
	addItem("Splitters/Vertical Splitter");
	addItem("Splitters/Horizontal Sizer");
	addItem("Panels/Track Info");
	addItem("Splitters/Horizontal Splitter");
	addItem("Panels/Album Cover");
	
	// Add/Remove tests
	addItem("Teir 1/Teir 2/Teir 3/Clip Me");
	addItem("Teir 1/Teir 2/Teir 4/Don't Clip Me");
	addItem("Teir 1/Teir 2/Don't Clip Me Either");
	removeItem("Teir 1/Teir 2/Teir 3/Clip Me");

	mTreeWidget->expandAll();
	mTreeWidget->header()->hide();
	
	connect(mClearButton, SIGNAL(clicked(bool)), mSearchEdit, SLOT(clear()));
	connect(mSearchEdit, SIGNAL(textEdited(const QString&)), this, SLOT(filter()));
	mTreeWidget->resizeColumnToContents(0);
	mTreeWidget->setDragEnabled(true);
	mTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
};

SearchTree::~SearchTree()
{
	delete mTreeWidget;
	delete mSearchEdit;
	delete mClearButton;
	delete mSearchLayout;
	delete mMainLayout;
};

void SearchTree::filter()
{
	QString search = mSearchEdit->text();
	QTreeWidgetItem *item = 0;

	if( search.isEmpty() )
	{
		for(int i = 0; i < mTreeWidget->topLevelItemCount(); i++)
		{
			item = mTreeWidget->topLevelItem(i);
			if(!item)
				continue;

			showItems(item);
		}
	}
	else
	{
		for(int i = 0; i < mTreeWidget->topLevelItemCount(); i++)
		{
			item = mTreeWidget->topLevelItem(i);
			if(!item)
				continue;

			filterItems(item, search);
		}
		
		mTreeWidget->keyboardSearch( QString() );
		mTreeWidget->clearSelection();
		mTreeWidget->keyboardSearch(search);
	}

	mTreeWidget->resizeColumnToContents(0);
};

void SearchTree::showItems(QTreeWidgetItem *item)
{
	QTreeWidgetItem *child = 0;
	item->setHidden(false);
	
	for(int i = 0; i < item->childCount(); i++)
	{
		child = item->child(i);
		if(!child)
			continue;

		showItems(child);
	}
};

bool SearchTree::filterItems(QTreeWidgetItem *item, const QString& search)
{
	bool result; // true if we need to hide the item, false if we show the item

	if(item->childCount())
	{
		// If the search matches a item with children, show that item and all it's children
		result = !item->text(0).contains(search, Qt::CaseInsensitive);
		if(!result)
		{
			showItems(item);
			return result;
		}
		
		result = true;
		QTreeWidgetItem *child = 0;
		
		// Check each child (and their children) to see if we should show or hide them.
		for(int i = 0; i < item->childCount(); i++)
		{
			child = item->child(i);
			if(!child)
				continue;

			result &= filterItems(child, search);
		}
	}
	else
	{
		// If the item has no children and it matches, show it, otherwise hide it.
		result = !item->text(0).contains(search, Qt::CaseInsensitive);
	}
	
	item->setHidden(result);
	return result;
};

void SearchTree::addItem(const QString& path)
{
	if(path.isEmpty())
		return;

	QTreeWidgetItem *item = 0;
	QStringList pathComponents = path.split("/");
	QString current = pathComponents.takeFirst();

	for(int i = 0; i < mTreeWidget->topLevelItemCount(); i++)
	{
		item = mTreeWidget->topLevelItem(i);
		if(!item)
			continue;

		if( item->text(0) == current ) // We found the item
		{
			break;
		}
		else if( item->text(0).compare(current, Qt::CaseInsensitive) > 0 ) // We passed where the item would be, so let's add it
		{
			item = new QTreeWidgetItem(QStringList() << current);
			mTreeWidget->insertTopLevelItem(i, item);
			break;
		}
		
		item = 0;
	}
	
	if(!item) // We never passed the item or found a exact match, so let's add it to the end of the list
	{
		item = new QTreeWidgetItem(QStringList() << current);
		mTreeWidget->addTopLevelItem(item);
	}
	
	if(pathComponents.count())
		recursiveAdd(item, pathComponents);

	filter();
};

void SearchTree::recursiveAdd(QTreeWidgetItem *item, const QStringList& path)
{
	QTreeWidgetItem *child = 0;
	QStringList pathComponents = path;
	QString current = pathComponents.takeFirst();

	for(int i = 0; i < item->childCount(); i++)
	{
		child = item->child(i);
		if(!child)
			continue;

		if( child->text(0) == current ) // We found the item
		{
			break;
		}
		else if( child->text(0).compare(current, Qt::CaseInsensitive) > 0 ) // We passed where the item would be, so let's add it
		{
			child = new QTreeWidgetItem(QStringList() << current);
			item->insertChild(i, child);
			break;
		}
		
		child = 0;
	}
	
	if(!child) // We never passed the item or found a exact match, so let's add it to the end of the list
	{
		child = new QTreeWidgetItem(QStringList() << current);
		item->addChild(child);
	}

	if(pathComponents.count())
		recursiveAdd(child, pathComponents);
};

QTreeWidgetItem* SearchTree::itemFromPath(const QString& path)
{
	if(path.isEmpty())
		return 0;

	QTreeWidgetItem *item = 0;
	QStringList pathComponents = path.split("/");
	QString current = pathComponents.takeFirst();

	for(int i = 0; i < mTreeWidget->topLevelItemCount(); i++)
	{
		item = mTreeWidget->topLevelItem(i);
		if(!item)
			continue;

		if(item->text(0) == current)
		{
			if(pathComponents.count())
				return crawlDown(item, pathComponents);
			else
				return item;
		}
	}

	return 0;
};

void SearchTree::removeItem(const QString& path)
{
	if(path.isEmpty())
		return;

	removeItem( itemFromPath(path) );
	mTreeWidget->resizeColumnToContents(0);
}

void SearchTree::removeItem(QTreeWidgetItem *item)
{
	if(!item)
		return;

	QTreeWidgetItem *parent = item->parent();
	if(parent) // We have a parent, so we need to crawl up the tree cleaning empty nodes.
	{
		for(int i = 0; i < parent->childCount(); i++)
		{
			if(parent->child(i) == item)
			{
				parent->takeChild(i);
				break;
			}
		}
		
		if(parent->childCount() == 0) // We have no children, so let's remove the parent
			removeItem(parent);
	}
	else // It has no parent so it must be a top level item.
	{
		for(int i = 0; i < mTreeWidget->topLevelItemCount(); i++)
		{
			if(mTreeWidget->topLevelItem(i) == item)
			{
				mTreeWidget->takeTopLevelItem(i);
				break;
			}
		}
	}
};

QTreeWidgetItem* SearchTree::crawlDown(QTreeWidgetItem *item, const QStringList& path)
{
	QTreeWidgetItem *child = 0;
	QStringList pathComponents = path;
	QString current = pathComponents.takeFirst();

	for(int i = 0; i < item->childCount(); i++)
	{
		child = item->child(i);
		if(!child)
			continue;

		if(child->text(0) == current)
		{
			if(pathComponents.count())
				return crawlDown(child, pathComponents);
			else
				return child;
		}
	}

	return 0;
};

QString SearchTree::pathFromItem(QTreeWidgetItem *item, const QString& path) const
{
	return SearchTreeWidget::pathFromItem(item, path);
};

void SearchTree::addItems(const QStringList& paths)
{
	foreach(QString path, paths)
		addItem(path);
};

void SearchTree::removeItems(const QStringList& paths)
{
	foreach(QString path, paths)
		removeItem(path);
};

void SearchTree::removeItems(const QList<QTreeWidgetItem*>& items)
{
	foreach(QTreeWidgetItem *item, items)
		removeItem(item);
};
