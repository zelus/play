#ifndef TEST_ITEM_H
#define TEST_ITEM_H

#include <cppunit/extensions/HelperMacros.h>

#include <stdexcept>

#include "Item.h"
#include "Folder.h"
#include "Movie.h"
#include "Tag.h"

using namespace std;

class TestItem : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestItem);

  CPPUNIT_TEST(test_constructor_nullparent);
  CPPUNIT_TEST_EXCEPTION(test_constructor_itemparent,logic_error);
  CPPUNIT_TEST(test_constructor_folderparent);
  CPPUNIT_TEST_EXCEPTION(test_constructor_movieparent,logic_error);

  CPPUNIT_TEST(test_destructor);

  CPPUNIT_TEST(test_getParent);
  CPPUNIT_TEST(test_getParent_nullptr);

  CPPUNIT_TEST(test_getName);

  CPPUNIT_TEST(test_getType);

  CPPUNIT_TEST(test_setParent);
  CPPUNIT_TEST(test_setParent_nullptr);
  CPPUNIT_TEST(test_setParent_fromitemtoitem);

  CPPUNIT_TEST_EXCEPTION(test_addSubItem,logic_error);
  CPPUNIT_TEST_EXCEPTION(test_removeSubItem,logic_error);
  CPPUNIT_TEST_EXCEPTION(test_deleteSubItem,logic_error);
  CPPUNIT_TEST_EXCEPTION(test_getSubItem,logic_error);
  CPPUNIT_TEST_EXCEPTION(test_containsSubItem,logic_error);
  CPPUNIT_TEST_EXCEPTION(test_getAllSubItems,logic_error);

  CPPUNIT_TEST(test_addTag);
  CPPUNIT_TEST_EXCEPTION(test_addTag_doubleaddition,logic_error);
  CPPUNIT_TEST_EXCEPTION(test_addTag_evenregistered,logic_error);

  CPPUNIT_TEST(test_removeTag_existingtag);
  CPPUNIT_TEST_EXCEPTION(test_removeTag_nonexistingtag,logic_error);
  CPPUNIT_TEST_EXCEPTION(test_removeTag_unregisteredtag,logic_error);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void test_constructor_nullparent();
  void test_constructor_itemparent();
  void test_constructor_folderparent();
  void test_constructor_movieparent();

  void test_destructor();

  void test_getParent();
  void test_getParent_nullptr();

  void test_getName();

  void test_getType();

  void test_setParent();
  void test_setParent_nullptr();
  void test_setParent_fromitemtoitem();

  void test_addSubItem();
  void test_removeSubItem();
  void test_deleteSubItem();

  void test_getSubItem();
  void test_containsSubItem();
  void test_getAllSubItems();

  void test_addTag();
  void test_addTag_doubleaddition();
  void test_addTag_evenregistered();

  void test_removeTag_existingtag();
  void test_removeTag_nonexistingtag();
  void test_removeTag_unregisteredtag();

private:
  Folder* folder1;
  Folder* folder2;
  Item* item1;
  Item* item2;
  Tag* tag1;
  Tag* tag2;
};
#endif // TEST_ITEM_H
