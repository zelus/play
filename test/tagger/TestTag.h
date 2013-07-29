#ifndef TESTTAG_H
#define TESTTAG_H

#include <cppunit/extensions/HelperMacros.h>

#include "Item.h"
#include "Tag.h"

using namespace std;

class TestTag : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestTag);

    CPPUNIT_TEST(test_constructor);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void test_constructor();

private:
    Item* item1_;
    Tag<Item*>* tag1_;
};

#endif // TESTTAG_H
