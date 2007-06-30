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

#include "ID3v1.h"

using namespace MetaData;

#include <QtCore/QFile>

#include <cstdio>
#include <cstdlib>
#include <cstring>

static char* GenreList[] = {
	"Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge",
	"Hip-Hop", "Jazz", "Metal", "New Age", "Oldies", "Other", "Pop", "R&B",
	"Rap", "Reggae", "Rock", "Techno", "Industrial", "Alternative", "Ska",
	"Death Metal", "Pranks", "Soundtrack", "Euro-Techno", "Ambient",
	"Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical",
	"Instrumental", "Acid", "House", "Game", "Sound Clip", "Gospel", "Noise",
	"AlternRock", "Bass", "Soul", "Punk", "Space", "Meditative",
	"Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic", "Darkwave",
	"Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance", "Dream",
	"Southern Rock", "Comedy", "Cult", "Gangsta", "Top 40", "Christian Rap",
	"Pop/Funk", "Jungle", "Native American", "Cabaret", "New Wave",
	"Psychadelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal",
	"Acid Punk", "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll",
	"Hard Rock", "Folk", "Folk-Rock", "National Folk", "Swing", "Fast Fusion",
	"Bebob", "Latin", "Revival", "Celtic", "Bluegrass", "Avantgarde",
	"Gothic Rock", "Progressive Rock", "Psychedelic Rock", "Symphonic Rock",
	"Slow Rock", "Big Band", "Chorus", "Easy Listening", "Acoustic", "Humour",
	"Speech", "Chanson", "Opera", "Chamber Music", "Sonata", "Symphony",
	"Booty Bass", "Primus", "Porn Groove", "Satire", "Slow Jam", "Club",
	"Tango", "Samba", "Folklore", "Ballad", "Power Ballad", "Rhythmic Soul",
	"Freestyle", "Duet", "Punk Rock", "Drum Solo", "A capella", "Euro-House",
	"Dance Hall"
};

ID3v1::ID3v1()
{
	mCurrentEncoding = defaultEncoding();
	d = (ID3v1Data*)calloc(1, 128);
	memcpy(d->Magic, "TAG", 3);
};

ID3v1::ID3v1(const ID3v1& other)
{
	mCurrentEncoding = defaultEncoding();
	memcpy(d, other.d, 128);
};

ID3v1::ID3v1(const QString& path)
{
	mCurrentEncoding = defaultEncoding();
	d = (ID3v1Data*)calloc(1, 128);
	memcpy(d->Magic, "TAG", 3);
	read(path);
};

ID3v1::~ID3v1()
{
	free(d);
};

QString ID3v1::title() const
{
	return mTitle;
};

QString ID3v1::artist() const
{
	return mArtist;
};

QString ID3v1::album() const
{
	return mAlbum;
};

QString ID3v1::comment() const
{
	return mComment;
};

QString ID3v1::genre() const
{
	if(d->Genre >= 126)
		return QString();

	return QString(GenreList[d->Genre]);
};

int ID3v1::year() const
{
	return QString::fromAscii(d->Year, 4).toInt();
};

int ID3v1::track() const
{
	return d->Track;
};

void ID3v1::setTitle(const QString& title)
{
	mTitle = title;
};

void ID3v1::setArtist(const QString& artist)
{
	mArtist = artist;
};

void ID3v1::setAlbum(const QString& album)
{
	mAlbum = album;
};

void ID3v1::setComment(const QString& comment)
{
	mComment = comment;
};

void ID3v1::setGenre(const QString& genre)
{
	for(int i = 0; i < 126; i++)
	{
		if(genre == GenreList[i])
		{
			d->Genre = i;
			return;
		}
	}

	d->Genre = 255;
};

void ID3v1::setYear(int year)
{
	if(year > 9999 || year < 0)
		return;

	QString nYear = QString::number(year).rightJustified(4, '0');
	memcpy(d->Year, nYear.toAscii().data(), 4);
};

void ID3v1::setTrack(int track)
{
	d->Track = track;
};

void ID3v1::clear()
{
	free(d);

	mCurrentEncoding = defaultEncoding();
	d = (ID3v1Data*)calloc(1, 128);
	memcpy(d->Magic, "TAG", 3);
};

bool ID3v1::isEmpty()
{
	if(d->Title[0] == 0x0 && d->Artist[0] == 0x0 && d->Album[0] == 0 && d->Comment[0] == 0x0 && d->Year == 0 && d->Track == 0 && d->Genre == 0)
		return true;

	return false;
};

QString ID3v1::encoding() const
{
	return mCurrentEncoding;
};

QString ID3v1::defaultEncoding() const
{
	return "ISO-8859-1";
};

Tag* ID3v1::duplicate()
{
	ID3v1 *tag = new ID3v1;
	tag->mCurrentEncoding = mCurrentEncoding;
	memcpy(tag->d, d, 128);
};

qint64 ID3v1::size()
{
	return 128;
};

QByteArray ID3v1::tagData() const
{
	return QByteArray( (const char*)d, 128 );
};

void ID3v1::removeTag(const QString& path)
{
	if( !containsTag(path) )
		return;

	QFile file(path);

	// Open the file for writing
	if(!file.open(QIODevice::WriteOnly))
		return;

	file.seek(0);
	file.resize( file.size() - 128 );
	file.close();
};

qint64 ID3v1::position(const QString& path)
{
	if( !containsTag(path) )
		return -1;

	QFile file(path);

	return file.size() - 128;
};

bool ID3v1::containsTag(const QString& path)
{
	QFile file(path);

	// Open the file for reading
	if(!file.open(QIODevice::ReadOnly))
		return false;

	// Make sure the file is big enough to hold a ID3v1 tag
	if(file.size() < 128)
	{
		file.close();
		return false;
	}

	// Seek to the right place in the file
	file.seek(file.size() - 128);

	// Allocate the tag
	ID3v1Data *tag = new ID3v1Data;

	// Read the tag
	file.read((char*)tag, 128);

	// Check if the data is really a ID3v1 tag
	if( strcmp(tag->Magic, "TAG") != 0)
	{
		file.close();
		free(tag);
		return false;
	}

	file.close();
	free(tag);
	return true;
};

bool ID3v1::conformsToSpec(const QString& path)
{
	if( containsTag(path) )
		return true;

	return false;
};

bool ID3v1::read(const QString& path, const QString& encoding)
{
	if( !encoding.isEmpty() )
		mCurrentEncoding = encoding;
/*"English (ISO-8859-1)"
"Japanese (EUC-JP)"
"Japanese (SJIS)"
"Unicode (UTF-8)"*/
	QFile file(path);

	// Open the file for reading
	if(!file.open(QIODevice::ReadOnly))
		return false;

	// Make sure the file is big enough to hold a ID3v1 tag
	if(file.size() < 128)
	{
		file.close();
		return false;
	}

	// Seek to the right place in the file
	file.seek(file.size() - 128);

	// Read the tag
	file.read((char*)d, 128);

	// Check if the data is really a ID3v1 tag
	if(memcmp(d->Magic, "TAG", 3) != 0)
	{
		file.close();
		free(d);

		d = (ID3v1Data*)calloc(1, 128);
		memcpy(d->Magic, "TAG", 3);

		return false;
	}

	d->Comment[28] = 0x00; // Convert a ID3v1 to a ID3v1.1

	file.close();

	// Read in the tags from the buffer
	mTitle = fromEncoding(mCurrentEncoding, d->Title);
	mArtist = fromEncoding(mCurrentEncoding, d->Artist);
	mAlbum = fromEncoding(mCurrentEncoding, d->Album);
	mComment = fromEncoding(mCurrentEncoding, d->Comment);

	return true;
};

bool ID3v1::write(const QString& path, const QString& encoding)
{
	if( !encoding.isEmpty() )
		mCurrentEncoding = encoding;

	// Write the data to the buffer
	writeString(d->Title, mTitle, 30);
	writeString(d->Artist, mArtist, 30);
	writeString(d->Album, mAlbum, 30);
	writeString(d->Comment, mComment, 29);

	QFile file(path);

	// Open the file for reading and writing
	if(!file.open(QIODevice::ReadWrite | QIODevice::Append))
		return false;

	qint64 offset = file.size();

	// Make sure the file is big enough to hold a ID3v1 tag
	if(file.size() >= 128)
	{
		char magic[3];

		// Seek to the right place in the file
		file.seek(file.size() - 128);

		// Read the magic
		file.read((char*)&magic, 128);

		// If we have a tag already, adjust the offset
		if( strcmp(magic, "TAG") == 0 )
			offset -= 128;
	}

	// Seek to the position to write the tag at
	file.seek(offset);

	// Write the tag
	file.write((char*)d, 128);

	file.close();

	return true;
};

QString ID3v1::type() const
{
	return "ID3v1";
};

void ID3v1::writeString(void *dest, const QString& src, int size)
{
	char *buffer = (char*)calloc(1, size);
	QByteArray data = toEncoding(mCurrentEncoding, src);
	memcpy(buffer, data.data(), (data.size() < size) ? data.size() : (size - 1));
	memcpy(dest, buffer, size);
	free(buffer);
};

QString ID3v1::fromEncoding(const QString& encoding, const char *str, int size) const
{
	// Open the conversion descriptor
	iconv_t conversionDescriptor = iconv_open("UTF-8", encoding.toLatin1().data());

	// See if the conversion descriptor opened properly
	if(conversionDescriptor == (iconv_t) -1)
		return QString();

	// Calculate our buffer size
	int bufferSize = ( (size < 0) ? strlen(str) : size ) * 4;

    // Allocate and zero a buffer for the text.
    char *buffer = (char*)calloc(1, bufferSize);

	/*
	 * We first copy the 'str' and 'buffer' pointers because we have to
	 * pass a reference to the pointer instead of a copy of it anf iconv
	 * modifies the pointers. Using a throw away copy prevents the pointer
	 * from pointing to somewhere other than the beginning of the string.
	 */
	char *strCopy = (char*)str;
	char *bufferCopy = buffer;

	// The iconv conversion counters
	size_t inSize = (size < 0) ? strlen(str) : size;
	size_t outSize = bufferSize;

	// Convert the string
	#ifdef WIN32
	int ret = iconv(conversionDescriptor, (const char **)&strCopy, &inSize, &bufferCopy, &outSize);
	#else
	int ret = iconv(conversionDescriptor, &strCopy, &inSize, &bufferCopy, &outSize);
	#endif

	QString final;

	// Handle iconv errors
    if(ret != (size_t) -1)
		final = QString::fromUtf8(buffer);

	// Free the buffer
	free(buffer);

	// Close the conversion descriptor
    iconv_close(conversionDescriptor);

    // Return the cnverted string
    return final;
};

QByteArray ID3v1::toEncoding(const QString& encoding, const QString& str) const
{
	// Open the conversion descriptor
	iconv_t conversionDescriptor = iconv_open(encoding.toLatin1().data(), "UTF-8");

	// See if the conversion descriptor opened properly
	if(conversionDescriptor == (iconv_t) -1)
		return QByteArray();

	// Create a byte array from the string
	QByteArray str_buf(str.toUtf8().data(), str.toUtf8().size());

	// Calculate our buffer size
	int bufferSize = str_buf.size() * 4;

    // Allocate and zero a buffer for the text.
    char *buffer = (char*)calloc(1, bufferSize);

	/*
	 * We first copy the 'str' and 'buffer' pointers because we have to
	 * pass a reference to the pointer instead of a copy of it anf iconv
	 * modifies the pointers. Using a throw away copy prevents the pointer
	 * from pointing to somewhere other than the beginning of the string.
	 */
	char *strCopy = str_buf.data();
	char *bufferCopy = buffer;

	// The iconv conversion counters
	size_t inSize = str.toUtf8().size();
	size_t outSize = bufferSize;

	// Convert the string
	#ifdef WIN32
	int ret = iconv(conversionDescriptor, (const char **)&strCopy, &inSize, &bufferCopy, &outSize);
	#else
	int ret = iconv(conversionDescriptor, &strCopy, &inSize, &bufferCopy, &outSize);
	#endif

	QByteArray final;

	// Handle iconv errors
    if(ret != (size_t) -1)
		final.append(buffer);

	// Free the buffer
	free(buffer);

	// Close the conversion descriptor
    iconv_close(conversionDescriptor);

    // Return the cnverted string
    return final;
};
