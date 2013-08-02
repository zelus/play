#ifndef TESTTAGMANAGER_H
#define TESTTAGMANAGER_H

#include <cppunit/extensions/HelperMacros.h>

#include "Item.h"
#include "Tag.h"
#include "MockTag.h"
#include "MockTagManager.h"
#include "TagManager.h"
#include "TaggerException.h"

using namespace std;

class TestTagManager : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestTagManager);

    CPPUNIT_TEST(test_destructor);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void test_destructor();
private:
    TagManager<Item*>* tagManager_;
    Tag<Item*>* tag1_;
    Tag<Item*>* tag2_;

};

#endif // TESTTAGMANAGER_H
