#include "TestItem.h"

#include "Folder.h"
#include <vector>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);

void TestItem::setUp()
{
    folder1 = new Folder("0","folder1",nullptr);
    folder2 = new Folder("1","folder2",nullptr);
    item1 = new Item("2","item1",ItemType::ANY_TYPE,nullptr);
    item2 = new Item("3","item2",ItemType::ANY_TYPE,nullptr);
}

void TestItem::tearDown()
{
    if(!folder1->containsSubItem(item1->getId()) && !folder2->containsSubItem(item1->getId())) {
        delete item1;
    }
    if(!folder1->containsSubItem(item2->getId()) && !folder2->containsSubItem(item2->getId())) {
        delete item2;
    }
    delete folder1;
    delete folder2;
}

/*
  Constructor test with basic parameters. Parent is not
  tested.
 */
void TestItem::test_constructor_nullparent()
{
    item1 = new Item("2","item",ItemType::ANY_TYPE,nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item name", item1->getId() == "2");
    CPPUNIT_ASSERT_MESSAGE("Wrong Item type", item1->getType() == ItemType::ANY_TYPE);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent() == nullptr);
}

/*
  Constructor test with an Item object as parent.
  A core::CoreException is expected (basic Item cannot
  handle subItems)
 */
void TestItem::test_constructor_itemparent()
{
    item1 = new Item("2","parent");
    item2 = new Item("3","item",ItemType::ANY_TYPE,item1);
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
    item1 = new Item("2","item",ItemType::ANY_TYPE,folder1);
    CPPUNIT_ASSERT_MESSAGE("Parent not set", item1->getParent() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong parent", item1->getParent()->getId() == folder1->getId());
}

/*
  Constructor test with a Movie object as parent.
  A core::CoreException is expected (Movie cannot
  handle subItems)
 */
void TestItem::test_constructor_movieparent()
{
    Item parent("5","parent");
    item1 = new Item("2","item1",ItemType::ANY_TYPE,&parent);
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
    Item* item = new Item("5","item tag",ItemType::ANY_TYPE,nullptr);
    Item* item1 = new Item("6","item tag test",ItemType::ANY_TYPE,nullptr);
    delete item;
    delete item1;
}

/*
  getParent test with a Folder object as parent.
  Parent is tested by its name.
 */
void TestItem::test_getParent()
{
    item1 = new Item("2","item",ItemType::ANY_TYPE,folder1);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent()->getId() == folder1->getId());
}

/*
  getParent test with nullptr as parent.
 */
void TestItem::test_getParent_nullptr()
{
    item1 = new Item("2","item",ItemType::ANY_TYPE,nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent() == nullptr);
}

/*
  getId test with basic constructed item.
 */
void TestItem::test_getId()
{
    item1 = new Item("2","item",ItemType::ANY_TYPE,nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item Id", item1->getId() == "2");
}

/*
  getId test with a setName method call
  The test is done by checking that the Id hasn't been updated
  in any way after the setName call (that would cause consistency
  errors : two items with different ID may have the same ID after a call
  to setName method).
 */
void TestItem::test_getId_namechanged()
{
    item1 = new Item("2","item",ItemType::ANY_TYPE,nullptr);
    item1->setName("item2");
    CPPUNIT_ASSERT_MESSAGE("Item Id has been updated (that should be impossible)", item1->getId() == "2");
}

/*
  getId test with a setParent method call
  The test is done by checking that the Id hasn't been updated
  in any way after the setParent call (that would cause consistency
  errors : two items with different ID may have the same ID after a call
  to setParent method).
 */
void TestItem::test_getId_parentchanged()
{
    item1 = new Item("2","item",ItemType::ANY_TYPE,nullptr);
    item1->setParent(folder1);
    CPPUNIT_ASSERT_MESSAGE("Item Id has been updated (that should be impossible)", item1->getId() == "2");
}

/*
  getName test
 */
void TestItem::test_getName()
{
    item1 = new Item("2","item");
    CPPUNIT_ASSERT_MESSAGE("Wrong Item name", item1->getName() == "item");
}

/*
  getType test
 */
void TestItem::test_getType()
{
    item1 = new Item("2","item",ItemType::FOLDER_TYPE,nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item type", item1->getType() == ItemType::FOLDER_TYPE);
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
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent()->getId() == folder1->getId());
}

/*
  setParent test with nullptr as new parent.
  Previous parent is a Folder object.
  Consistency of the parent childs list is not checked, see
  documentation.
 */
void TestItem::test_setParent_nullptr()
{
    item1 = new Item("2","item",ItemType::ANY_TYPE,folder1);
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
    item1 = new Item("2","item",ItemType::ANY_TYPE,folder1);
    item1->setParent(folder2);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent()->getId() == folder2->getId());
}

/*
  setName test with a valid new name.
  Tag consistency is checked through the TagManager::containsTag method
  and the registered Item list returned by the Tag.
 */
void TestItem::test_setName()
{
    item1 = new Item("2","item",ItemType::ANY_TYPE,nullptr);
    item1->setName("item2");
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
