#ifndef TESTIDITEMSEARCHER_H
#define TESTIDITEMSEARCHER_H

#include <cppunit/extensions/HelperMacros.h>

#include "IdItemSearcher.h"

class TestIdItemSearcher : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestIdItemSearcher);

  CPPUNIT_TEST(test_constructor);

  CPPUNIT_TEST(test_search_movieexistingid);
  CPPUNIT_TEST(test_search_folderexistingid);
  CPPUNIT_TEST(test_search_movienonexistingid);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void test_constructor();

  void test_search_movieexistingid();
  void test_search_folderexistingid();
  void test_search_movienonexistingid();

private:
  Item* root_;
  Item* item1_;
  Item* subFolder1_;
  Item* item2_;
  Item* item3_;
};

#endif // TESTIDITEMSEARCHER_H
