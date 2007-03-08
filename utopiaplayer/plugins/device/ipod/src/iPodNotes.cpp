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

#include "iPodNotes.h"
#include "Application.h"
#include "MainWindow.h"

#include <QtCore/QFile>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QMessageBox>
#include <QtGui/QTreeWidgetItem>

iPodNotes::iPodNotes(QWidget *parent) : QWidget(parent), mTreeItem(0), mTabIndex(-1)
{
	QVBoxLayout *mainLayout = new QVBoxLayout;

	QHBoxLayout *titleLayout = new QHBoxLayout;
	titleLayout->addWidget(new QLabel( tr("Title:") ));
	mTitleEdit = new QLineEdit;
	mTitleEdit->setText( tr("Untitled") );
	titleLayout->addWidget(mTitleEdit);
	mCapacity = new QLabel( tr("Capacity: 0/4096") );
	titleLayout->addWidget( mCapacity );
	mainLayout->addLayout(titleLayout);

	mTextEdit = new QTextEdit;
	mTextEdit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
	mTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mainLayout->addWidget(mTextEdit);

	setLayout(mainLayout);

	connect(mTextEdit, SIGNAL(textChanged()), this, SLOT(capacity()));
	connect(mTitleEdit, SIGNAL(textChanged(const QString&)), this, SLOT(updateTitle()));
};

QString iPodNotes::currentFilePath() const
{
	return mFilePath;
};

bool iPodNotes::changed() const
{
	if( mOriginalTitle != mTitleEdit->text() || mOriginalContents != mTextEdit->toPlainText() )
		return true;

	return false;
};

void iPodNotes::load(const QString& file_path)
{
	mFilePath = file_path;

	QFile in(mFilePath);
	if(in.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString line = QString::fromUtf8( in.readLine().data() );

		QRegExp encodingHeader("^\\s*<\\?xml encoding=\\\".*\\\"\\?>\\s*$");
		if(encodingHeader.exactMatch(line))
			line = QString::fromUtf8( in.readLine().data() );

		QRegExp cheapHeader("^\\s*<title>(.*)</title>\\s*$");
		if(cheapHeader.exactMatch(line))
		{
			mTitleEdit->setText(cheapHeader.cap(1));
			line.clear();
		}

		while(!in.atEnd())
		{
			line += QString::fromUtf8( in.readLine().data() );
		}

		mTextEdit->setPlainText(line);

		in.close();
	}

	mOriginalTitle = mTitleEdit->text();
	mOriginalContents = mTextEdit->toPlainText();
};

void iPodNotes::capacity()
{
	int space = tr("<?xml encoding=\"UTF-8\"?>\n<title>%1</title>\n%2").arg(mTitleEdit->text()).arg(mTextEdit->toPlainText()).toUtf8().count();

	QPalette palette = this->palette();
	QBrush brush = palette.brush(mCapacity->foregroundRole());
	if(space > 4096)
		brush.setColor( QColor(Qt::red) );
	palette.setBrush(mCapacity->foregroundRole(), brush);
	mCapacity->setPalette(palette);

	mCapacity->setText( tr("Capacity: %1/4096").arg(space) );
};

QString iPodNotes::title() const
{
	return mTitleEdit->text();
};

void iPodNotes::save(const QString& file_path)
{
	if(!file_path.isEmpty())
		mFilePath = file_path;

	QFile in(mFilePath);
	if(in.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QByteArray data = tr("<?xml encoding=\"UTF-8\"?>\n<title>%1</title>\n%2").arg(mTitleEdit->text()).arg(mTextEdit->toPlainText()).toUtf8();

		if( data.count() != in.write( data ) )
			QMessageBox::critical(0, uApp->applicationName(), tr("Error writing to file: <i>%1</i>").arg(mFilePath));

		in.close();
	}
	else
	{
		QMessageBox::critical(0, uApp->applicationName(), tr("Error opening file for writing: <i>%1</i>").arg(mFilePath));
	}
};

void iPodNotes::setTreeItem(QTreeWidgetItem *item)
{
	mTreeItem = item;
};

QTreeWidgetItem* iPodNotes::treeItem()
{
	return mTreeItem;
};

void iPodNotes::updateTitle()
{
	QTabWidget *widget = uApp->mainWindow()->tabWidget();
	widget->setTabText( widget->indexOf(this), tr("Notes [%1]").arg(mTitleEdit->text()) );

	if(mTreeItem)
	{
		mTreeItem->setText( 0, mTitleEdit->text() );
	}

	capacity();
};
