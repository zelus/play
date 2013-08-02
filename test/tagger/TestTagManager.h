#ifndef TESTTAGMANAGER_H
#define TESTTAGMANAGER_H

#include <cppunit/extensions/HelperMacros.h>

#include "Item.h"
#include "Tag.h"
#include "TagManager.h"
#include "TaggerException.h"

using namespace std;

class TestTagManager : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestTagManager);


    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();


};

#endif // TESTTAGMANAGER_H
