#ifndef __PaletteEditor_h__
#define __PaletteEditor_h__

#include "ui_PaletteEditor.h"

#include <QtGui/QPalette>

class PaletteEditor : public QWidget
{
	Q_OBJECT

public:
	PaletteEditor();

protected slots:
	void save();
	void updateColor();
	void updatePalette();

protected:
	QPalette mPalette;
	Ui::PaletteEditor ui;

	QMap<QString, QPalette::ColorRole>  mColorRoles;
	QMap<QString, QPalette::ColorGroup> mColorGroups;
	QMap<QPalette::ColorRole, QString>  mDescriptions;
};

#endif // __PaletteEditor_h__
