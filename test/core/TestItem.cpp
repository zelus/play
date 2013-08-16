#include "TestItem.h"

#include <vector>
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
    tagManager = new TagManager<Item*>();
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
  A core::CoreException is expected (basic Item cannot
  handle subItems)
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
  A core::CoreException is expected (Movie cannot
  handle subItems)
 */
void TestItem::test_constructor_movieparent()
{
    Movie parent("parent");
    item1 = new Item("item1",ANY_TYPE,&parent);
}

/*
  Constructor test with a TagManager associated to the Item.
  Tag consistency is checked by the TagManager::constainsTag method
  and the registered Item list returned by the Tag.
 */
void TestItem::test_constructor_tagManager()
{
    item1 = new Item("item1",ANY_TYPE,nullptr,tagManager);
    CPPUNIT_ASSERT_MESSAGE("TagManager's Tag list is empty",tagManager->getTagsNumber() == 1);
    CPPUNIT_ASSERT_MESSAGE("TagManager doesn't contain the Tag \"item1\"",tagManager->containsTag("item1"));
    CPPUNIT_ASSERT_MESSAGE("Tag \"item1\" doesn't contain a reference to the Item", tagManager->getTag("item1")->getRegisteredItemsNumber() == 1 && tagManager->getTag("item1")->getRegisteredItems()[Item::name_priority][0]->getId() == item1->getId());
}

/*
  Dectructor test with a Tag list containing two Tags.
  Consistency relative to TagManager is checked by a double creation
  of Items with similar Tags followed by the deletion of one.
  The Tags corresponding to the Item deleted are retrieved from the
  TagManager and comparison is done on registred Item number and id of
  the Item remaining.

  The double creation is necessary because the TagManager deletes Tags that
  have no registered Items.
 */
void TestItem::test_destructor()
{
    Item* item = new Item("item tag",ANY_TYPE,nullptr,tagManager);
    Item* item1 = new Item("item tag test",ANY_TYPE,nullptr,tagManager);
    delete item;
    Tag<Item*>* tag1 = tagManager->getTag("item");
    Tag<Item*>* tag2 = tagManager->getTag("tag");
    CPPUNIT_ASSERT_MESSAGE("Tag \"item\" has not the right number of Item references", tag1->getRegisteredItemsNumber() == 1);
    CPPUNIT_ASSERT_MESSAGE("Tag \"tag\" has not the right number of Item references", tag2->getRegisteredItemsNumber() == 1);
    CPPUNIT_ASSERT_MESSAGE("Tag \"item\" contains a reference to the Item", tag1->getRegisteredItems()[Item::name_priority][0]->getId() == item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Tag \"tag\" contains a reference to the Item", tag2->getRegisteredItems()[Item::name_priority][0]->getId() == item1->getId());
    delete item1;
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

void TestItem::test_getId()
{

}

void TestItem::test_getId_namechanged()
{

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
  setName test with a valid new name.
  Tag consistency is checked through the TagManager::containsTag method
  and the registered Item list returned by the Tag.
 */
void TestItem::test_setName()
{
    item1 = new Item("item",ANY_TYPE,nullptr,tagManager);
    item1->setName("item2");
    CPPUNIT_ASSERT_MESSAGE("Item name hasn't been updated", item1->getName() == "item2");
    CPPUNIT_ASSERT_MESSAGE("Tag \"item\" hasn't been deleted", tagManager->containsTag("item") == false);
    CPPUNIT_ASSERT_MESSAGE("Tag \"item2\" hasn't been created", tagManager->containsTag("item2"));
    CPPUNIT_ASSERT_MESSAGE("Tag \"item2\" doesn't contain a reference to the Item", tagManager->getTag("item2")->getRegisteredItemsNumber() == 1 && tagManager->getTag("item2")->getRegisteredItems()[Item::name_priority][0]->getId() == item1->getId());
}

/*
  addSubItem test.
  A core::CoreException is expected (Item cannot handle subItems).
 */
void TestItem::test_addSubItem()
{
    item1->addSubItem(item2);
}

/*
  removeSubItem test.
  A core::CoreException is expected (Item cannot handle subItems).
 */
void TestItem::test_removeSubItem()
{
    item1->removeSubItem(item2);
}

/*
  deleteSubItem test.
  A core::CoreException is expected (Item cannot handle subItems).
 */
void TestItem::test_deleteSubItem()
{
    item1->deleteSubItem(item2);
}

/*
  getSubItem test.
  A core::CoreException is expected (Item cannot handle subItems).
 */
void TestItem::test_getSubItem()
{
    item1->getSubItem("item2");
}

/*
  containsSubItem test.
  A core::CoreException is expected (Item cannot handle subItems).
 */
void TestItem::test_containsSubItem()
{
    item1->containsSubItem("item2");
}

/*
  getAllSubItems test.
  A core::CoreException is expected (Item cannot handle subItems).
 */
void TestItem::test_getAllSubItems()
{
    item1->getAllSubItems();
}
