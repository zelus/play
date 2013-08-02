#include "TestItem.h"

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);

void TestItem::setUp()
{
    folder1 = new Folder("folder1",nullptr);
    folder2 = new Folder("folder2",nullptr);
    item1 = new Item("item1",ANY_TYPE,nullptr);
    item2 = new Item("item2",ANY_TYPE,nullptr);
    tag1 = new Tag<Item*>("tag1");
    tag2 = new Tag<Item*>("tag2");
}

void TestItem::tearDown()
{
    if(!folder1->containsSubItem(item1->getName()) && !folder2->containsSubItem(item1->getName())) {
        delete item1;
    }
    if(!folder1->containsSubItem(item2->getName()) && !folder2->containsSubItem(item2->getName())) {
        delete item2;
    }
    delete folder1;
    delete folder2;
    delete tag1;
    delete tag2;
}

/*
  Constructor test with basic parameters. Parent is not
  tested.
 */
void TestItem::test_constructor_nullparent()
{
    item1 = new Item("item",ANY_TYPE,nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item name", item1->getName() == "item");
    CPPUNIT_ASSERT_MESSAGE("Wrong Item type", item1->getType() == ANY_TYPE);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent() == nullptr);
}

/*
  Constructor test with an Item object as parent.
  A std::logic_error is expected (Item cannot handle subItems)
 */
void TestItem::test_constructor_itemparent()
{
    item1 = new Item("parent");
    item2 = new Item("item",ANY_TYPE,item1);
}

/*
  Constructor test with a Folder object as parent.
  The subItems management behavior is not tested here, see
  TestFolder class for those tests.
  Parent is tested by its name (different pointers to the same
  object are allowed).
 */
void TestItem::test_constructor_folderparent()
{
    item1 = new Item("item",ANY_TYPE,folder1);
    CPPUNIT_ASSERT_MESSAGE("Parent not set", item1->getParent() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong parent", item1->getParent()->getName() == folder1->getName());
}

/*
  Constructor test with a Movie object as parent.
  A std::logic_error is expected (Movie cannot handle subItems)
 */
void TestItem::test_constructor_movieparent()
{
    Movie parent("parent");
    item1 = new Item("item1",ANY_TYPE,&parent);
}

/*
  Dectructor test with a Tag list containing two Tags.
  Item check is done by the registeredItems list size to
  avoid core dump during the test.
 */
void TestItem::test_destructor()
{
    Item* item = new Item("item");
    item->addTag(tag1);
    item->addTag(tag2);
    delete item;
    CPPUNIT_ASSERT_MESSAGE("Tag1 contains a reference to the Item", tag1->getRegisteredItemsNumber() == 0);
    CPPUNIT_ASSERT_MESSAGE("Tag2 contains a reference to the Item", tag2->getRegisteredItemsNumber() == 0);
}

/*
  getParent test with a Folder object as parent.
  Parent is tested by its name.
 */
void TestItem::test_getParent()
{
    item1 = new Item("item",ANY_TYPE,folder1);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent()->getName() == folder1->getName());
}

/*
  getParent test with nullptr as parent.
 */
void TestItem::test_getParent_nullptr()
{
    item1 = new Item("item",ANY_TYPE,nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent() == nullptr);
}

/*
  getName test
 */
void TestItem::test_getName()
{
    item1 = new Item("item");
    CPPUNIT_ASSERT_MESSAGE("Wrong Item name", item1->getName() == "item");
}

/*
  getType test
 */
void TestItem::test_getType()
{
    item1 = new Item("item",FOLDER_TYPE,nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item type", item1->getType() == FOLDER_TYPE);
}

/*
  setParent test with a Folder object as new parent.
  Previous parent is nullptr.
  Parent is tested by its name.
  Consistency of the parent childs list is not checked, see
  documentation.
 */
void TestItem::test_setParent()
{
    item1->setParent(folder1);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent()->getName() == folder1->getName());
}

/*
  setParent test with nullptr as new parent.
  Previous parent is a Folder object.
  Consistency of the parent childs list is not checked, see
  documentation.
 */
void TestItem::test_setParent_nullptr()
{
    item1 = new Item("item",ANY_TYPE,folder1);
    item1->setParent(nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent() == nullptr);
}

/*
  setParent test with a Folder object as new parent.
  Previous parent is an other Folder object.
  Consistency of the parent childs list is not checked, see
  documentation.
 */
void TestItem::test_setParent_fromitemtoitem()
{
    item1 = new Item("item",ANY_TYPE,folder1);
    item1->setParent(folder2);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent()->getName() == folder2->getName());
}

/*
  addSubItem test.
  A std::logic_error is expected (Item cannot handle subItems).
 */
void TestItem::test_addSubItem()
{
    item1->addSubItem(item2);
}

/*
  removeSubItem test.
  A std::logic_error is expected (Item cannot handle subItems).
 */
void TestItem::test_removeSubItem()
{
    item1->removeSubItem(item2);
}

/*
  deleteSubItem test.
  A std::logic_error is expected (Item cannot handle subItems).
 */
void TestItem::test_deleteSubItem()
{
    item1->deleteSubItem(item2);
}

/*
  getSubItem test.
  A std::logic_error is expected (Item cannot handle subItems).
 */
void TestItem::test_getSubItem()
{
    item1->getSubItem("item2");
}

/*
  containsSubItem test.
  A std::logic_error is expected (Item cannot handle subItems).
 */
void TestItem::test_containsSubItem()
{
    item1->containsSubItem("item2");
}

/*
  getAllSubItems test.
  A std::logic_error is expected (Item cannot handle subItems).
 */
void TestItem::test_getAllSubItems()
{
    item1->getAllSubItems();
}

/*
  addTag test with a new Tag (not even in the Tag list).
  Consistency of the related Tag registered Item list is
  not checked (see TestTag for those tests).
 */
void TestItem::test_addTag()
{
    item1->addTag(tag1);
    Item::TagList tagList = item1->getAllTags();
    bool containsTag = false;
    for(size_t i = 0; i < tagList.size(); ++i) {
        if(tagList[i]->getName() == tag1->getName()) {
            containsTag = true;
        }
    }
    CPPUNIT_ASSERT_MESSAGE("Item doesn't contain added Tag",containsTag);
}

/*
  addTag test with addition of a Tag already in the Tag list.
  A std::logic_error is expected (Item cannot have the same Tag
  twice).
 */
void TestItem::test_addTag_doubleaddition()
{
    item1->addTag(tag1);
    item1->addTag(tag1);
}

/*
  addTag test with addition of a Tag wich has the Item in its
  registered Item list.
  A std::logic_error is expected (The model is not consistent
  in that case).
 */
void TestItem::test_addTag_evenregistered()
{
    tag1->registerItem(item1);
    item1->addTag(tag1);
}

/*
  removeTag test with an existing Tag (previously added into
  the Tag list).
  Consistency of the related Tag registered Item list is
  not checked (see TestTag for those tests).
 */
void TestItem::test_removeTag_existingtag()
{
    item1->addTag(tag1);
    item1->removeTag(tag1);
    Item::TagList tagList = item1->getAllTags();
    bool containsTag = false;
    for(size_t i = 0; i < tagList.size(); ++i) {
        if(tagList[i]->getName() == tag1->getName()) {
            containsTag = true;
        }
    }
    CPPUNIT_ASSERT_MESSAGE("Item still contain removed Tag",!containsTag);
}

/*
  removeTag test with a non-existing Tag (not in the Tag List).
  A std::logic_error is expected (Item cannot remove a Tag it
  doesn't contain).
 */
void TestItem::test_removeTag_nonexistingtag()
{
    item1->removeTag(tag1);
}

/*
  removeTag test with removal of a Tag wich doesn't have
  the Item in its registered Item List.
  A std::logic_error is expected (The model is not consistent
  in that case).
 */
void TestItem::test_removeTag_unregisteredtag()
{
    item1->addTag(tag1);
    tag1->unregisterItem(item1);
    item1->removeTag(tag1);
}
