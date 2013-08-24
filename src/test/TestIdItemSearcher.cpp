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
    root_ = new Folder("root","folder");
    item1_ = new Movie("item1","item1",root_);
    subFolder1_ = new Folder("folder2","folder2",root_);
    item2_ = new Movie("item2","item2",subFolder1_);
    item3_ = new Movie("item3","item3",subFolder1_);
}

void TestIdItemSearcher::tearDown()
{
    delete root_;
}

void TestIdItemSearcher::test_constructor()
{
    string searched_id = "string id";
    IdItemSearcher searcher(searched_id);
    CPPUNIT_ASSERT_MESSAGE("Wrong searched Id value",searcher.getSearchedId() == searched_id);
}

void TestIdItemSearcher::test_search_movieexistingid()
{

    string searched_id = "item3";
    IdItemSearcher searcher(searched_id);
    root_->accept(&searcher);
    Item* founded_item = searcher.getFoundItem();
    vector<Item*> founded_items = searcher.getFoundItems();
    CPPUNIT_ASSERT_MESSAGE("Item returned is nullptr", founded_item != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong search result",founded_item->getId() == searched_id);
    CPPUNIT_ASSERT_MESSAGE("Result vector is empty", !founded_items.empty());
    CPPUNIT_ASSERT_MESSAGE("Wrong result in vector", founded_items[0]->getId() == searched_id);
}

void TestIdItemSearcher::test_search_folderexistingid()
{
    string searched_id = "folder2";
    IdItemSearcher searcher(searched_id);
    root_->accept(&searcher);
    Item* founded_item = searcher.getFoundItem();
    vector<Item*> founded_items = searcher.getFoundItems();
    CPPUNIT_ASSERT_MESSAGE("Item returned is nullptr", founded_item != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong search result", founded_item->getId() == searched_id);
    CPPUNIT_ASSERT_MESSAGE("Result vector is empty", !founded_items.empty());
    CPPUNIT_ASSERT_MESSAGE("Wrong result in vector", founded_items[0]->getId() == searched_id);
}

void TestIdItemSearcher::test_search_movienonexistingid()
{
    string searched_id = "test";
    IdItemSearcher searcher(searched_id);
    root_->accept(&searcher);
    Item* founded_item = searcher.getFoundItem();
    vector<Item*> founded_items = searcher.getFoundItems();
    CPPUNIT_ASSERT_MESSAGE("Item returned is not nullptr", founded_item == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Result vector is not empty", founded_items.empty());
}
