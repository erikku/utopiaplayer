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

/**
 * @file utopiafactory.h The UtopiaFactory class implementation
 */

#ifndef __UtopiaFactory_h__
#define __UtopiaFactory_h__

#include "utopiadb.h"
#include "utopiablock.h"

#define db (Utopia::UtopiaFactory::getCurrentFactory())

#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QMap>

namespace Utopia
{

class UtopiaFactory
{
public:
	UtopiaFactory() { };
	//UtopiaBlock block(uid id, BlockType type = UtopiaDB_UtopiaBlock);
	//void addBlock(const UtopiaBlock& block);
	//void updateBlock(const UtopiaBlock& block);
	//void removeBlock(uid id);
	//void removeBlock(const UtopiaBlock& block);

	Individual individual(uid id);
	void addIndividual(const Individual& individual);
	void updateIndividual(const Individual& individual);
	void removeIndividual(uid id);
	void removeIndividual(const Individual& individual);

	Artist artist(uid id);
	void addArtist(const Artist& artist);
	void updateArtist(const Artist& artist);
	void removeArtist(uid id);
	void removeArtist(const Artist& artist);

	static void setCurrentFactory(UtopiaFactory *factory);
	static UtopiaFactory* getCurrentFactory();
protected:
	UtopiaBlock* blockPtr(uid id, BlockType type = UtopiaDB_UtopiaBlock);
	void addBlock(UtopiaBlock *block);
	void updateBlock(UtopiaBlock *block);
	UtopiaBlock* takeBlock(UtopiaBlock *block);

	QMap<BlockType, QHash<uid, UtopiaBlock*> >  mIDs;
	QMap<BlockType, QHash<UtopiaBlock*, uid> >  mBlocks;
};

}; // namespace Utopia

#endif // __UtopiaFactory_h__
