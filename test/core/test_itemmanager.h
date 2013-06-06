#ifndef TEST_ITEMMANAGER_H
#define TEST_ITEMMANAGER_H

#include <cppunit/extensions/HelperMacros.h>

#include <stdexcept>

using namespace std;

class TestItemManager : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestItemManager);
  CPPUNIT_TEST(testConstructor);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testConstructor();

};



#endif // TEST_ITEMMANAGER_H
