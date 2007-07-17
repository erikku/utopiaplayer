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
 * @file DatabaseList.h Definition of the DatabaseList class.
 */

#ifndef __DatabaseList_h__
#define __DatabaseList_h__

#include <QtCore/QString>
#include <QtGui/QTableView>
#include <QtSql/QSqlRelationalTableModel>

/**
 * @brief Creates a QTableView to display and handle the list of songs.
 * DatabaseList creates a QSqlRelationalTableModel class and uses it as it's table model
 * (DatabaseList is inherited from QTavleView).
 */
class DatabaseList : public QTableView
{
	Q_OBJECT

public:
	DatabaseList(QWidget *parent = 0);

	int rowCount() { return mDatabaseModel->rowCount(); };

signals:

public slots:
	void saveSettings();
	void restoreSettings();

	void refreshTable();
	void clearTable();

	void toggleColumn(const QString = QString(""));

protected:
	QAction* registerHeaderField(const QString, const QString = QString(""));

	/// Contains a pointer to the datanase model.
	QSqlRelationalTableModel *mDatabaseModel;
};

#endif // __DatabaseList_h__
