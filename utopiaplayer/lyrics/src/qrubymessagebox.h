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
 * @file QRubyMessageBox.h The class definition for QRubyMessageBox
 */

#ifndef __QRubyMessageBox_h__
#define __QRubyMessageBox_h__

#include <QtCore/QList>
#include <QtGui/QDialog>
#include <QtGui/QPixmap>

class QLabel;
class QRubyLabel;
class QHBoxLayout;
class QVBoxLayout;

class QRubyMessageBox : public QDialog
{
	Q_OBJECT
	Q_ENUMS(Icon)
	Q_PROPERTY(QString text READ text WRITE setText)
	Q_PROPERTY(Icon icon READ icon WRITE setIcon)
	Q_PROPERTY(QPixmap iconPixmap READ iconPixmap WRITE setIconPixmap)
	Q_PROPERTY(Qt::TextFormat textFormat READ textFormat WRITE setTextFormat)

public:
	enum Icon
	{
		NoIcon = 0,
		Information = 1,
		Warning = 2,
		Critical = 3,
		Question = 4
	};

	enum Button
	{
		NoButton = 0,
		Ok = 1,
		Cancel = 2,
		Yes = 3,
		No = 4,
		Abort = 5,
		Retry = 6,
		Ignore = 7,
		YesAll = 8,
		NoAll = 9,
		ButtonMask = 0xff,
		Default = 0x100,
		Escape = 0x200,
		FlagMask = 0x300
	};

	QRubyMessageBox(QWidget *parent = 0);
	QRubyMessageBox(const QString &caption, const QString &text, Icon icon, int button0, int button1, int button2, QWidget *parent = 0, Qt::WFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	~QRubyMessageBox();

	QString text() const;
	void setText(const QString &);

	Icon icon() const;
	void setIcon(Icon);

	QPixmap iconPixmap() const;
	void setIconPixmap(const QPixmap &);

	QString buttonText(int button) const;
	void setButtonText(int button, const QString &);

	Qt::TextFormat textFormat() const;
	void setTextFormat(Qt::TextFormat);

	static int information(QWidget *parent, const QString &caption, const QString& text, int button0, int button1=0, int button2=0);
	static int information(QWidget *parent, const QString &caption, const QString& text, const QString& button0Text = QString(), const QString& button1Text = QString(), const QString& button2Text = QString(), int defaultButtonNumber = 0, int escapeButtonNumber = -1);

	static int question(QWidget *parent, const QString &caption, const QString& text, int button0, int button1=0, int button2=0);
	static int question(QWidget *parent, const QString &caption, const QString& text, const QString& button0Text = QString(), const QString& button1Text = QString(), const QString& button2Text = QString(), int defaultButtonNumber = 0, int escapeButtonNumber = -1);

	static int warning(QWidget *parent, const QString &caption, const QString& text, int button0, int button1, int button2=0);
	static int warning(QWidget *parent, const QString &caption, const QString& text, const QString& button0Text = QString(), const QString& button1Text = QString(), const QString& button2Text = QString(), int defaultButtonNumber = 0, int escapeButtonNumber = -1);

	static int critical(QWidget *parent, const QString &caption, const QString& text, int button0, int button1, int button2=0);
	static int critical(QWidget *parent, const QString &caption, const QString& text, const QString& button0Text = QString(), const QString& button1Text = QString(), const QString& button2Text = QString(), int defaultButtonNumber = 0, int escapeButtonNumber = -1);

	static void about(QWidget *parent, const QString &caption, const QString& text);

	QSize sizeHint() const;

	static QPixmap standardIcon(Icon icon);

protected slots:
	void buttonClicked();

protected:
	//void resizeEvent(QResizeEvent *event) { };
	//void showEvent(QShowEvent *) { };
	//void closeEvent(QCloseEvent *) { };
	//void keyPressEvent(QKeyEvent *) { };
	//void changeEvent(QEvent *) { };

	int mIconType;
	QLabel* mIcon;

	QRubyLabel* mMessage;

	QVBoxLayout* mDialogLayout;
	QHBoxLayout* mMessageLayout;
	QHBoxLayout* mButtonLayout;

	int mButtonType0;
	QPushButton* mButton0;
	int mButtonType1;
	QPushButton* mButton1;
	int mButtonType2;
	QPushButton* mButton2;
};

#endif // __QRubyMessageBox_h__
