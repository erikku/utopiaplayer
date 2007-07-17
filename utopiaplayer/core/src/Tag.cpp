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

#include "Tag.h"

using namespace MetaData;

QString Tag::fromEncoding(const QString& encoding, const char *str, int size) const
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

QByteArray Tag::toEncoding(const QString& encoding, const QString& str) const
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
