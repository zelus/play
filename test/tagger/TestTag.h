#ifndef TESTTAG_H
#define TESTTAG_H

#include <cppunit/extensions/HelperMacros.h>

#include "Item.h"
#include "Tag.h"
#include "TaggerException.h"

using namespace std;

class TestTag : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestTag);

    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_registerItem);
    CPPUNIT_TEST_EXCEPTION(test_registerItem_nullptrItem, TaggerException);
    CPPUNIT_TEST_EXCEPTION(test_registerItem_nullItem, TaggerException);
    CPPUNIT_TEST_EXCEPTION(test_registerItem_doubleAdditionSamePriority, TaggerException);
    CPPUNIT_TEST(test_registerItem_doubleAdditionDifferentPriority);
    CPPUNIT_TEST(test_registerItem_doubleAdditionDifferentItems);

    CPPUNIT_TEST(test_unregisterItem);
    CPPUNIT_TEST_EXCEPTION(test_unregisterItem_nullptrItem, TaggerException);
    CPPUNIT_TEST_EXCEPTION(test_unregisterItem_nullItem, TaggerException);
    CPPUNIT_TEST_EXCEPTION(test_unregisterItem_invalidItem, TaggerException);
    CPPUNIT_TEST(test_unregisterItem_doubleAdditionDifferentPriority_deleteOne);
    CPPUNIT_TEST(test_unregisterItem_doubleAddition_deleteAll);

    CPPUNIT_TEST(test_getRegisteredItemsWithPriority);
    CPPUNIT_TEST(test_getRegisteredItemsWithPriority_noItem);
    CPPUNIT_TEST(test_getRegisteredItemsWithPriority_emptyPriority);

    CPPUNIT_TEST(test_getRegisteredItems);
    CPPUNIT_TEST(test_getRegisteredItems_noItem);

    CPPUNIT_TEST(test_getRegisteredItemsNumber);
    CPPUNIT_TEST(test_getRegisteredItemsNumber_noItem);

    CPPUNIT_TEST(test_containsItem);
    CPPUNIT_TEST_EXCEPTION(test_containsItem_nullptrItem, TaggerException);
    CPPUNIT_TEST_EXCEPTION(test_containsItem_nullItem, TaggerException);
    CPPUNIT_TEST(test_containsItem_noItem);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void test_constructor();

    void test_registerItem();
    void test_registerItem_nullptrItem();
    void test_registerItem_nullItem();
    void test_registerItem_doubleAdditionSamePriority();
    void test_registerItem_doubleAdditionDifferentPriority();
    void test_registerItem_doubleAdditionDifferentItems();

    void test_unregisterItem();
    void test_unregisterItem_nullptrItem();
    void test_unregisterItem_nullItem();
    void test_unregisterItem_invalidItem();
    void test_unregisterItem_doubleAdditionDifferentPriority_deleteOne();
    void test_unregisterItem_doubleAddition_deleteAll();

    void test_getRegisteredItemsWithPriority();
    void test_getRegisteredItemsWithPriority_noItem();
    void test_getRegisteredItemsWithPriority_emptyPriority();

    void test_getRegisteredItems();
    void test_getRegisteredItems_noItem();

    void test_getRegisteredItemsNumber();
    void test_getRegisteredItemsNumber_noItem();

    void test_containsItem();
    void test_containsItem_nullptrItem();
    void test_containsItem_nullItem();
    void test_containsItem_noItem();
private:
    Item* item1_;
    Item* item2_;
    Tag<Item*>* tag1_;
};

#endif // TESTTAG_H
