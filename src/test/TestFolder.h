#ifndef TEST_FOLDER_H
#define TEST_FOLDER_H

#include <cppunit/extensions/HelperMacros.h>
#include "Item.h"
#include "CoreException.h"

class TestFolder : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestFolder);

    CPPUNIT_TEST(test_constructor);

    CPPUNIT_TEST(test_destructor);

    CPPUNIT_TEST(test_addSubItem);
    CPPUNIT_TEST_EXCEPTION(test_addSubItem_doubleaddition,CoreException);

    CPPUNIT_TEST(test_removeSubItem);
    CPPUNIT_TEST_EXCEPTION(test_removeSubItem_notchild,CoreException);

    CPPUNIT_TEST(test_deleteSubItem);
    CPPUNIT_TEST_EXCEPTION(test_deleteSubItem_notChild,CoreException);

    CPPUNIT_TEST(test_getSubItem);
    CPPUNIT_TEST(test_getSubItem_notchild);

    CPPUNIT_TEST(test_containsSubItem);
    CPPUNIT_TEST(test_containsSubItem_notchild);

    CPPUNIT_TEST(test_getAllSubItems);
    CPPUNIT_TEST(test_getAllSubItems_emptychildrenlist);

    CPPUNIT_TEST(test_accept);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void test_constructor();

    void test_destructor();

    void test_addSubItem();
    void test_addSubItem_doubleaddition();

    void test_removeSubItem();
    void test_removeSubItem_notchild();

    void test_deleteSubItem();
    void test_deleteSubItem_notChild();

    void test_getSubItem();
    void test_getSubItem_notchild();

    void test_containsSubItem();
    void test_containsSubItem_notchild();

    void test_getAllSubItems();
    void test_getAllSubItems_emptychildrenlist();

    void test_accept();

private:
    Item* item1;
    Item* item2;
    Item* folder1;
};

#endif // TEST_FOLDER_H
