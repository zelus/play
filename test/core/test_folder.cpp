#include "test_folder.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestFolder);

void TestFolder::setUp()
{
    folder1 = new Folder("folder1",nullptr);
    item1 = new Item("item1",ANY_TYPE,nullptr);
    item2 = new Item("item2",ANY_TYPE,nullptr);
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

void TestFolder::test_destructor()
{
    Folder* folder = new Folder("folder");
    bool item1Deleted = false;
    bool item2Deleted = false;
    MockItem* mockItem1 = new MockItem("mockItem1",ANY_TYPE,folder,&item1Deleted);
    MockItem* mockItem2 = new MockItem("mockItem2",ANY_TYPE,folder,&item2Deleted);
    delete folder;
    CPPUNIT_ASSERT_MESSAGE("item1 hasn't been deleted",item1Deleted);
    CPPUNIT_ASSERT_MESSAGE("item2 hasn't been deleted",item2Deleted);
}
