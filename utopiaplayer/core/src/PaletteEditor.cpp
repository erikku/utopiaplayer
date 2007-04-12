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

#include "PaletteEditor.h"
#include "Application.h"

#include <QtCore/QtDebug>
#include <QtCore/QSettings>

PaletteEditor::PaletteEditor()
{
	ui.setupUi(this);

	QVariant variant = mPalette;

	QSettings settings;
	if( settings.contains("Palettes/Dark") )
	{
		mPalette = settings.value("Palettes/Dark").value<QPalette>();
	}
	else
	{
		mPalette = uApp->style()->standardPalette();
	}

	mColorGroups["Disabled"] = QPalette::Disabled;
	mColorGroups["Active"] = QPalette::Active;
	mColorGroups["Inactive"] = QPalette::Inactive;
	mColorGroups["Normal"] = QPalette::Normal;

	mColorRoles["Window"] = QPalette::Window;
	mColorRoles["Window Text"] = QPalette::WindowText;
	mColorRoles["Base"] = QPalette::Base;
	mColorRoles["Alternate Base"] = QPalette::AlternateBase;
	mColorRoles["Text"] = QPalette::Text;
	mColorRoles["Button"] = QPalette::Button;
	mColorRoles["Button Text"] = QPalette::ButtonText;
	mColorRoles["Bright Text"] = QPalette::BrightText;
	mColorRoles["Light"] = QPalette::Light;
	mColorRoles["Medium Light"] = QPalette::Midlight;
	mColorRoles["Dark"] = QPalette::Dark;
	mColorRoles["Medium"] = QPalette::Mid;
	mColorRoles["Shadow"] = QPalette::Shadow;
	mColorRoles["Highlight"] = QPalette::Highlight;
	mColorRoles["Highlighted Text"] = QPalette::HighlightedText;
	mColorRoles["Link"] = QPalette::Link;
	mColorRoles["Link Visited"] = QPalette::LinkVisited;

	mBrushStyles["None"] = Qt::NoBrush;
	mBrushStyles["Solid"] = Qt::SolidPattern;
	mBrushStyles["Dense 1"] = Qt::Dense1Pattern;
	mBrushStyles["Dense 2"] = Qt::Dense2Pattern;
	mBrushStyles["Dense 3"] = Qt::Dense3Pattern;
	mBrushStyles["Dense 4"] = Qt::Dense4Pattern;
	mBrushStyles["Dense 5"] = Qt::Dense5Pattern;
	mBrushStyles["Dense 6"] = Qt::Dense6Pattern;
	mBrushStyles["Dense 7"] = Qt::Dense7Pattern;
	mBrushStyles["Horizontal"] = Qt::HorPattern;
	mBrushStyles["Vertical"] = Qt::VerPattern;
	mBrushStyles["Cross"] = Qt::CrossPattern;
	mBrushStyles["Backward Diagonal"] = Qt::BDiagPattern;
	mBrushStyles["Forward Diagonal"] = Qt::FDiagPattern;
	mBrushStyles["Diagonal Cross"] = Qt::DiagCrossPattern;
	mBrushStyles["Linear Gradient"] = Qt::LinearGradientPattern;
	mBrushStyles["Conical Gradient"] = Qt::ConicalGradientPattern;
	mBrushStyles["Radial Gradient"] = Qt::RadialGradientPattern;
	mBrushStyles["Texture Pattern"] = Qt::TexturePattern;

	mGradType["Linear"] = QGradient::LinearGradient;
	mGradType["Radial"] = QGradient::RadialGradient;
	mGradType["Conical"] = QGradient::ConicalGradient;
	mGradType["None"] = QGradient::NoGradient;
	mGradSpread["Pad"] = QGradient::PadSpread;
	mGradSpread["Repeat"] = QGradient::RepeatSpread;
	mGradSpread["Reflect"] = QGradient::ReflectSpread;

	mDescriptions[QPalette::Window] = "A general background color.";
	mDescriptions[QPalette::WindowText] = "A general foreground color.";
	mDescriptions[QPalette::Base] = "Used as the background color for text entry widgets; usually white or another light color.";
	mDescriptions[QPalette::AlternateBase] = "Used as the alternate background color in views with alternating row colors (see QAbstractItemView::setAlternatingRowColors()).";
	mDescriptions[QPalette::Text] = "The foreground color used with Base. This is usually the same as the WindowText, in which case it must provide good contrast with Window and Base.";
	mDescriptions[QPalette::Button] = "The general button background color. This background can be different from Window as some styles require a different background color for buttons.";
	mDescriptions[QPalette::ButtonText] = "A foreground color used with the Button color.";
	mDescriptions[QPalette::BrightText] = "A text color that is very different from WindowText, and contrasts well with e.g. Dark. Typically used for text that needs to be drawn where Text or WindowText would give poor contrast, such as on pressed push buttons. Note that text colors can be used for things other than just words; text colors are usually used for text, but it's quite common to use the text color roles for lines, icons, etc.";
	mDescriptions[QPalette::Light] = "Lighter than Button color.";
	mDescriptions[QPalette::Midlight] = "Between Button and Light.";
	mDescriptions[QPalette::Dark] = "Darker than Button.";
	mDescriptions[QPalette::Mid] = "Between Button and Dark.";
	mDescriptions[QPalette::Shadow] = "A very dark color. By default, the shadow color is Qt::black.";
	mDescriptions[QPalette::Highlight] = "A color to indicate a selected item or the current item. By default, the highlight color is Qt::darkBlue.";
	mDescriptions[QPalette::HighlightedText] = "A text color that contrasts with Highlight. By default, the highlighted text color is Qt::white.";
	mDescriptions[QPalette::Link] = "A text color used for unvisited hyperlinks. By default, the link color is Qt::blue.";
	mDescriptions[QPalette::LinkVisited] = "A text color used for already visited hyperlinks. By default, the linkvisited color is Qt::magenta.";

	ui.RoleCombo->insertItems( 0, mColorRoles.keys() );
	ui.GroupCombo->insertItems( 0, mColorGroups.keys() );

	updateColor();
	updatePalette();

	connect(ui.RoleCombo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(updateColor()));
	connect(ui.GroupCombo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(updateColor()));

	connect(ui.RBox, SIGNAL(valueChanged(int)), this, SLOT(updatePalette()));
	connect(ui.GBox, SIGNAL(valueChanged(int)), this, SLOT(updatePalette()));
	connect(ui.BBox, SIGNAL(valueChanged(int)), this, SLOT(updatePalette()));

	connect(ui.ButtonBox, SIGNAL(accepted()), this, SLOT(save()));

	setWindowTitle(tr("Palette Editor - %1").arg("Dark"));
};

QString PaletteEditor::exportPalette(const QPalette& pal) const
{
	QString xml;
	QBrush brush;
	const QGradient *grad;
	QGradientStops stops;

	xml += "<palette>\n";
	foreach(QString role, mColorRoles.keys())
	{
		xml += "  <role name=\"" + role + "\">\n";
		foreach(QString group, mColorGroups.keys())
		{
			brush = pal.brush(mColorGroups.value(group), mColorRoles.value(role));
			if(brush.style() == Qt::TexturePattern)
			{
				qWarning() << QString("Ignoring brush for ") + group + " - " + role + " because it is a texture!";
				xml += "    <brush group=\"" + group + "\"/>\n";
				continue;
			}
			if(brush.style() == Qt::NoBrush)
			{
				xml += "    <brush group=\"" + group + "\"/>\n";
				continue;
			}

			xml += "    <brush group=\"" + group + "\" style=\"" + mBrushStyles.key(brush.style()) + "\">\n";
			if(brush.style() == Qt::LinearGradientPattern || brush.style() == Qt::ConicalGradientPattern ||
				brush.style() == Qt::RadialGradientPattern)
			{
				grad = brush.gradient();
				if(grad->type() == QGradient::NoGradient)
				{
					xml += "      <gradient/>\n";
				}
				else
				{
					xml += "      <gradient type=\"" + mGradType.key(grad->type()) + "\" spread=\"" + mGradSpread.key(grad->spread()) + "\"/>\n";
					stops = grad->stops();
					for(int i = 0; i < stops.size(); ++i)
					{
						xml += "      <stop pos=\"" + QString::number(stops.at(i).first) + "\" color=\"" + stops.at(i).second.name() + "\"/>\n";
					}
					xml += "      </gradient>\n";
				}
			}
			else
			{
				xml += "      <color>" + brush.color().name() + "</color>\n";
			}
			xml += "    </brush>\n";
		}
		xml += "  </role>\n";
	}
	xml += "</palette>\n";

	return xml;
};

void PaletteEditor::save()
{
	QVariant variant = mPalette;

	QSettings settings;
	settings.setValue("Palettes/Dark", variant);
};

void PaletteEditor::updateColor()
{
	QPalette::ColorRole cr = mColorRoles.value( ui.RoleCombo->currentText() );
	QPalette::ColorGroup gr = mColorGroups.value( ui.GroupCombo->currentText() );

	QBrush brush = mPalette.brush(gr, cr);
	QColor color = brush.color();

	ui.RBox->setValue(color.red());
	ui.GBox->setValue(color.green());
	ui.BBox->setValue(color.blue());

	QPixmap pix(24, 24);
	pix.fill(color);
	ui.ColorButton->setIcon( QIcon(pix) );

	ui.Description->setText( mDescriptions.value(cr) );
};

void PaletteEditor::updatePalette()
{
	QPalette::ColorRole cr = mColorRoles.value( ui.RoleCombo->currentText() );
	QPalette::ColorGroup gr = mColorGroups.value( ui.GroupCombo->currentText() );

	QBrush brush = mPalette.brush(gr, cr);
	QColor color = QColor( ui.RBox->value(), ui.GBox->value(), ui.BBox->value() );

	brush.setColor(color);
	mPalette.setBrush(gr, cr, brush);

	QPixmap pix(24, 24);
	pix.fill(color);
	ui.ColorButton->setIcon( QIcon(pix) );

	ui.PreviewBox->setPalette(mPalette);
	ui.PreviewBox->repaint();
};
