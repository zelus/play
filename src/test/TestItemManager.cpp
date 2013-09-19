#include "TestItemManager.h"
#include "Movie.h"
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(TestItemManager);

void TestItemManager::setUp()
{
    itemTree_ = new ItemTree();
}

void TestItemManager::tearDown()
{
    delete itemTree_;
}

void TestItemManager::test_constructor()
{
    Item* rootItem = itemTree_->getRootItem();
    CPPUNIT_ASSERT_MESSAGE("Root Item ID is not 0", rootItem->getId() == "0");
    CPPUNIT_ASSERT_MESSAGE("Root Item name is not _root_", rootItem->getName() == "_root_");
    CPPUNIT_ASSERT_MESSAGE("Root Item parent is not nullptr", rootItem->getParent() == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Item number is not 0", itemTree_->getItemNumber() == 0);
}
