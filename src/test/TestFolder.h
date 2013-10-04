#ifndef TEST_FOLDER_H
#define TEST_FOLDER_H

#include <cppunit/extensions/HelperMacros.h>
#include "TreeContext.h"
#include "Item.h"
#include "CoreException.h"

using namespace play_core;

class TestFolder : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestFolder);

    CPPUNIT_TEST(test_constructor_basic);

    CPPUNIT_TEST(test_destructor);

    CPPUNIT_TEST(test_addChild_emptyfolder);
    CPPUNIT_TEST(test_addChild_notemptyfolder);
    CPPUNIT_TEST_EXCEPTION(test_addChild_doubleaddition,CoreException);

    CPPUNIT_TEST_EXCEPTION(test_removeChild_emptyfolder,CoreException);
    CPPUNIT_TEST(test_removeChild_singlechild);
    CPPUNIT_TEST(test_removeChild_multiplechild);
    CPPUNIT_TEST_EXCEPTION(test_removeChild_notchild,CoreException);

    CPPUNIT_TEST_EXCEPTION(test_deleteChild_emptyfolder,CoreException);
    CPPUNIT_TEST(test_deleteChild_singlechild);
    CPPUNIT_TEST(test_deleteChild_multiplechild);
    CPPUNIT_TEST_EXCEPTION(test_deleteChild_notChild,CoreException);

    CPPUNIT_TEST(test_getChild_emptyfolder);
    CPPUNIT_TEST(test_getChild_singlechild);
    CPPUNIT_TEST(test_getChild_multiplechild);
    CPPUNIT_TEST(test_getChild_notchild);

    CPPUNIT_TEST(test_containsChild_emptyfolder);
    CPPUNIT_TEST(test_containsChild_singlechild);
    CPPUNIT_TEST(test_containsChild_multiplechild);
    CPPUNIT_TEST(test_containsChild_notchild);

    CPPUNIT_TEST(test_getChildIndex_emptyfolder);
    CPPUNIT_TEST(test_getChildIndex_singlechild);
    CPPUNIT_TEST(test_getChildIndex_multiplechild_first);
    CPPUNIT_TEST(test_getChildIndex_multiplechild_last);
    CPPUNIT_TEST(test_getChildIndex_notchild);

    CPPUNIT_TEST(test_getChildren_emptyfolder);
    CPPUNIT_TEST(test_getChildren_singlechild);
    CPPUNIT_TEST(test_getChildren_multiplechild);

    CPPUNIT_TEST(test_childCount_emptyfolder);
    CPPUNIT_TEST(test_childCount_singlechild);
    CPPUNIT_TEST(test_childCount_multiplechild);

    CPPUNIT_TEST(test_accept);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void test_constructor_basic();

    void test_destructor();

    void test_addChild_emptyfolder();
    void test_addChild_notemptyfolder();
    void test_addChild_doubleaddition();

    void test_removeChild_emptyfolder();
    void test_removeChild_singlechild();
    void test_removeChild_multiplechild();
    void test_removeChild_notchild();

    void test_deleteChild_emptyfolder();
    void test_deleteChild_singlechild();
    void test_deleteChild_multiplechild();
    void test_deleteChild_notChild();

    void test_getChild_emptyfolder();
    void test_getChild_singlechild();
    void test_getChild_multiplechild();
    void test_getChild_notchild();

    void test_containsChild_emptyfolder();
    void test_containsChild_singlechild();
    void test_containsChild_multiplechild();
    void test_containsChild_notchild();

    void test_getChildIndex_emptyfolder();
    void test_getChildIndex_singlechild();
    void test_getChildIndex_multiplechild_first();
    void test_getChildIndex_multiplechild_last();
    void test_getChildIndex_notchild();

    void test_getChildren_emptyfolder();
    void test_getChildren_singlechild();
    void test_getChildren_multiplechild();

    void test_childCount_emptyfolder();
    void test_childCount_singlechild();
    void test_childCount_multiplechild();

    void test_accept();

private:
    Item* item1;
    Item* item2;
    Item* folder1;
};

#endif // TEST_FOLDER_H
