#include "TestItemManager.h"
#include "Movie.h"
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(TestItemManager);

void TestItemManager::setUp()
{
    itemManager_ = new ItemManager();
}

void TestItemManager::tearDown()
{
    delete itemManager_;
}

void TestItemManager::test_constructor()
{
    Item* rootItem = itemManager_->getRootItem();
    CPPUNIT_ASSERT_MESSAGE("Root Item ID is not 0", rootItem->getId() == "0");
    CPPUNIT_ASSERT_MESSAGE("Root Item name is not _root_", rootItem->getName() == "_root_");
    CPPUNIT_ASSERT_MESSAGE("Root Item parent is not nullptr", rootItem->getParent() == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Item number is not 0", itemManager_->getItemNumber() == 0);

}

/*
  createMovie basic test with valid parameters.
  The parent management is not tested (see createMovie_*parent
  for those tests).
  ID unicity is not strongly checked : the test only verify that
  the generated ID is not the same as the root item. See createItem_idunicity_*
  for those tests.
 */
void TestItemManager::test_createMovie()
{
    string movie_name = "movie";
    string movie_summary = "summary movie";
    short movie_notation = 5;
    Item* item_movie = itemManager_->createMovie(movie_name,nullptr,movie_summary,movie_notation);
    Movie* movie = dynamic_cast<Movie*>(item_movie);
    CPPUNIT_ASSERT_MESSAGE("Invalid movie name", movie->getName() == movie_name);
    CPPUNIT_ASSERT_MESSAGE("Invalid movie summary", movie->getSummary() == movie_summary);
    CPPUNIT_ASSERT_MESSAGE("Invalid movie notation", movie->getNotation() == movie_notation);
    CPPUNIT_ASSERT_MESSAGE("Movie has the same ID as the root Item", movie->getId() != itemManager_->getRootItem()->getId());
}

/*
  createMovie test with nullptr given as parent.
  Construction operations are not tested (see test_createMovie
  for those tests).
 */
void TestItemManager::test_createMovie_nullparent()
{
    Item* item_movie = itemManager_->createMovie("movie");
    Movie* movie = dynamic_cast<Movie*>(item_movie);
    Item* movie_parent = movie->getParent();
    CPPUNIT_ASSERT_MESSAGE("Movie parent is nullptr", movie_parent != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Movie parent is different from root element", movie_parent->getId() == itemManager_->getRootItem()->getId());
}

/*
  Id unicity test through creational methods.
  The test is a basic double Item creation. It verify that each
  ID in the Item tree is different form the other (including the root
  Item).
 */
void TestItemManager::test_createItem_idunicity_doublecreation()
{
    Item* item_movie1 = itemManager_->createMovie("movie1");
    Item* item_movie2 = itemManager_->createMovie("movie2");
    CPPUNIT_ASSERT_MESSAGE("Movie1 has the same ID as root Item", item_movie1->getId() != itemManager_->getRootItem()->getId());
    CPPUNIT_ASSERT_MESSAGE("Movie2 has the same ID as root Item", item_movie2->getId() != itemManager_->getRootItem()->getId());
    CPPUNIT_ASSERT_MESSAGE("Movie1 has the same ID as movie2", item_movie1->getId() != item_movie2->getId());
}

/*
  Id unicity test through creational methods.
  The test start with the a double Item creation. Then the first created
  Item is removed (calling the deleteItem method) and an other one is
  created.
  This method test that if there is an autoincrement algorithm that generates
  the IDs it works well and doesn't create duplicated IDs.
  In that specific case a CoreException is thrown if the ID is duplicated
  because the deleted and created movie are in the same folder.
 */
void TestItemManager::test_createItem_idunicity_withdeletion()
{
    Item* item_movie1 = itemManager_->createMovie("movie1");
    Item* item_movie2 = itemManager_->createMovie("movie2");
    itemManager_->deleteItem(item_movie1);
    itemManager_->createMovie("movie3");
}
