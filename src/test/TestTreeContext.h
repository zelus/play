#ifndef TEST_ITEMMANAGER_H
#define TEST_ITEMMANAGER_H

#include <cppunit/extensions/HelperMacros.h>

#include "TreeContext.h"
#include <stdexcept>

using namespace std;
using namespace play_core;

class TestTreeContext : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestTreeContext);

  CPPUNIT_TEST(test_constructor_basic);

  CPPUNIT_TEST(test_destructor_singleChildInRoot);
  CPPUNIT_TEST(test_destructor_multipleChildrenInRoot);

  CPPUNIT_TEST(test_getRootItem);

  CPPUNIT_TEST(test_getTopLevelItems_emptyRoot);
  CPPUNIT_TEST(test_getTopLevelItems_singleChildInRoot);
  CPPUNIT_TEST(test_getTopLevelItems_multipleChildrenInRoot);

  CPPUNIT_TEST(test_getTopLevelItemCount_emptyRoot);
  CPPUNIT_TEST(test_getTopLevelItemCount_singleChildInRoot);
  CPPUNIT_TEST(test_getTopLevelItemCount_multipleChildrenInRoot);

  CPPUNIT_TEST(test_addTopLevelItem_nullParent);
  CPPUNIT_TEST(test_addTopLevelItem_notNullParent_notInContext);
  CPPUNIT_TEST(test_addTopLevelItem_notNullParent_inContext);

  CPPUNIT_TEST(test_moveItem_nullparent);
  CPPUNIT_TEST(test_moveItem_notNullParent_notInContext);
  CPPUNIT_TEST(test_moveItem_notNullParent_inContext);

  CPPUNIT_TEST(test_registerItem_notEmptyContext_sameItemName);
  CPPUNIT_TEST(test_registerItem_afterDeleteItem);

  CPPUNIT_TEST(test_deleteItem_nullParent);
  CPPUNIT_TEST(test_deleteItem_notNullParent);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void test_constructor_basic();

  void test_destructor_singleChildInRoot();
  void test_destructor_multipleChildrenInRoot();

  void test_getRootItem();

  void test_getTopLevelItems_emptyRoot();
  void test_getTopLevelItems_singleChildInRoot();
  void test_getTopLevelItems_multipleChildrenInRoot();

  void test_getTopLevelItemCount_emptyRoot();
  void test_getTopLevelItemCount_singleChildInRoot();
  void test_getTopLevelItemCount_multipleChildrenInRoot();

  void test_addTopLevelItem_nullParent();
  void test_addTopLevelItem_notNullParent_notInContext();
  void test_addTopLevelItem_notNullParent_inContext();

  void test_moveItem_nullparent();
  void test_moveItem_notNullParent_notInContext();
  void test_moveItem_notNullParent_inContext();

  void test_registerItem_notEmptyContext_sameItemName();
  void test_registerItem_afterDeleteItem();

  void test_deleteItem_nullParent();
  void test_deleteItem_notNullParent();

private:
  TreeContext* treeContext_;

};



#endif // TEST_ITEMMANAGER_H
