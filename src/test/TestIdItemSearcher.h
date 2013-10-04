#ifndef TESTIDITEMSEARCHER_H
#define TESTIDITEMSEARCHER_H

#include <cppunit/extensions/HelperMacros.h>

#include "TreeContext.h"
#include "IdItemSearcher.h"

using namespace play_core;

class TestIdItemSearcher : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestIdItemSearcher);

  CPPUNIT_TEST(test_constructor_basic);

  CPPUNIT_TEST(test_search_existingid_fromroot);
  CPPUNIT_TEST(test_search_nonexistingid_fromroot);

  CPPUNIT_TEST(test_search_existingid_fromlevel1);
  CPPUNIT_TEST(test_search_nonexistingid_fromlevel1);
  CPPUNIT_TEST(test_search_upperexistingid_fromlevel1);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void test_constructor_basic();

  void test_search_existingid_fromroot();
  void test_search_nonexistingid_fromroot();

  void test_search_existingid_fromlevel1();
  void test_search_nonexistingid_fromlevel1();
  void test_search_upperexistingid_fromlevel1();

private:
  Item* root_;
  Item* item1_;
  Item* subFolder1_;
  Item* item2_;
  Item* item3_;
};

#endif // TESTIDITEMSEARCHER_H
