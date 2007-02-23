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
 * @file DatabaseList.cpp Implementation of the DatabaseList class.
 */

#include "DatabaseList.h"

#include <QtCore/QSettings>
#include <QtCore/QSignalMapper>
#include <QtGui/QAction>
#include <QtGui/QHeaderView>
#include <QtSql/QSqlRelationalDelegate>

/**
 * @brief Creates a QTableView to display and handle the list of songs.
 * DatabaseList is inhirited from QSqlTable and sets uses a QSqlRelationalTableModel
 * to display the table in the current working database. DatabaseList also provides
 * various slots and signals to hook into the parent window. See bellow for more
 * information on how this class works.
 * @param parent The parent QWidget object that this instance of DatabaseList belongs to.
 */
DatabaseList::DatabaseList(QWidget *parent) : QTableView(parent)
{
	// Create the mDatabaseModel
	mDatabaseModel = new QSqlRelationalTableModel();

	// Set some options
	mDatabaseModel->setEditStrategy(QSqlTableModel::OnFieldChange);

	// Set header data
	//mDatabaseModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

	// Set some default options for the QTableView (DatabaseList)
	setSelectionMode(QAbstractItemView::SingleSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setModel(mDatabaseModel);
	verticalHeader()->hide();
	horizontalHeader()->setHighlightSections(false);

	setShowGrid(false);
	setAlternatingRowColors(true);
};

void DatabaseList::saveSettings()
{
	QSettings settings;

	// Loop through all the columns
	for(int i = 0; i < mDatabaseModel->columnCount(); i++)
	{
		// Save the value to the setting files for each column size
		settings.setValue(objectName() + "/ColumnSize" + QString::number(i), columnWidth(i));
	}
};

void DatabaseList::restoreSettings()
{
	QSettings settings;

	// Loop through all the columns
	for(int i = 0; i < mDatabaseModel->columnCount(); i++)
	{
		// If the key is in the settings, restore the value
		if( (horizontalHeader()->visualIndex(i) != -1) && (settings.contains(objectName() + "/ColumnSize" + QString::number(i))) )
			setColumnWidth(i, settings.value(objectName() + "/ColumnSize" + QString::number(i)).toInt());
	}
};

/**
 * @brief Refreshes the contents of the view model from the database.
 * You should connect other dialogs and windows to this slot so that when they update
 * the database with new information, the changes get reflected in the DatabaseList widget.
 */
void DatabaseList::refreshTable()
{
	mDatabaseModel->select();
};

/**
 * @brief Clears the contents of the view model.
 * You should call this slot once before the application shuts down.
 */
void DatabaseList::clearTable()
{
	mDatabaseModel->clear();
};

/**
 * @brief Adds a menu item to the header context menu.
 * The column named field gets added to the header context menu so that you can toggle
 * the visibility of that column.
 * @param field The name of the column to register
 * @return A pointer to the generated QAction, for example, you can add it to the main menu.
 */
QAction* DatabaseList::registerHeaderField(const QString fieldName, const QString newFieldName)
{
	QAction* header = NULL;
	QString field;

	// Loop through the columns looking for the one we want.
	for(int i = 0; i < mDatabaseModel->columnCount(); i++)
	{
		if(mDatabaseModel->headerData(i, Qt::Horizontal).toString() == fieldName)
		{
			// If we have a newFieldName, use it, otherwise use the default one.
			if(newFieldName.isEmpty())
			{
				field = fieldName;
			}
			else
			{
				field = newFieldName;
				mDatabaseModel->setHeaderData(i, Qt::Horizontal, QVariant(field));
			}

			// Create our action
			header = new QAction(field, horizontalHeader());
			//header->setShortcut(tr("Ctrl+" + QString::number(i)));
			header->setToolTip(tr("Hide the column named ") + field);
			header->setCheckable(true);
			header->setChecked(true);

			// Connect our action to the toggleColumn slot
			connect(header, SIGNAL(triggered()), this, SLOT(toggleColumn()));

			// Add the action to the header
			horizontalHeader()->addAction(header);
		}
	}

	return header;
};

/**
 * @brief Toggles the visibility of the column on or off.
 * If a signal is sent, the column name is derived from QAction::text(). Because of this,
 * You can only connect signals from a QAction to this slot.
 * @param column The name of the column to toggle
 */
void DatabaseList::toggleColumn(const QString column)
{
	QSettings settings;
	QAction* actionUsed = (QAction*)sender();
	QString columnName = column;

	// If we recieved a signal, find the column name from the sender
	if(actionUsed != 0)
		columnName = actionUsed->text();

	// Loop through the columns looking for the one we want
	for(int i = 0; i < mDatabaseModel->columnCount(); i++)
	{
		if(mDatabaseModel->headerData(i, Qt::Horizontal).toString() == columnName)
		{
			// Toggle the visibility of the column
			if(isColumnHidden(i))
			{
				setColumnWidth(i, settings.value("SongView/ColumnSize" + QString::number(i)).toInt());
				showColumn(i);
			}
			else
			{
				settings.setValue("SongView/ColumnSize" + QString::number(i), columnWidth(i));
				hideColumn(i);
			}
		}
	}
};
