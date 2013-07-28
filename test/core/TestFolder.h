#ifndef TEST_FOLDER_H
#define TEST_FOLDER_H

#include <cppunit/extensions/HelperMacros.h>

#include <stdexcept>

#include "Folder.h"
#include "Item.h"
#include "MockItem.h"

using namespace std;

class TestFolder : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestFolder);
    CPPUNIT_TEST(test_destructor);
    CPPUNIT_TEST(test_addSubItem);
    CPPUNIT_TEST_EXCEPTION(test_addSubItem_doubleaddition,logic_error);
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
    Folder* folder1;
};

#endif // TEST_FOLDER_H
