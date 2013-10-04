#ifndef TEST_ITEM_H
#define TEST_ITEM_H

#include <cppunit/extensions/HelperMacros.h>

#include "TreeContext.h"
#include "Item.h"
#include "IllegalOperationException.h"

#include <stdexcept>

using namespace std;
using namespace play_core;

class TestItem : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestItem);

  CPPUNIT_TEST(test_constructor_basic);

  CPPUNIT_TEST(test_destructor_nullparent);
  CPPUNIT_TEST(test_destructor_folderparent);

  CPPUNIT_TEST(test_getParent);
  CPPUNIT_TEST(test_getParent_nullptr);

  CPPUNIT_TEST(test_getId);
  CPPUNIT_TEST(test_getId_namechanged);
  CPPUNIT_TEST(test_getId_parentchanged);

  CPPUNIT_TEST(test_getName);

  CPPUNIT_TEST(test_setParent_fromnullptrtoitem);
  CPPUNIT_TEST(test_setParent_fromitemtonullptr);
  CPPUNIT_TEST(test_setParent_fromitemtoitem);

  CPPUNIT_TEST(test_setName);

  CPPUNIT_TEST_EXCEPTION(test_addChild,IllegalOperationException);
  CPPUNIT_TEST_EXCEPTION(test_removeChild,IllegalOperationException);
  CPPUNIT_TEST_EXCEPTION(test_deleteChild,IllegalOperationException);
  CPPUNIT_TEST_EXCEPTION(test_getChild,IllegalOperationException);
  CPPUNIT_TEST_EXCEPTION(test_containsChild,IllegalOperationException);
  CPPUNIT_TEST_EXCEPTION(test_getChildIndex,IllegalOperationException);
  CPPUNIT_TEST_EXCEPTION(test_getChildren,IllegalOperationException);
  CPPUNIT_TEST_EXCEPTION(test_childCount,IllegalOperationException);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void test_constructor_basic();
  void test_constructor_movieparent();
  void test_constructor_folderparent();
  void test_constructor_folderparent_evencontains();

  void test_destructor_nullparent();
  void test_destructor_folderparent();

  void test_getParent();
  void test_getParent_nullptr();

  void test_getId();
  void test_getId_namechanged();
  void test_getId_parentchanged();

  void test_getName();

  void test_getType();

  void test_setParent_fromnullptrtoitem();
  void test_setParent_fromitemtonullptr();
  void test_setParent_fromitemtoitem();

  void test_setName();

  void test_addChild();
  void test_removeChild();
  void test_deleteChild();
  void test_getChild();
  void test_containsChild();
  void test_getChildIndex();
  void test_getChildren();
  void test_childCount();

private:
  Item* folder1;
  Item* folder2;
  Item* item1;
  Item* item2;
};
#endif // TEST_ITEM_H
