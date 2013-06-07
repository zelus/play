#ifndef TEST_FOLDER_H
#define TEST_FOLDER_H

#include <cppunit/extensions/HelperMacros.h>

#include <stdexcept>

#include "folder.h"
#include "item.h"
#include "mock_item.h"

using namespace std;

class TestFolder : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestFolder);
    CPPUNIT_TEST(test_destructor);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void test_destructor();

private:
    Item* item1;
    Item* item2;
    Folder* folder1;
};

#endif // TEST_FOLDER_H
