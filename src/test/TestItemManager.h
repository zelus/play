#ifndef TEST_ITEMMANAGER_H
#define TEST_ITEMMANAGER_H

#include <cppunit/extensions/HelperMacros.h>

#include "ItemManager.h"
#include <stdexcept>

using namespace std;

class TestItemManager : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestItemManager);
  CPPUNIT_TEST(test_constructor);

  CPPUNIT_TEST(test_createMovie);
  CPPUNIT_TEST(test_createMovie_nullparent);

  CPPUNIT_TEST(test_createItem_idunicity_doublecreation);
  CPPUNIT_TEST(test_createItem_idunicity_withdeletion);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void test_constructor();

  void test_createMovie();
  void test_createMovie_nullparent();

  void test_createItem_idunicity_doublecreation();
  void test_createItem_idunicity_withdeletion();

private:
  ItemManager* itemManager_;

};



#endif // TEST_ITEMMANAGER_H
