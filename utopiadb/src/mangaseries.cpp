/*************************************************************************\
*  UtopiaDB - A multimedia database application and library with a clean  *
*  API and lots of features, including multiple languages per entry.      *
*                                                                         *
*  Copyright (C) 2006-2007 John Eric Martin <john.eric.martin@gmail.com>  *
*                                                                         *
*  This program is free software; you can redistribute it and/or modify   *
*  it under the terms of the GNU General Public License version 2 as      *
*  published by the Free Software Foundation.                             *
*                                                                         *
*  This program is distributed in the hope that it will be useful,        *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with this program; if not, write to the                          *
*  Free Software Foundation, Inc.,                                        *
*  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
\*************************************************************************/

// Utopia Headers
#include "mangaSeries.h"

// Utopia Classes
#include "mangapublisher.h"
#include "mangamangaka.h"
#include "mangavolume.h"
#include "mediarelationship.h"

using namespace Utopia;

/// TODO - Ensure each element added is not already in the list

MangaSeries::MangaSeries(QObject* parent = 0) : QObject(parent)
{
	clear();
};

MangaSeries::MangaSeries(const MangaSeries& series, QObject* parent = 0) : QObject(parent)
{
	clear();

	mAbbrName = series.mAbbrName;
	mTitle = series.mTitle;

	mPublishers = series.mPublishers;
	mMangaka = series.mMangaka;

	mAgeRating = series.mAgeRating;
	mVisibility = series.mVisibility;

	mFavorRating = series.mFavorRating;

	mAgeDescriptors = series.mAgeDescriptors;
	mGenres = series.mGenres;

	mComments = series.mComments;
	mLangOverride = series.mLangOverride;
	mNativeOverride = series.mNativeOverride;

	mVolumes = series.mVolumes;
	mMediaRelationships = series.mMediaRelationships;
};

MangaSeries::~MangaSeries()
{
	// Code here (Maybe free pointers?)
};

MangaSeries& MangaSeries::operator=(const MangaSeries& series)
{
	if(this != &series)
		return *this;

	clear();

	mAbbrName = series.mAbbrName;
	mTitle = series.mTitle;

	mPublishers = series.mPublishers;
	mMangaka = series.mMangaka;

	mAgeRating = series.mAgeRating;
	mVisibility = series.mVisibility;

	mFavorRating = series.mFavorRating;

	mAgeDescriptors = series.mAgeDescriptors;
	mGenres = series.mGenres;

	mComments = series.mComments;
	mLangOverride = series.mLangOverride;
	mNativeOverride = series.mNativeOverride;

	mVolumes = series.mVolumes;
	mMediaRelationships = series.mMediaRelationships;

	return *this;
};

bool MangaSeries::operator==(const MangaSeries& series)
{
	if(mAbbrName != series.mAbbrName)
		return false;

	if(mTitle != series.mTitle)
		return false;

	for(int i = 0; i < mPublishers.size(); i++)
	{
		if(!series.mPublishers.contains(mPublishers[i]))
			return false;
	}

	for(int i = 0; i < mMangaka.size(); i++)
	{
		if(!series.mMangaka.contains(mMangaka[i]))
			return false;
	}

	if(mAgeRating != series.mAgeRating)
		return false;

	if(mVisibility != series.mVisibility)
		return false;

	if(mFavorRating != series.mFavorRating)
		return false;

	for(int i = 0; i < mAgeDescriptors.size(); i++)
	{
		if(!series.mAgeDescriptors.contains(mAgeDescriptors[i]))
			return false;
	}

	for(int i = 0; i < mGenres.size(); i++)
	{
		if(!series.mGenres.contains(mGenres[i]))
			return false;
	}

	if(mComments != series.mComments)
		return false;
	
	if(mLangOverride != series.mLangOverride)
		return false;

	if(mNativeOverride != series.mNativeOverride)
		return false;

	if(mVolumes != series.mVolumes)
		return false;

	for(int i = 0; i < mMediaRelationships.size(); i++)
	{
		if(!series.mMediaRelationships.contains(mMediaRelationships[i]))
			return false;
	}

	return true;
};

bool MangaSeries::operator!=(const MangaSeries& series)
{
	if((*this) == series)
		return false;
	else
		return true;
};

QString MangaSeries::abbrName() { return mAbbrName; };

QMap<QString, QString> MangaSeries::title() { return mTitle; };

QString MangaSeries::title(const QString& locale = QLocale::system().language())
{
	return mTitle.value(locale);
};

QList<MangaPublisher*> MangaSeries::publishers() { return mPublishers; };

QList<MangaPublisher*> MangaSeries::mangaka() { return mMangaka; };

AgeRating MangaSeries::ageRating() { return mAgeRating; };

Visibility MangaSeries::visibility() { return mVisibility; };

int MangaSeries::favorRating() { return mFavorRating; };

QStringList MangaSeries::ageDescriptors() { return mAgeDescriptors; };

QStringList MangaSeries::genres() { return mGenres; };

QString MangaSeries::comments() { return mComment; };

QString MangaSeries::langOverride() { return mLangOverride; };

QString MangaSeries::nativeLang() { return mNativeLang; };

MangaVolume* MangaSeries::volume(IssueIdent issue)
{
	if(mVolumes.contains(issue)
		return mVolumes.value(issue);
	else
		return NULL;
};

MangaVolume* MangaSeries::volume(const QString& volume)
{
	QMapIterator<IssueIdent, MangaVolume*> i(mVolumes);
	while( i.hasNext() )
	{
		i.next();
		if(i.value()->name() == volume)
			return i.value();
	}

	return NULL;
};

QMap<IssueIdent, MangaVolume*> MangaSeries::volumes()
{
	return mVolumes;
};

MediaRelationship* MangaSeries::mediaRelationship(Game* game)
{
	QMapIterator<IssueIdent, MangaVolume*> i(mMediaRelationships);
	while( i.hasNext() )
	{
		i.next();
		if(i.value()->contains(game))
			return i.value();
	}

	return NULL;
};

MediaRelationship* MangaSeries::mediaRelationship(AnimeSeries* anime)
{
	QMapIterator<IssueIdent, MangaVolume*> i(mMediaRelationships);
	while( i.hasNext() )
	{
		i.next();
		if(i.value()->contains(anime))
			return i.value();
	}

	return NULL;
};

MediaRelationship* MangaSeries::mediaRelationship(const QString& related_title)
{
	QMapIterator<IssueIdent, MangaVolume*> i(mMediaRelationships);
	while( i.hasNext() )
	{
		i.next();
		if(i.value()->contains(related_title))
			return i.value();
	}

	return NULL;
};

QList<MediaRelationship*> MangaSeries::mediaRelationships() { return mMediaRelationships; };

QString xml()
{
	QStingList text;
	text << "<utopia version=\"0.1\">";
	text << "  <manga>";
	text << "    <volume>";
	text << "      <abbr>" + mAbbrName + "</abbr>";
	QMapIterator<QString, QString> i(mTitle);
	while( i.hasNext() )
	{
		i.next();
		text << "      <title lang=\"" + i.key() + "\">" + i.value() + "</title>";
	}
	for(int j = 0; j < mPublishers.size(); j++)
	{
		text << "      <publisher>";
		text << "        <title lang=\"" +  + "\"";
		text << "      </publisher>";
	}
	for(int j = 0; j < mMangaka.size(); j++)
	{
		text << "      <mangaka id=\"" + QString::number( MangaFactory::getMangakaID(mMangaka[j]) ) + "\" />"
	}
	text << "      <age>";
	switch(mAgeRating)
	{
		case EC:
			text << "EC";
			break;
		case E:
			text << "E";
			break;
		case E10:
			text << "E10";
			break;
		case T:
			text << "T";
			break;
		case M:
			text << "M";
			break;
		case AO:
			text << "AO";
			break;
	}
	text << "      </age>";
	text << "      <visibility>";
	switch(mVisibility)
	{
		case PUBLIC:
			text << "public";
			break;
		case REGISTERED:
			text << "registered";
			break;
		case FRIENDS:
			text << "friends";
			break;
		case AFRIENDS:
			text << "afriends";
			break;
		case PRIVATE:
			text << "private";
			break;
	}
	text << "      </visibility>";
	text << "      <favor>" + QString::number(mFavorRating) + "</favor>";
	text << "    </volume>";
	text << "  </manga>";
	text << "</utopia>";
};

	bool startDocument();
	bool startElement( const QString&, const QString&, const QString&, const QXmlAttributes& );

	bool characters( const QString& );

	bool endElement( const QString&, const QString&, const QString& );
	bool endDocument();

void MangaSeries::setAbbrName(const QString& name)
{
	if(!name.isEmpty())
	{
		mAbbrName = name;
		emit dataChanged();
	}
};

void MangaSeries::addTitle(const QString& title, const QString& lang = CURRENT_LANG)
{
	mTitle.insert(lang, title);
};

void MangaSeries::removeTitle(const QString& title = "", const QString& lang = CURRENT_LANG)
{
	if(!title.isEmpty())
	{
		QMapIterator<QString, QString> i(mTitle);
		while( i.hasNext() )
		{
			i.next();
			if(i.value() == title)
			{
				mTitle.remove(i.key());
				return;
			}
		}
	}
	else
	{
		mTitle.remove(lang);
	}
};

void MangaSeries::clearTitles() { mTitle.clear() };

void MangaSeries::addPublisher(const QString& publisher)
{
	addPublisher( MangaFactory::getPublisherByName(publisher) );
};

void MangaSeries::addPublisher(MangaPublisher* publisher)
{
	mPublishers << publisher;
};

void MangaSeries::removePublisher(MangaPublisher* publisher)
{
	for(int i = 0; i < mPublishers.size(); i++)
	{
		if(mPublishers[i] == publisher)
		{
			mPublisher.removeAt(i);
			return;
		}
	}
};

void MangaSeries::removePublisher(const QString& publisher)
{
	removePublisher( MangaFactory::getPublisherByName(publisher) );
};

void MangaSeries::clearPublishers() { mPublishers.clear(); };

void MangaSeries::addMangaka(const QString& mangaka)
{
	addMangaka( MangaFactory::getMangakaByName(mangaka) );
};

void MangaSeries::addMangaka(MangaMangaka* mangaka)
{
	mMangaka << mangaka;
};

void MangaSeries::removeMangaka(MangaMangaka* mangaka)
{
	for(int i = 0; i < mMangaka.size(); i++)
	{
		if(mMangaka[i] == mangaka)
		{
			mMangaka.removeAt(i);
			return;
		}
	}
};

void MangaSeries::removeMangaka(const QString& mangaka)
{
	removeMangaka( MangaFactory::getMangakaByName(mangaka) );
};

void MangaSeries::clearMangaka() { mMangaka.clear(); };

void MangaSeries::setAgeRating(AgeRating rating) { mAgeRating = rating; };

void MangaSeries::setVisibility(Visibility visibility) { mVisibility = visibility; };

void MangaSeries::setFavorRating(int rating) { mFacorRating = rating; };

void MangaSeries::addAgeDescriptor(const QString& descriptor)
{
	mAgeDescriptors << descriptor;
};

void MangaSeries::addAgeDescriptors(const QStringList& descriptors)
{
	for(int i = 0; i < descriptors.size(); i++)
	{
		addAgeDescriptor(descriptors[i]);
	}
};

void MangaSeries::removeAgeDescriptor(const QString& descriptor)
{
	for(int i = 0; i < mAgeDescriptors.size(); i++)
	{
		if(mAgeDescriptors[i] == descriptor)
		{
			mAgeDescriptors.removeAt(i);
			return;
		}
	}
};

void MangaSeries::removeAgeDescriptors(const QStringList& descriptors)
{
	for(int i = 0; i < descriptors.size(); i++)
	{
		removeAgeDescriptor(descriptors[i]);
	}
};

void MangaSeries::clearAgeDescriptors() { mAgeDescriptors.clear(); };

void MangaSeries::addGenre(const QString& genre)
{
	mGenres << genre;
};

void MangaSeries::addGenres(const QStringList& genres)
{
	for(int i = 0; i < genres.size(); i++)
	{
		addGenre(genres[i]);
	}
};

void MangaSeries::removeGenre(const QString& genre)
{
	for(int i = 0; i < mGenres.size(); i++)
	{
		if(mGenres[i] == genre)
		{
			mGenres.removeAt(i);
			return;
		}
	}
};

void MangaSeries::removeGenres(const QStringList& genres)
{
	for(int i = 0; i < genres.size(); i++)
	{
		removeGenre(genres[i]);
	}
};

void MangaSeries::clearGenres() { mGenres.remove(); };

void MangaSeries::setComments(const QString& comment) { mComment = comment; };

void MangaSeries::setLangOverride(const QString& lang = CURRENT_LANG)
{
	mLangOverride = lang;
};

void MangaSeries::setNativeLang(const QString& lang = CURRENT_LANG)
{
	mNativeLang = lang;
};

void MangaSeries::addVolume(IssueIdent, const QString& volume)
{
	mVolumes.insert(IssueIdent, MangaFactory::getValumeByName(volume));
};

void MangaSeries::addVolume(IssueIdent, MangaVolume* volume)
{
	mVolumes.insert(issue, volume);
};

void MangaSeries::removeVolume(IssueIdent issue)
{
	mVolumes.remove(issue);
};

void MangaSeries::removeVolume(MangaVolume* volume)
{
	QMapIterator<IssueIdent, MangaVolume*> i(mVolumes);
	while( i.hasNext() )
	{
		i.next();
		if(i.value() == volume)
		{
			mVolumes.remove(i.key());
			return;
		}
	}
};

void MangaSeries::removeVolume(const QString& volume)
{
	QMapIterator<IssueIdent, MangaVolume*> i(mVolumes);
	while( i.hasNext() )
	{
		i.next();
		if(i.value()->name() == volume)
		{
			mVolumes.remove(i.key());
			return;
		}
	}
};

void MangaSeries::clearVolumes() { mVolumes.clear(); };

/*void MangaSeries::addMediaRelationship(const QString& relationship)
void MangaSeries::addMediaRelationship(MediaRelationship* relationship)
void MangaSeries::removeMediaRelationship(MediaRelationship* relationship);
void MangaSeries::removeMediaRelationship(const QString& relationship);
void MangaSeries::clearMediaRelationships();*/

void MangaSeries::clear()
{
	mAbbrName.clear();
	mTitle.clear();

	mPublishers.clear();
	mMangaka.clear();

	mAgeRating = 0;
	mVisibility = 0;

	mFavorRating = 0;

	mAgeDescriptors.clear();
	mGenres.clear();

	mComments.clear();
	mLangOverride.clear();
	mNativeOverride.clear();

	// Maybe we should free what these point to???
	mVolumes.clear();
	mMediaRelationships.clear();
};

void MangaSeries::populateFromXml(const QString& data)
{
	clear();

	QXmlInputSource input;
	input.setData(data);

	QXmlSimpleReader reader;
	reader.setContentHandler( this );
	reader.parse( input );
};
