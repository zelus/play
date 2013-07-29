#include "TestTag.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestTag);

void TestTag::setUp()
{
    item1_ = new Item("item1");
    tag1_ = new Tag<Item*>("tag1");
}

void TestTag::tearDown()
{
    delete tag1_;
    delete item1_;
}

void TestTag::test_constructor()
{
    CPPUNIT_ASSERT_MESSAGE("Wrong Tag name",tag1_->getName() == "tag1");
}
