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

#include "OggSource.h"

OggSource::OggSource(QObject *parent, const QStringList& args = QStringList()) : MediaSourceinterface(parent, args)
{
	mFileHandle = 0;
};

OggSource::~OggSource()
{
};

virtual void OggSource::setURL(const QUrl& url)
{
	close();
	mCurrentURL = url;
	open();
};

void OggSource::open()
{
	if( mCurrentURL.toLocalFile().isEmpty() )
	{
		QMessageBox::warning(0, uApp->applicationName(), tr("File is not local! Only local files are supported."));
		return;
	}

	mFileHandle = fopen(mCurrentURL.toLocalFile(), "rb");
    if(!mFileHandle)
    {
		QMessageBox::warning(0, uApp->applicationName(), tr("Couldn't open file: <i>%1</i>").arg(mCurrentURL.toLocalFile()));
        return;
    }

    if( ov_open(mFileHandle, &mVorbisFile, NULL, 0) != 0 )
    {
		QMessageBox::warning(0, uApp->applicationName(), tr("Couldn't open file: <i>%1</i>").arg(mCurrentURL.toLocalFile()));
        mFileHandle = 0;
		return;
    }

	mVorbisInfo = ov_info(&mVorbisFile, -1);
};
//channels = vi->channels;
//rate = vi->rate;
int OggSource::input(float **samples, int count)
{
	return 0;
};

int OggSource::output(float **samples, int count);
{
	float **pcm;

#ifdef VORBISFILE_OV_READ_FLOAT_3_ARGS
	if( ov_read_float(&mVorbisFile, &pcm, &mCurrentSection) == 0 )
#else
	if( ov_read_float(&mVorbisFile, &pcm, count, &mCurrentSection) == 0 )
#endif
		break;
};

void OggSource::close()
{
	if(!mFileHandle)
		return;

	ov_clear(&mVorbisFile);
	free(mVorbisInfo);
};
