#include "TestIdItemSearcher.h"
#include "Item.h"
#include "Folder.h"
#include "Movie.h"
#include <string>
#include <iostream>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(TestIdItemSearcher);

void TestIdItemSearcher::setUp()
{
    root_ = new Folder("root");
    item1_ = new Movie("item1");
    subFolder1_ = new Folder("folder2");
    item2_ = new Movie("item2");
    item3_ = new Movie("item3");
    root_->addChild(item1_);
    root_->addChild(subFolder1_);
    subFolder1_->addChild(item2_);
    subFolder1_->addChild(item3_);
}

void TestIdItemSearcher::tearDown()
{

}

/*
  Constructor test with basic parameters.
  Initialization is checked with searchedId value.
 */
void TestIdItemSearcher::test_constructor_basic()
{
    string searched_id = "string id";
    IdItemSearcher searcher(searched_id);
    CPPUNIT_ASSERT_MESSAGE("Wrong searched Id value",searcher.getSearchedId() == searched_id);
}

/*
  Search test with an existing Movie ID.
  Found values are checked with both generic getFoundItems method (which
  returns a vector) and getFoundItem (which returns a single Item element).
  Found Item is checked with its ID.
 */
void TestIdItemSearcher::test_search_existingid_fromroot()
{
    string searched_id = "item3";
    IdItemSearcher searcher(searched_id);
    searcher.search(root_);
    Item* found_item = searcher.getFoundItem();
    vector<Item*> found_items = searcher.getFoundItems();
    CPPUNIT_ASSERT_MESSAGE("Item returned is nullptr", found_item != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item found",found_item->getId() == searched_id);
    CPPUNIT_ASSERT_MESSAGE("Result vector is empty", !found_items.empty());
    CPPUNIT_ASSERT_MESSAGE("Wrong Item found (in vector)", found_items[0]->getId() == searched_id);
}

/*
  Search test with a non-existing ID.
  Found values are checked with both generic getFoundItems method (which
  returns a vector) and getFoundItem (which returns a single Item element).
 */
void TestIdItemSearcher::test_search_nonexistingid_fromroot()
{
    string searched_id = "test";
    IdItemSearcher searcher(searched_id);
    searcher.search(root_);
    Item* found_item = searcher.getFoundItem();
    vector<Item*> found_items = searcher.getFoundItems();
    CPPUNIT_ASSERT_MESSAGE("Item returned is not nullptr", found_item == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Result vector is not empty", found_items.empty());
}

/*
  Search test with an existing Movie ID.
  Search method is called on level1 Folder (here folder2).
  Found values are checked with both generic getFoundItems method (which
  returns a vector) and getFoundItem (which returns a single Item element).
  Found Item is checked with its ID.
 */
void TestIdItemSearcher::test_search_existingid_fromlevel1()
{
    string searched_id = "item2";
    IdItemSearcher searcher(searched_id);
    searcher.search(subFolder1_);
    Item* found_item = searcher.getFoundItem();
    vector<Item*> found_items = searcher.getFoundItems();
    CPPUNIT_ASSERT_MESSAGE("Item returned is nullptr", found_item != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item found", found_item->getId() == searched_id);
    CPPUNIT_ASSERT_MESSAGE("Result vector is empty", !found_items.empty());
    CPPUNIT_ASSERT_MESSAGE("Wrong Item found (in vector)", found_items[0]->getId() == searched_id);
}

/*
  Search test with a non-existing ID.
  Search method is called on level1 Folder (here folder2).
  Found values are checked with both generic getFoundItems method (which
  returns a vector) and getFoundItem (which returns a single Item element).
 */
void TestIdItemSearcher::test_search_nonexistingid_fromlevel1()
{
    string searched_id = "test";
    IdItemSearcher searcher(searched_id);
    searcher.search(subFolder1_);
    Item* found_item = searcher.getFoundItem();
    vector<Item*> found_items = searcher.getFoundItems();
    CPPUNIT_ASSERT_MESSAGE("Item returned is not nullptr", found_item == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Result vector is not empty", found_items.empty());
}

/*
  Search test with an existing ID but at an upper level than the one
  the search start from.
  Because IdItemSearcher is a descendant searcher the expected returned
  value is nullptr or an empty vector.
  Found values are checked with both generic getFoundItems method (which
  returns a vector) and getFoundItem (which returns a single Item element).
 */
void TestIdItemSearcher::test_search_upperexistingid_fromlevel1()
{
    string searched_id = "root";
    IdItemSearcher searcher(searched_id);
    searcher.search(subFolder1_);
    Item* found_item = searcher.getFoundItem();
    vector<Item*> found_items = searcher.getFoundItems();
    CPPUNIT_ASSERT_MESSAGE("Item returned is not nullptr", found_item == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Result vector is not empty", found_items.empty());
}
