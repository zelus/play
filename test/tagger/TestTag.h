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

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void test_constructor();

    void test_registerItem();
    void test_registerItem_nullptrItem();
private:
    Item* item1_;
    Tag<Item*>* tag1_;
};

#endif // TESTTAG_H
