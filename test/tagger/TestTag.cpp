#include "TestTag.h"

// debug
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestTag);

void TestTag::setUp()
{
    item1_ = new Item("item1");
    tag1_ = new Tag<Item*>("tag1");
}

void TestTag::tearDown()
{
    delete tag1_;
    delete item1_;
}

void TestTag::test_constructor()
{
    CPPUNIT_ASSERT_MESSAGE("Wrong Tag name",tag1_->getName() == "tag1");
}

void TestTag::test_registerItem()
{
    tag1_->registerItem(item1_,2);
    Item* registered_item = tag1_->getRegisteredItems()[2][0];
    CPPUNIT_ASSERT_MESSAGE("Item has not been registered",registered_item->getId() == item1_->getId());
}

void TestTag::test_registerItem_nullptrItem()
{
    tag1_->registerItem(nullptr,2);
}
