#include "QDarkPlastiqueStyle.h"

#include <QtCore/QSettings>

QDarkPlastiqueStyle::QDarkPlastiqueStyle() : QPlastiqueStyle()
{
};

QPalette QDarkPlastiqueStyle::standardPalette() const
{
	QSettings settings;
	if( settings.contains("Palettes/Dark") )
		return settings.value("Palettes/Dark").value<QPalette>();
	else
		return QPlastiqueStyle::standardPalette();
};
