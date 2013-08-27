#ifndef TEST_ITEM_H
#define TEST_ITEM_H

#include <cppunit/extensions/HelperMacros.h>

#include "Item.h"
#include "CoreException.h"
#include "IllegalOperationException.h"
#include "InternalErrorException.h"

#include <stdexcept>

using namespace std;

class TestItem : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestItem);

  CPPUNIT_TEST(test_constructor_nullparent);
  CPPUNIT_TEST_EXCEPTION(test_constructor_movieparent,IllegalOperationException);
  CPPUNIT_TEST(test_constructor_folderparent);
  CPPUNIT_TEST_EXCEPTION(test_constructor_folderparent_evencontains,CoreException);

  CPPUNIT_TEST(test_destructor_nullparent);
  CPPUNIT_TEST(test_destructor_folderparent);

  CPPUNIT_TEST(test_getParent);
  CPPUNIT_TEST(test_getParent_nullptr);

  CPPUNIT_TEST(test_getId);
  CPPUNIT_TEST(test_getId_namechanged);
  CPPUNIT_TEST(test_getId_parentchanged);

  CPPUNIT_TEST(test_getName);

  CPPUNIT_TEST(test_getType);

  CPPUNIT_TEST(test_setParent_fromnulltofolder);
  CPPUNIT_TEST_EXCEPTION(test_setParent_fromnulltomovie,IllegalOperationException);
  CPPUNIT_TEST(test_setParent_fromnulltomovie_parentrestored);
  CPPUNIT_TEST(test_setParent_fromfoldertonull);
  CPPUNIT_TEST(test_setParent_fromfoldertofolder);
  CPPUNIT_TEST_EXCEPTION(test_setParent_fromfoldertomovie,IllegalOperationException);
  CPPUNIT_TEST(test_setParent_fromfoldertomovie_parentrestored);

  CPPUNIT_TEST(test_setName);

  CPPUNIT_TEST_EXCEPTION(test_addSubItem,CoreException);
  CPPUNIT_TEST_EXCEPTION(test_removeSubItem,CoreException);
  CPPUNIT_TEST_EXCEPTION(test_deleteSubItem,CoreException);
  CPPUNIT_TEST_EXCEPTION(test_getSubItem,CoreException);
  CPPUNIT_TEST_EXCEPTION(test_containsSubItem,CoreException);
  CPPUNIT_TEST_EXCEPTION(test_getAllSubItems,CoreException);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void test_constructor_nullparent();
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

  void test_setParent_fromnulltofolder();
  void test_setParent_fromnulltomovie();
  void test_setParent_fromnulltomovie_parentrestored();
  void test_setParent_fromfoldertonull();
  void test_setParent_fromfoldertofolder();
  void test_setParent_fromfoldertomovie();
  void test_setParent_fromfoldertomovie_parentrestored();

  void test_setName();

  void test_addSubItem();
  void test_removeSubItem();
  void test_deleteSubItem();

  void test_getSubItem();
  void test_containsSubItem();
  void test_getAllSubItems();

private:
  Item* folder1;
  Item* folder2;
  Item* item1;
  Item* item2;
};
#endif // TEST_ITEM_H
