#include "TestMovie.h"
#include "MockItemVisitor.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(TestMovie);

void TestMovie::setUp()
{
    movie1 = new Movie("movie1");
}

void TestMovie::tearDown()
{
    delete movie1;
}

/*
  Base constructor test with basic parameters.
  Initialization is checked with summary and notation values.
  Name setting is not tested (see TestItem::test_constructor_basic
  for this test).
 */
void TestMovie::test_constructor_basic()
{
    movie1 = new Movie("movie");
    CPPUNIT_ASSERT_MESSAGE("Wrong summary", movie1->getSummary() == "");
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == 0);
}

/*
  Complete constructor test with basic parameters.
  Initialization is checked with summary and notation values.
  Name setting is not tested (see TestItem::test_constructor_basic
  for this test).
 */
void TestMovie::test_constructor_complete()
{
    string summary = "summary";
    short notation = 3;
    movie1 = new Movie("movie",summary,notation);
    CPPUNIT_ASSERT_MESSAGE("Wrong summary", movie1->getSummary() == summary);
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == notation);
}

/*
  getSummary test.
 */
void TestMovie::test_getSummary()
{
    string summary = "summary";
    movie1 = new Movie("movie",summary,2);
    CPPUNIT_ASSERT_MESSAGE("Wrong summary", movie1->getSummary() == summary);
}

/*
  getNotation test.
 */
void TestMovie::test_getNotation()
{
    short notation = 2;
    movie1 = new Movie("movie","sum",notation);
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == notation);
}

/*
  setSummary test.
 */
void TestMovie::test_setSummary()
{
    string new_summary = "new summary";
    movie1->setSummary(new_summary);
    CPPUNIT_ASSERT_MESSAGE("Wrong summary",movie1->getSummary() == new_summary);
}

/*
  setNotation test.
 */
void TestMovie::test_setNotation()
{
    short notation = 3;
    movie1->setNotation(notation);
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == notation);
}

/*
  accept test.
  Check is done by using a MockItemVisitor class that set an integer
  according to the method called.
  See MockItemVisitor constructor documentation for explanation
  about values given.
 */
void TestMovie::test_accept()
{
    int called_method = 0;
    MockItemVisitor mock_visitor(called_method);
    movie1->accept(mock_visitor);
    CPPUNIT_ASSERT_MESSAGE("Wrong method called in Visitor", called_method == 2);
}
