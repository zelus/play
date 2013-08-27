#include "TestMovie.h"
#include "MockItemVisitor.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(TestMovie);

void TestMovie::setUp()
{
    movie1 = new Movie("0","movie1");
}

void TestMovie::tearDown()
{
    delete movie1;
}

/*
  Constructor test with basic parameters. Item specific
  inherited behaviour is not tested, see TestItem
  for those tests.
 */
void TestMovie::test_constructor()
{
    movie1 = new Movie("0","movie1","summary_movie1",2);
    CPPUNIT_ASSERT_MESSAGE("Wrong summary", movie1->getSummary() == "summary_movie1");
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == 2);
    CPPUNIT_ASSERT_MESSAGE("Wrong ItemType", movie1->getType() == ItemType::MOVIE_TYPE);
}

/*
  Constructor test with default parameters. Item specific
  inherited behaviour is not tested, see TestItem for those
  tests.
 */
void TestMovie::test_constructor_defaultparameters()
{
    movie1 = new Movie("movie","name");
    CPPUNIT_ASSERT_MESSAGE("Wrong summary", movie1->getSummary() == "");
    CPPUNIT_ASSERT_MESSAGE("Wrong notation", movie1->getNotation() == 0);
    CPPUNIT_ASSERT_MESSAGE("Wrong ItemType", movie1->getType() == ItemType::MOVIE_TYPE);
}

/*
  getSummary test.
 */
void TestMovie::test_getSummary()
{
    movie1 = new Movie("0","movie1","summary_movie1",2);
    CPPUNIT_ASSERT_MESSAGE("Wrong summary", movie1->getSummary() == "summary_movie1");
}

/*
  getNotation test.
 */
void TestMovie::test_getNotation()
{
    movie1 = new Movie("0","movie1","summary_movie1",2);
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

/*
  accept test.
  Check is done by using a MockItemVisitor class
  that set an integer according to the method called.
  See MockItemVisitor constructor documentation for explanation
  about values given.
 */
void TestMovie::test_accept()
{
    int called_method = 0;
    MockItemVisitor* mock_visitor = new MockItemVisitor(called_method);
    movie1->accept(mock_visitor);
    CPPUNIT_ASSERT_MESSAGE("Wrong method called in Visitor", called_method == 2);
    delete mock_visitor;
}
