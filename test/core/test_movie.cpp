#include "test_movie.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestMovie);

void TestMovie::setUp()
{
    movie1 = new Movie("movie1","summary",5,nullptr);
}

void TestMovie::tearDown()
{
    delete movie1;
}

/*
  Constructor test with basic parameters. Item specific
  inherited behavior is not tested, see TestItem
  for those tests.
 */
void TestMovie::test_constructor()
{
    movie1 = new Movie("movie1","summary_movie1", 2, nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong summary", movie1->getSummary() == "summary_movie1");
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == 2);
}

/*
  getSummary test.
 */
void TestMovie::test_getSummary()
{
    movie1 = new Movie("movie1","summary_movie1",2);
    CPPUNIT_ASSERT_MESSAGE("Wrong summary", movie1->getSummary() == "summary_movie1");
}

/*
  getNotation test.
 */
void TestMovie::test_getNotation()
{
    movie1 = new Movie("movie1","summary_movie1",2);
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == 2);
}

/*
  setParent test.
  Previous summary setUp summary ("summary").
 */
void TestMovie::test_setSummary()
{
    movie1->setSummary("new summary");
    CPPUNIT_ASSERT_MESSAGE("Wrong summary",movie1->getSummary() == "new summary");
}

/*
  setNotation test.
  Previous notation is setUp notation (5).
 */
void TestMovie::test_setNotation()
{
    movie1->setNotation(3);
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == 3);
}
