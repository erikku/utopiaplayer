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

#include <QtTest/QtTest>

#include <utopiadb/utopiablock.h>
#include <utopiadb/individual.h>
//#include <utopiadb/artist.h>
//#include <utopiadb/publisher.h>
//#include <utopiadb/cover.h>
//#include <utopiadb/utopiafactory.h>

#include <iostream>

class UtopiaDBTests : public QObject
{
	Q_OBJECT

private slots:
	void initTestCase() { };

	void utopiablock();
	void utopiablock_data();

	void individual();
	void individual_data();
	//void artist();
	//void artist_data();
	//void publisher();
	//void publisher_data();

	//void cover();
	//void cover_data();

	//void factory();
	//void factory_data();

	void cleanupTestCase() { };
};

void UtopiaDBTests::utopiablock()
{
	QFETCH(Utopia::uid, id);
	QFETCH(QString, name);
	QFETCH(QString, comments);
	QFETCH(QString, override);
	QFETCH(QString, native);

	// Create a block with some data
	Utopia::UtopiaBlock block1(name);
	block1.setID(id);
	block1.setComments(comments);
	block1.setLangOverride(override);
	block1.setNativeLang(native);

	// Check all the data returns right
	QVERIFY(id == block1.id());
	QVERIFY(name == block1.name());
	QVERIFY(comments == block1.comments());
	QVERIFY(override == block1.langOverride());
	QVERIFY(native == block1.nativeLang());

	// Copy the block (assignment method)
	Utopia::UtopiaBlock *block2 = new Utopia::UtopiaBlock();
	(*block2) = block1;

	// Copy the block (copy constructor method)
	Utopia::UtopiaBlock *block3 = new Utopia::UtopiaBlock(block1);

	// Check all the data returns right for the 2nd and 3rd block
	QVERIFY(id == block2->id());
	QVERIFY(name == block2->name());
	QVERIFY(comments == block2->comments());
	QVERIFY(override == block2->langOverride());
	QVERIFY(native == block2->nativeLang());
	QVERIFY(name == block3->name());
	QVERIFY(comments == block3->comments());
	QVERIFY(override == block3->langOverride());
	QVERIFY(native == block3->nativeLang());

	// Ensure the blocks are considered equal
	QVERIFY(block1 == (*block2));
	QVERIFY(block1 == (*block3));

	// Ensure the blocks are no longer equal
	block2->clear();
	QVERIFY(block1 != (*block2));

	// Make sure a block that was cleared is equal to a fresh block
	Utopia::UtopiaBlock block4;
	QVERIFY((*block2) == block4);

	delete block2;
	delete block3;
};

void UtopiaDBTests::utopiablock_data()
{
	QTest::addColumn<Utopia::uid>("id");
	QTest::addColumn<QString>("name");
	QTest::addColumn<QString>("comments");
	QTest::addColumn<QString>("override");
	QTest::addColumn<QString>("native");

	QTest::newRow("english") << (Utopia::uid)10 << QString::fromUtf8("BLOCK") << QString::fromUtf8("comment") << "ja" << "en";
	QTest::newRow("japanese") <<(Utopia::uid) 8346 << QString::fromUtf8("ブロック") << QString::fromUtf8("コメント") << "ja" << "ja";
};

void UtopiaDBTests::individual()
{
	QFETCH(QString, individual_name);

	// Create a block with some data
	Utopia::Individual block1;
	block1.addIndividualName(individual_name);
	block1.individualName().clear();

	// Check all the data returns right
	QVERIFY(individual_name == block1.individualName());

	// Copy the block (assignment method)
	Utopia::Individual *block2 = new Utopia::Individual;
	(*block2) = block1;

	// Copy the block (copy constructor method)
	Utopia::Individual *block3 = new Utopia::Individual(block1);

	// Check all the data returns right for the 2nd and 3rd block
	QVERIFY(individual_name == block2->individualName());
	QVERIFY(individual_name == block3->individualName());

	// Ensure the blocks are considered equal
	QVERIFY(block1 == (*block2));

	// Ensure the blocks are no longer equal
	block2->clearIndividualNames();
	QVERIFY(block1 != (*block2));

	// Make sure a block that was cleared is equal to a fresh block
	Utopia::Individual block4;
	QVERIFY((*block2) == block4);

	delete block2;
	delete block3;
};

void UtopiaDBTests::individual_data()
{
	QTest::addColumn<QString>("individual_name");

	QTest::newRow("english") << QString::fromUtf8("YUI");
	QTest::newRow("japanese") << QString::fromUtf8("モーニング娘。");
};
/*
void UtopiaDBTests::artist()
{
	QFETCH(QString, artist_name);

	// Create a block with some data
	Utopia::Artist block1(0);
	block1.addArtistName(artist_name);
	block1.artistName().clear();

	// Check all the data returns right
	QVERIFY(artist_name == block1.artistName());

	// Copy the block (assignment method)
	Utopia::Artist *block2 = new Utopia::Artist(0);
	(*block2) = block1;

	// Copy the block (copy constructor method)
	Utopia::Artist *block3 = new Utopia::Artist(block1);

	// Check all the data returns right for the 2nd and 3rd block
	QVERIFY(artist_name == block2->artistName());
	QVERIFY(artist_name == block3->artistName());

	// Ensure the blocks are considered equal
	QVERIFY(block1 == (*block2));

	// Ensure the blocks are no longer equal
	block2->clearArtistNames();
	QVERIFY(block1 != (*block2));

	// Make sure a block that was cleared is equal to a fresh block
	Utopia::Artist block4(0);
	QVERIFY((*block2) == block4);

	delete block2;
	delete block3;
};

void UtopiaDBTests::artist_data()
{
	QTest::addColumn<QString>("artist_name");

	QTest::newRow("english") << QString::fromUtf8("YUI");
	QTest::newRow("japanese") << QString::fromUtf8("モーニング娘。");
};

void UtopiaDBTests::publisher()
{
	QFETCH(QString, publisher_name);

	// Create a block with some data
	Utopia::Publisher block1(0);
	block1.addPublisherName(publisher_name);
	block1.publisherName().clear();

	// Check all the data returns right
	QVERIFY(publisher_name == block1.publisherName());

	// Copy the block (assignment method)
	Utopia::Publisher *block2 = new Utopia::Publisher(0);
	(*block2) = block1;

	// Copy the block (copy constructor method)
	Utopia::Publisher *block3 = new Utopia::Publisher(block1);

	// Check all the data returns right for the 2nd and 3rd block
	QVERIFY(publisher_name == block2->publisherName());
	QVERIFY(publisher_name == block3->publisherName());

	// Ensure the blocks are considered equal
	QVERIFY(block1 == (*block2));

	// Ensure the blocks are no longer equal
	block2->clearPublisherNames();
	QVERIFY(block1 != (*block2));

	// Make sure a block that was cleared is equal to a fresh block
	Utopia::Publisher block4(0);
	QVERIFY((*block2) == block4);

	delete block2;
	delete block3;
};

void UtopiaDBTests::publisher_data()
{
	QTest::addColumn<QString>("publisher_name");

	QTest::newRow("english") << QString::fromUtf8("YUI");
	QTest::newRow("japanese") << QString::fromUtf8("モーニング娘。");
};

void UtopiaDBTests::cover()
{
	QFETCH(QString, cover_path);

	// Create a block with some data
	Utopia::Cover block1(cover_path);
	
	// Check all the data returns right
	QVERIFY(cover_path == block1.path());
	QVERIFY(block1.cover().size() == QSize(400, 400));

	// Copy the block (assignment method)
	Utopia::Cover *block2 = new Utopia::Cover(0);
	(*block2) = block1;

	// Copy the block (copy constructor method)
	Utopia::Cover *block3 = new Utopia::Cover(block1);

	// Check all the data returns right for the 2nd and 3rd block
	QVERIFY(cover_path == block2->path());
	QVERIFY(cover_path == block3->path());

	// Ensure the blocks are considered equal
	QVERIFY(block1 == (*block2));

	// Ensure the blocks are no longer equal
	block2->clear();
	QVERIFY(block1 != (*block2));

	// Make sure a block that was cleared is equal to a fresh block
	Utopia::Cover block4(0);
	QVERIFY((*block2) == block4);

	delete block2;
	delete block3;
};

void UtopiaDBTests::cover_data()
{
	QTest::addColumn<QString>("cover_path");

	QTest::newRow("test_cover") << QString::fromUtf8("image.png");
};

void UtopiaDBTests::factory()
{
	QFETCH(int, id1);
	QFETCH(int, id2);
	QFETCH(QString, artist_name1);
	QFETCH(QString, artist_name2);
	QFETCH(QString, artist_name3);
	QFETCH(QString, artist_name4);

	// Create 2 blocks with some data
	Utopia::Artist block1(0);
	block1.setID(id1);
	block1.addArtistName(artist_name1, "ja");
	block1.addArtistName(artist_name2, "en");
	Utopia::Artist block2(0);
	block2.setID(id2);
	block2.addArtistName(artist_name3, "ja");
	block2.addArtistName(artist_name4, "en");

	// Add the blocks to the factory
	Utopia::UtopiaFactory::setCurrentFactory(new Utopia::UtopiaFactory());
	db->addArtist(block1);
	db->addArtist(block2);
	//db->addBlock(block2);

	// Fetch the blocks and see if they return right
	QVERIFY(block1 == db->artist(id1));
	//QVERIFY(block2 == db->block(id2, UtopiaDB_Artist));
	QVERIFY(block2 == db->artist(id2));

	// Remove the blocks from the factory
	db->removeArtist(id1);
	db->removeArtist(block2);

	// Ensure it doesn't return the blocks now
	QVERIFY(block1 != db->artist(id1));
	//QVERIFY(block2 != db->block(id2, UtopiaDB_Artist));
	QVERIFY(block2 != db->artist(id2));

	delete db;
	Utopia::UtopiaFactory::setCurrentFactory(0);
};

void UtopiaDBTests::factory_data()
{
	QTest::addColumn<int>("id1");
	QTest::addColumn<int>("id2");
	QTest::addColumn<QString>("artist_name1");
	QTest::addColumn<QString>("artist_name2");
	QTest::addColumn<QString>("artist_name3");
	QTest::addColumn<QString>("artist_name4");

	QTest::newRow("t1") << 10 << 134 << QString::fromUtf8("モーニング娘。") << QString::fromUtf8("Morning Musume") << QString::fromUtf8("新垣里沙") << QString::fromUtf8("Niigaki Risa");
	QTest::newRow("t2") << 1482 << 486 << QString::fromUtf8("安倍なつみ") << QString::fromUtf8("Abe Natsumi") << QString::fromUtf8("大塚愛") << QString::fromUtf8("Ai Otsuka");
};
*/
QTEST_MAIN(UtopiaDBTests)
#include "tests.moc"
