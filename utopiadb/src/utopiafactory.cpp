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

#include "utopiafactory.h"
#include "artist.h"

using namespace Utopia;

static UtopiaFactory *gCurrentFactory = 0;

void UtopiaFactory::setCurrentFactory(UtopiaFactory *factory)
{
	gCurrentFactory = factory;
};

UtopiaFactory* UtopiaFactory::getCurrentFactory()
{
	Q_ASSERT(gCurrentFactory);
	return gCurrentFactory;
};

Individual UtopiaFactory::individual(uid id)
{
	UtopiaBlock *block = blockPtr(id, UtopiaDB_Individual);
	if(!block)
		return Individual(0);

	return Individual(*(Individual*)block);
};

void UtopiaFactory::addIndividual(const Individual& individual)
{
	Individual *block = new Individual(individual);
	addBlock(block);
};

void UtopiaFactory::updateIndividual(const Individual& individual)
{
	Individual block = individual;
	updateBlock(&block);
};

void UtopiaFactory::removeIndividual(uid id)
{
	Individual block = individual(id);
	UtopiaBlock *deleteMe = takeBlock(&block);

	if(deleteMe)
		delete deleteMe;
};

void UtopiaFactory::removeIndividual(const Individual& individual)
{
	Individual block = individual;
	UtopiaBlock *deleteMe = takeBlock(&block);

	if(deleteMe)
		delete deleteMe;
};

Artist UtopiaFactory::artist(uid id)
{
	UtopiaBlock *block = blockPtr(id, UtopiaDB_Artist);
	if(!block)
		return Artist(0);

	return Artist(*(Artist*)block);
};

void UtopiaFactory::addArtist(const Artist& artist)
{
	Artist *block = new Artist(artist);
	addBlock(block);
};

void UtopiaFactory::updateArtist(const Artist& artist)
{
	Artist block = artist;
	updateBlock(&block);
};

void UtopiaFactory::removeArtist(uid id)
{
	Artist block = artist(id);
	UtopiaBlock *deleteMe = takeBlock(&block);

	if(deleteMe)
		delete deleteMe;
};

void UtopiaFactory::removeArtist(const Artist& artist)
{
	Artist block = artist;
	UtopiaBlock *deleteMe = takeBlock(&block);

	if(deleteMe)
		delete deleteMe;
};

UtopiaBlock* UtopiaFactory::blockPtr(uid id, BlockType type)
{
	// Make sure we have the block type first.
	if(!mIDs.contains(type))
		return 0;

	// Make sure we have the block before we return it.
	if(!(mIDs[type]).contains(id))
		return 0;

	// Return a pointer to the block
	return mIDs.value(type).value(id);
};

void UtopiaFactory::addBlock(UtopiaBlock *block)
{
	// If we already have a block with this ID, don't do anything
	if( mIDs[block->type()].contains(block->id()) )
		return;

	// Insert the block into the lists
	(mIDs[block->type()])[block->id()] = block;
	(mBlocks[block->type()])[block] = block->id();
};

void UtopiaFactory::updateBlock(UtopiaBlock *block)
{
	// If we don't have the block type, don't do anything.
	if(!mBlocks.contains(block->type()))
		return;

	// Fetch our block from it's ID and type.
	UtopiaBlock *updateBlock = blockPtr(block->id(), block->type());

	// Bail if we don't already have the block.
	if(!updateBlock)
		return;

	// Update our block.
	*updateBlock = *block;
};

UtopiaBlock* UtopiaFactory::takeBlock(UtopiaBlock *block)
{
	// If we don't have the block type, don't do anything.
	if(!mBlocks.contains(block->type()))
		return 0;

	// Remove the block from the lists
	UtopiaBlock *removedBlock = (mIDs[block->type()]).take( block->id() );
	(mBlocks[block->type()]).remove( removedBlock );

	// Return the block we removed
	return removedBlock;
};
