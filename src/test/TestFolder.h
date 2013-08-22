#ifndef TEST_FOLDER_H
#define TEST_FOLDER_H

#include <cppunit/extensions/HelperMacros.h>
#include "Item.h"
#include "CoreException.h"
#include "MockItem.h"
#include <stdexcept>

class TestFolder : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestFolder);
    CPPUNIT_TEST(test_destructor);
    CPPUNIT_TEST(test_addSubItem);
    CPPUNIT_TEST_EXCEPTION(test_addSubItem_doubleaddition,CoreException);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void test_destructor();

    void test_addSubItem();
    void test_addSubItem_doubleaddition();

private:
    Item* item1;
    Item* item2;
    Item* folder1;
};

#endif // TEST_FOLDER_H
