#include "TestTag.h"

// debug
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestTag);

void TestTag::setUp()
{
    item1_ = new Item("item1");
    item2_ = new Item("item2");
    tag1_ = new Tag<Item*>("tag1");
}

void TestTag::tearDown()
{
    delete tag1_;
    delete item1_;
    delete item2_;
}

/*
  Constructor test with basic parameters.
 */
void TestTag::test_constructor()
{
    CPPUNIT_ASSERT_MESSAGE("Wrong Tag name",tag1_->getName() == "tag1");
    CPPUNIT_ASSERT_MESSAGE("Tag's registered Item map is not empty", tag1_->getRegisteredItems().size() == 0);
}

/*
  registerItem method test with a valid Item.
  Register test is done by Item number comparison and Id comparison between Item added
  and Item returned by the getRegisteredItems method.
*/
void TestTag::test_registerItem()
{
    size_t previous_tag_map_size = tag1_->getRegisteredItemsNumber();
    tag1_->registerItem(item1_,2);
    CPPUNIT_ASSERT_MESSAGE("Tag's registered Item map size hasn't be increased", tag1_->getRegisteredItemsNumber() == previous_tag_map_size+1);
    Item* registered_item = tag1_->getRegisteredItems()[2][0];
    CPPUNIT_ASSERT_MESSAGE("Item has not been registered",registered_item->getId() == item1_->getId());
}

/*
  registerItem method test with a std::nullptr as Item.
  A TaggerException is expected.
*/
void TestTag::test_registerItem_nullptrItem()
{
    tag1_->registerItem(nullptr,2);
}

/*
  registerItem method test with NULL constant as Item.
  A TaggerException is expected.
*/
void TestTag::test_registerItem_nullItem()
{
    tag1_->registerItem(NULL,2);
}

/*
  registerItem method test with a double Item addition with the same priority.
  A TaggerException is expected.
*/
void TestTag::test_registerItem_doubleAdditionSamePriority()
{
    tag1_->registerItem(item1_,2);
    tag1_->registerItem(item1_,2);
}

/*
  registerItem method test with a double Item addition with different priority.
  Register test is done by Item number comparison and Id comparison between Items added
  and Items returned by the getRegisteredItems method.
*/
void TestTag::test_registerItem_doubleAdditionDifferentPriority()
{
    size_t previous_tag_map_size = tag1_->getRegisteredItemsNumber();
    tag1_->registerItem(item1_,0);
    tag1_->registerItem(item1_,1);
    CPPUNIT_ASSERT_MESSAGE("Tag's registered Item map size hasn't been increased", tag1_->getRegisteredItemsNumber() == previous_tag_map_size + 2);
    Item* first_registered_item = tag1_->getRegisteredItems()[0][0];
    Item* second_registered_item = tag1_->getRegisteredItems()[1][0];
    CPPUNIT_ASSERT_MESSAGE("First Item hasn't been registered", first_registered_item->getId() == item1_->getId());
    CPPUNIT_ASSERT_MESSAGE("Second Item hasn't been registered", second_registered_item->getId() == item1_->getId());
}

/*
  registerItem method test with addition of two different Items with the same priority.
  Register test is done by Item number comparison and Id comparison between Items added
  and Items returned by the getRegisteredItems method.
*/
void TestTag::test_registerItem_doubleAdditionDifferentItems()
{
    size_t previous_tag_map_size = tag1_->getRegisteredItemsNumber();
    tag1_->registerItem(item1_);
    tag1_->registerItem(item2_);
    CPPUNIT_ASSERT_MESSAGE("Tag's registered Item map size hasn't been increased", tag1_->getRegisteredItemsNumber() == previous_tag_map_size + 2);
    Item* first_registered_item = tag1_->getRegisteredItems()[0][0];
    Item * second_registered_item = tag1_->getRegisteredItems()[0][1];
    CPPUNIT_ASSERT_MESSAGE("First Item hasn't been registered", first_registered_item->getId() == item1_->getId());
    CPPUNIT_ASSERT_MESSAGE("Second Item hasn't been registered", second_registered_item->getId() == item2_->getId());
}

/*
  unregisterItem method test with a valid Item to unregister (not
  null and in the tag map)
  Unregister test is done by Item number comparison.
*/
void TestTag::test_unregisterItem()
{
    size_t previous_tag_map_size = tag1_->getRegisteredItemsNumber();
    tag1_->registerItem(item1_,2);
    tag1_->unregisterItem(item1_,2);
    CPPUNIT_ASSERT_MESSAGE("Tag's registered Item map size hasn't been decreased", tag1_->getRegisteredItemsNumber() == previous_tag_map_size);
}

/*
  unregisterItem method test with a std::nullptr as Item.
  A TaggerException is expected.
*/
void TestTag::test_unregisterItem_nullptrItem()
{
    tag1_->unregisterItem(nullptr);
}

/*
  unregisterItem method test with NULL constant as Item.
  A TaggerException is expected.
*/
void TestTag::test_unregisterItem_nullItem()
{
    tag1_->unregisterItem(NULL);
}

/*
  unregisterItem method test with an Item wich is not in the registered Item map.
  A TaggerException is expected.
*/
void TestTag::test_unregisterItem_invalidItem()
{
    tag1_->registerItem(item1_);
    tag1_->unregisterItem(item2_);
}

/*
  unregisterItem method test after a valid double addition (with different priorities).
  The test removes only one of the double added Items. Unregister test is done by
  vector size comparison.
*/
void TestTag::test_unregisterItem_doubleAdditionDifferentPriority_deleteOne()
{
    tag1_->registerItem(item1_,0);
    tag1_->registerItem(item1_,1);
    size_t previous_tag_map_size = tag1_->getRegisteredItemsNumber();
    tag1_->unregisterItem(item1_,1);
    CPPUNIT_ASSERT_MESSAGE("Wrong Tag's registered Item map size", tag1_->getRegisteredItemsNumber() == previous_tag_map_size - 1);
    CPPUNIT_ASSERT_MESSAGE("First Item has also been deleted", tag1_->getRegisteredItems()[0].size() == 1);
    Item* registered_item = tag1_->getRegisteredItems()[0][0];
    CPPUNIT_ASSERT_MESSAGE("Wrong Item in first vector", registered_item->getId() == item1_->getId());
}

/*
  unregisterItem method test after a valid double addition (with different priorities).
  The test removes all the instances of the Item to unregister from the Tag map (no priority given).
  Unregister test is done by vector size comparisons.
*/
void TestTag::test_unregisterItem_doubleAddition_deleteAll()
{
    tag1_->registerItem(item1_,0);
    tag1_->registerItem(item1_,1);
    size_t previous_tag_map_size = tag1_->getRegisteredItemsNumber();
    tag1_->unregisterItem(item1_);
    CPPUNIT_ASSERT_MESSAGE("Wrong Tag's registered Item map size", tag1_->getRegisteredItemsNumber() == previous_tag_map_size - 2);
    CPPUNIT_ASSERT_MESSAGE("First Item has not been deleted", tag1_->getRegisteredItems()[0].size() == 0);
    CPPUNIT_ASSERT_MESSAGE("Second Item has not been deleted", tag1_->getRegisteredItems()[1].size() == 0);
}
