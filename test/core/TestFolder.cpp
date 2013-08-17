#include "TestFolder.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestFolder);

void TestFolder::setUp()
{
    folder1 = new Folder("0","folder1",nullptr);
    item1 = new Item("1","item1",ANY_TYPE,nullptr);
    item2 = new Item("2","item2",ANY_TYPE,nullptr);
}

void TestFolder::tearDown()
{
    if(!folder1->containsSubItem(item1->getName())) {
        delete item1;
    }
    if(!folder1->containsSubItem(item2->getName())) {
        delete item2;
    }
    delete folder1;
}

/*
  Destructor test with a Folder containing two Items.
  SubItem deletion checking is done with the MockItem
  mock : a boolean is setted to true if the Item mocked
  destructor has been called.
 */
void TestFolder::test_destructor()
{
    Folder* folder = new Folder("3", "folder");
    bool item1Deleted = false;
    bool item2Deleted = false;
    MockItem* mockItem1 = new MockItem("4", "mockItem1",ANY_TYPE,folder,item1Deleted);
    MockItem* mockItem2 = new MockItem("5", "mockItem2",ANY_TYPE,folder,item2Deleted);
    delete folder;
    CPPUNIT_ASSERT_MESSAGE("item1 hasn't been deleted",item1Deleted);
    CPPUNIT_ASSERT_MESSAGE("item2 hasn't been deleted",item2Deleted);
}

/*
  addSubItem test. Folder consistency is checked by
  the folder size and the contain method. Item
  consistency is checked by the getParent method.
 */
void TestFolder::test_addSubItem()
{
    folder1->addSubItem(item1);
    folder1->addSubItem(item2);
    CPPUNIT_ASSERT_MESSAGE("folder doesn't contain the two items",folder1->getAllSubItems().size() == 2);
    CPPUNIT_ASSERT_MESSAGE("folder doesn't contain item1", folder1->containsSubItem("item1"));
    CPPUNIT_ASSERT_MESSAGE("folder doesn't contain item2", folder1->containsSubItem("item2"));
    CPPUNIT_ASSERT_MESSAGE("wrong item1 parent", item1->getParent()->getName() == "folder1");
    CPPUNIT_ASSERT_MESSAGE("wrong item2 parent", item2->getParent()->getName() == "folder1");
}

/*
  addSubItem test with addition of an Item already in the sub item list.
  A std::logic_error is expected (Item cannot have the same child twice,
  see documentation for further explanations).
 */
void TestFolder::test_addSubItem_doubleaddition()
{
    folder1->addSubItem(item1);
    folder1->addSubItem(item1);
}
