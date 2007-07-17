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

#include "Browser.h"
#include "Application.h"

#include <utopiadb/sqlmetabase.h>

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QTextEdit>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QInputDialog>

#include <iostream>

using namespace Utopia;

Browser::Browser(QWidget *parent) : QMainWindow(parent), mCurrentMetabase(0), mCurrentID(0)
{
	mBlockList = new QTreeWidget;
	mBlockList->setColumnCount(2);
	mBlockList->setHeaderLabels ( QStringList() << tr("ID") << tr("Type") );

	mBlockXmlEdit = new QTextEdit;
	mBlockXmlEdit->setReadOnly(true);
	mBlockRawEdit = new QTextEdit;
	mBlockRawEdit->setReadOnly(true);

	QVBoxLayout *mBlockXmlLayout = new QVBoxLayout;
	mBlockXmlLayout->addWidget(mBlockXmlEdit);

	QVBoxLayout *mBlockRawLayout = new QVBoxLayout;
	mBlockRawLayout->addWidget(mBlockRawEdit);

	QWidget *mBlockXmlTab = new QWidget;
	mBlockXmlTab->setLayout(mBlockXmlLayout);

	QWidget *mBlockRawTab = new QWidget;
	mBlockRawTab->setLayout(mBlockRawLayout);

	mRevSpinner = new QSpinBox;
	QTabWidget *mBlockTabs = new QTabWidget;
	mBlockTabs->addTab(mBlockXmlTab, tr("XML"));
	mBlockTabs->addTab(mBlockRawTab, tr("RAW"));

	QVBoxLayout *mBlockLayout = new QVBoxLayout;
	mBlockLayout->addWidget(mRevSpinner);
	mBlockLayout->addWidget(mBlockTabs);

	QWidget *mBlockWidget = new QWidget;
	mBlockWidget->setLayout(mBlockLayout);

	mMainSplitter = new QSplitter;
	mMainSplitter->addWidget(mBlockList);
	mMainSplitter->addWidget(mBlockWidget);

	setCentralWidget(mMainSplitter);
	mMainSplitter->hide();

	QMenu *mFileMenu = new QMenu( tr("&File") );
	QAction *mFileOpen = mFileMenu->addAction( tr("Open SQLite Database...") );
	connect(mFileOpen, SIGNAL(triggered()), this, SLOT(openSQLite()));

	menuBar()->addMenu(mFileMenu);

	connect(mBlockList, SIGNAL(itemSelectionChanged()), this, SLOT(updateSelection()));
	connect(mRevSpinner, SIGNAL(valueChanged(int)), this, SLOT(updateRev(int)));
};

Browser::~Browser()
{
	mCurrentDatabase.close();
	mCurrentDatabase = QSqlDatabase();

	QStringList connections = QSqlDatabase::connectionNames();
	foreach(QString connection, connections)
		QSqlDatabase::removeDatabase(connection);
};

QSize Browser::sizeHint() const
{
	return QSize(640, 480);
};

void Browser::openSQLite()
{
	QString file = QFileDialog::getOpenFileName(this, tr("Please select the SQLite Database..."));
	if(file.isEmpty())
		return;

	mCurrentDatabase.close();
	mCurrentDatabase = QSqlDatabase();

	delete mCurrentMetabase;
	mCurrentMetabase = 0;
	mBlockList->clear();

	QStringList connections = QSqlDatabase::connectionNames();
	foreach(QString connection, connections)
		QSqlDatabase::removeDatabase(connection);

	mCurrentDatabase = QSqlDatabase::addDatabase("QSQLITE");
	mCurrentDatabase.setDatabaseName(file);
	if( !mCurrentDatabase.open() )
	{
		QMessageBox::critical( 0, tr("Cannot open database"), tr("Unable to establish a database connection.") );
		return;
	}

	mPrefix = QInputDialog::getText(this, tr("Table Prefix"), tr("Please enter in the table prefix for this database"), 
		QLineEdit::Normal, "utopia_");

	QSqlQuery query(mCurrentDatabase);
	query.prepare("SELECT `uid`, `type` FROM " + mPrefix + "blocks");
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return;
	}

	uid id;
	QString type;

	while( query.next() )
	{
		id = query.record().value("uid").toInt();
		type = query.record().value("type").toString();
		mBlockList->addTopLevelItem( new QTreeWidgetItem( QStringList() << QString::number(id) << type ) );
	}

	mCurrentMetabase = new SqlMetaBase(mCurrentDatabase, mPrefix);

	mMainSplitter->show();
};

void Browser::updateSelection()
{
	if(!mBlockList->selectedItems().count())
		return;

	uid id = mBlockList->selectedItems().first()->text(0).toInt();

	mCurrentID = id;

	if(id < 1)
		return;

	QSqlQuery query(mCurrentDatabase);
	query.prepare("SELECT `rev` FROM " + mPrefix + "blocks WHERE `uid` = :uid");
	query.bindValue(":uid", id);
	if( !query.exec() )
	{
		std::cout << query.lastQuery().toLocal8Bit().data() << ": " << query.lastError().driverText().toLocal8Bit().data() << std::endl;
		return;
	}

	int rev = 0;

	if( !query.next() )
		return;

	rev = query.record().value("rev").toInt();

	mRevSpinner->setMinimum(1);
	mRevSpinner->setMaximum(rev);
	mRevSpinner->setValue(rev);
};

void Browser::updateRev(int rev)
{
	if(mCurrentID < 1)
		return;

	// Fetch the XML
	mBlockXmlEdit->clear();
	mBlockXmlEdit->insertPlainText( mCurrentMetabase->patchedBlockData(mCurrentID, rev) );

	// Fetch the RAW
	mBlockRawEdit->clear();
	mBlockRawEdit->insertPlainText( mCurrentMetabase->fetchRevisionData(mCurrentID, rev) );
};
