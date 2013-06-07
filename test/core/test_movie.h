#ifndef TEST_MOVIE_H
#define TEST_MOVIE_H

#include <cppunit/extensions/HelperMacros.h>

#include <stdexcept>

#include "movie.h"

using namespace std;

class TestMovie : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMovie);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_getSummary);
    CPPUNIT_TEST(test_getNotation);
    CPPUNIT_TEST(test_setSummary);
    CPPUNIT_TEST(test_setNotation);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void test_constructor();
    void test_getSummary();
    void test_getNotation();
    void test_setSummary();
    void test_setNotation();

private:
    Movie* movie1;
};

#endif // TEST_MOVIE_H
