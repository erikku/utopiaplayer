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

#ifndef __BackgroundProcess_h__
#define __BackgroundProcess_h__

#include <QtCore/QString>

class QLabel;
class QWidget;

class BackgroundProcess
{
public:
	BackgroundProcess(bool hasProgress = false, bool canCancel = false) : mMin(0), mMax(100), mProgress(0), mFinished(false), mHasProgress(hasProgress), mCanCancel(canCancel)
{
	mProgressWidget = new ProgressWidget;
	mStatusLabel = la;
};

	virtual void start() = 0;
	virtual void update() = 0;
	virtual void stop() = 0;

	virtual void cancel() { };

	QWidget* progressWidget() const { return mProgressWidget; };

	QString statusText() const { if(!mStatusLabel) return QString(); return mStatusLabel->text(); };

	bool isFinished() { return mFinished; };
	bool canCancel() { return mCanCancel; };
	bool hasProgress() { return mHasProgress; };

	int progressMin() { return mMin; };
	int progressVal() { return mProgress; };
	int progressMax() { return mMax; };

protected:
	QLabel *mStatusLabel;
	QWidget *mProgressWidget;

	bool mFinished;
	bool mCanCancel;
	bool mHasProgress;

	int mMin, mMax;
	int mProgress;
};

#endif // __BackgroundProcess_h__
