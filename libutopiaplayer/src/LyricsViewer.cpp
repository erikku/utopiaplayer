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

#include "LyricsViewer.h"

struct font_data {
	float h;										// Holds The Height Of The Font.
	GLuint * textures;									// Holds The Texture Id's 
	GLuint list_base;									// Holds The First Display List Id

	// The Init Function Will Create A Font With
	// The Height h From The File fname.
	void init(const char * fname, unsigned int h);

	// Free All The Resources Associated With The Font.
        void clean();
};

inline int nextPowerOf2(int a)
{
	int rval = 1; 
	while(rval < a) rval *= 2;
	return rval;
};

// Create A Display List Corresponding To The Given Character.
void make_dlist(FT_Face face, char ch, GLuint list_base, GLuint * tex_base)
{

	// The First Thing We Do Is Get FreeType To Render Our Character
	// Into A Bitmap.  This Actually Requires A Couple Of FreeType Commands:

	// Load The Glyph For Our Character.
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT ))
		throw std::runtime_error("FT_Load_Glyph failed");

	// Move The Face's Glyph Into A Glyph Object.
	FT_Glyph glyph;
	if(FT_Get_Glyph( face->glyph, &glyph ))
		throw std::runtime_error("FT_Get_Glyph failed");

	// Convert The Glyph To A Bitmap.
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	// This Reference Will Make Accessing The Bitmap Easier.
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;

LyricsViewer::LyricsViewer(QWidget *parent) : QGLWidget(parent), face(0)
{
	// OMG! Where is the code?!
};

LyricsViewer::~LyricsViewer()
{
	makeCurrent();
};

QSize LyricsViewer::minimumSizeHint() const
{
	return QSize(50, 50);
};

QSize LyricsViewer::sizeHint() const
{
	return QSize(400, 400);
};

void LyricsViewer::initializeGL()
{
	qglClearColor(Qt::black);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	if(FT_Init_FreeType( &library ))
		uError("LyricsViewer", tr("OMG!E&*(@4@ It didn't start!!!"));

	switch(FT_New_Face(library, "/usr/share/fonts/truetype/sazanami/sazanami-mincho.ttf", 0, &face))
	{
		case 0: // Everything is OK
			break;
		case FT_Err_Unknown_File_Format:
			uError("LyricsViewer", tr("Unknow file format!"));
		default:
			uError("LyricsViewer", tr("Error opening font!"));
	}

	if(FT_Set_Pixel_Sizes(face, 0, 32))
		uError("LyricsViewer", tr("Error setting font size!"));
};

void LyricsViewer::loadText(const QString& text)
{
	QChar *ptrText = text.unicode();

	for(int i = 0; ptrText[0] != 0; i++)
	{
		FT_UInt glyph_index = FT_Get_Char_Index(face, ptrText[i]->unicode());
		if(FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT))
			throw std::runtime_error("Error loading glyph!");

		// Move The Face's Glyph Into A Glyph Object.
		FT_Glyph glyph;
		if(FT_Get_Glyph(face->glyph, &glyph))
			throw std::runtime_error("FT_Get_Glyph failed");

		// Convert The Glyph To A Bitmap.
		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		// This Reference Will Make Accessing The Bitmap Easier.
		FT_Bitmap& bitmap=bitmap_glyph->bitmap;

		// Use Our Helper Function To Get The Widths Of
		// The Bitmap Data That We Will Need In Order To Create
		// Our Texture.
		int width  = nextPowerOf2(bitmap.width);
		int height = nextPowerOf2(bitmap.rows);

		// Allocate Memory For The Texture Data.
		GLubyte* expanded_data = new GLubyte[ 2 * width * height];

		// Here We Fill In The Data For The Expanded Bitmap.
		// Notice That We Are Using A Two Channel Bitmap (One For
		// Channel Luminosity And One For Alpha), But We Assign
		// Both Luminosity And Alpha To The Value That We
		// Find In The FreeType Bitmap. 
		// We Use The ?: Operator To Say That Value Which We Use
		// Will Be 0 If We Are In The Padding Zone, And Whatever
		// Is The FreeType Bitmap Otherwise.
		for(int j = 0; j < height; j++)
		{
			for(int i = 0; i < width; i++)
			{
				expanded_data[2 * (i + j * width)]= expanded_data[2 * (i + j * width) + 1] = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
			}
		}

		// Now We Just Setup Some Texture Parameters.
		glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Here We Actually Create The Texture Itself, Notice
		// That We Are Using GL_LUMINANCE_ALPHA To Indicate That
		// We Are Using 2 Channel Data.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);

		// With The Texture Created, We Don't Need The Expanded Data Anymore.
		delete[] expanded_data;
	}
};

void LyricsViewer::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -10.0);
	glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
	glCallList(object);
};

void LyricsViewer::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
};

void LyricsViewer::mousePressEvent(QMouseEvent *event)
{
	// OMG! Where is the code?!
};

void LyricsViewer::mouseMoveEvent(QMouseEvent *event)
{
	// OMG! Where is the code?!
};
