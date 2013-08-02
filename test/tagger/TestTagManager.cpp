#include "TestTagManager.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestTagManager);

void TestTagManager::setUp()
{
    tagManager_ = new TagManager<Item*>();
    tag1_ = new Tag<Item*>("tag1");
    tag2_ = new Tag<Item*>("tag2");
}

void TestTagManager::tearDown()
{
    delete tagManager_;
    // TODO add test to know if the others tag need to be deleted
}


void TestTagManager::test_destructor()
{
    MockTagManager* tag_manager = new MockTagManager();
    bool tag1_deleted = false;
    bool tag2_deleted = false;
    MockTag* mock1 = new MockTag("tag1",tag1_deleted);
    MockTag* mock2 = new MockTag("tag2",tag2_deleted);
    tag_manager->addTag(mock1);
    tag_manager->addTag(mock2);
    delete tag_manager;
    CPPUNIT_ASSERT_MESSAGE("tag1 hasn't been deleted",tag1_deleted);
    CPPUNIT_ASSERT_MESSAGE("tag2 hasn't been deleted",tag2_deleted);
}
