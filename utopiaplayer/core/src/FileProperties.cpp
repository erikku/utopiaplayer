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

#include "FileProperties.h"
#include "AdvancedTag.h"
#include "AudioFile.h"

#include <QtGui/QHBoxLayout>
#include "TagEditBasic.h"

FileProperties::FileProperties(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
};

FileProperties::FileProperties(AudioFile *file, QWidget *parent)
{
	ui.setupUi(this);
	populate(file);
};

void FileProperties::populate(AudioFile *file)
{
	if( !file->isValid() )
		return;

	bool open = file->isOpen();

	if(!open)
	{
		if( !file->load() )
			return;
	}

	setWindowTitle( tr("File Properties - %1").arg(file->name()) );
	ui.Name->setText( file->name() );
	ui.Path->setText( file->path() );
	ui.Size->setText( sizeToString( file->size() ) );
	ui.Created->setText( file->created().toString() );
	ui.Modified->setText( file->modified().toString() );

	ui.Duration->setText( secondsToString( file->length() ) );
	ui.SampleRate->setText( tr("%1 Hz").arg( file->sampleRate() ) );
	ui.Channels->setText( tr("%1 channels").arg( file->channels() ) );
	ui.BitsPerSample->setText( tr("%1 bits").arg( file->bitsPerSample() ) );
	if( file->bitrate() )
		ui.Bitrate->setText( QString::number( file->bitrate() ) + " kbps" );
	else
		ui.Bitrate->setText( tr("N/A") );
	ui.Codec->setText( file->codec() );
	ui.Tool->setText( file->tool() );
	ui.Encoding->setText( file->encoding() );

	foreach(MetaData::Tag *tag, file->tags())
	{
		if(tag->hasAdvancedFeatures())
			populateTag( (MetaData::AdvancedTag*)tag );
		else
			populateTag(tag);
	}

	if(open)
		file->close();
};

void FileProperties::populateTag(MetaData::Tag *tag)
{
	QWidget *tab = new QWidget;
	QHBoxLayout *layout = new QHBoxLayout;
	TagEditBasic *basic = new TagEditBasic(tag);

	layout->addWidget(basic);
	tab->setLayout(layout);

	ui.PropertiesTabWidget->addTab(tab, tag->type());
};

void FileProperties::populateTag(MetaData::AdvancedTag *tag)
{
	populateTag( (MetaData::Tag*)tag );
};

QString FileProperties::sizeToString(quint64 size) const
{
	QStringList sizeCounters = QString("B,KB,MB,GB,TB").split(",");

	int counter = 0;
	float nSize = size;

	while(nSize > 1024)
	{
		counter++;
		nSize /= 1024.0f;
	}

	if(counter)
		return QString::number(nSize, 'g', 4) + " " + sizeCounters.at(counter);

	return QString::number(nSize, 'g', 4) + " " + sizeCounters.first();
};

QString FileProperties::secondsToString(quint32 seconds) const
{
	int days = 0, hours = 0, minutes = 0;
	int remaining = seconds;

	// Days
	if(remaining >= 86400)
	{
		days = ( remaining - (remaining % 86400) ) / 86400;
		remaining = remaining % 86400;
	}

	// Hours
	if(remaining >= 3600)
	{
		hours = ( remaining - (remaining % 3600) ) / 3600;
		remaining = remaining % 3600;
	}

	// Minutes
	if(remaining >= 60)
	{
		minutes = ( remaining - (remaining % 60) ) / 60;
		remaining = remaining % 60;
	}

	if(days)
		return tr("%1 Days %2:%3:%4").arg(days).arg( QString::number(hours).rightJustified(2, '0') ).arg( QString::number(minutes).rightJustified(2, '0') ).arg( QString::number(remaining).rightJustified(2, '0') );
	else if(hours)
		return tr("%1:%2:%3").arg( QString::number(hours).rightJustified(2, '0') ).arg( QString::number(minutes).rightJustified(2, '0') ).arg( QString::number(remaining).rightJustified(2, '0') );

	return tr("%1:%2").arg( QString::number(minutes).rightJustified(2, '0') ).arg( QString::number(remaining).rightJustified(2, '0') );
};
