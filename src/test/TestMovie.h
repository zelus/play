#ifndef TEST_MOVIE_H
#define TEST_MOVIE_H

#include <cppunit/extensions/HelperMacros.h>
#include "TreeContext.h"
#include "Item.h"
#include "Movie.h"

using namespace play_core;

class TestMovie : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMovie);

    CPPUNIT_TEST(test_constructor_basic);
    CPPUNIT_TEST(test_constructor_complete);

    CPPUNIT_TEST(test_getSummary);

    CPPUNIT_TEST(test_getNotation);

    CPPUNIT_TEST(test_setSummary);

    CPPUNIT_TEST(test_setNotation);

    CPPUNIT_TEST(test_accept);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void test_constructor_basic();
    void test_constructor_complete();

    void test_getSummary();

    void test_getNotation();

    void test_setSummary();

    void test_setNotation();

    void test_accept();

private:
    Movie* movie1;
};

#endif // TEST_MOVIE_H
