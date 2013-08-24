#include "TestItem.h"

#include "Folder.h"
#include "Movie.h"
#include <vector>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);

void TestItem::setUp()
{
    folder1 = new Folder("0","folder1",nullptr);
    folder2 = new Folder("1","folder2",nullptr);
    item1 = new Movie("2","item1",nullptr);
    item2 = new Movie("3","item2",nullptr);
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
    item1 = new Movie("2","item",nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item name", item1->getId() == "2");
    CPPUNIT_ASSERT_MESSAGE("Wrong Item type", item1->getType() == ItemType::MOVIE_TYPE);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent() == nullptr);
}

/*
  Constructor test with an Item object as parent.
  A core::CoreException is expected (basic Item cannot
  handle subItems)
 */
void TestItem::test_constructor_itemparent()
{
    item1 = new Movie("2","parent");
    item2 = new Movie("3","item",item1);
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
    item1 = new Movie("2","item",folder1);
    CPPUNIT_ASSERT_MESSAGE("Parent not set", item1->getParent() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong parent", item1->getParent()->getId() == folder1->getId());
}

/*
  Dectructor test with Items registered to a parent.

  Composite consistency is checked by the parent children list.
 */
void TestItem::test_destructor_folderparent()
{
    Item* folder = new Folder("folder","folder",nullptr);
    Item* item1 = new Movie("item1","item1",folder);
    Item* item2 = new Movie("item2","item2",folder);
    delete item1;
    CPPUNIT_ASSERT_MESSAGE("item1 hasn't been removed from its parent", !folder->containsSubItem("item1"));
    delete item2;
    CPPUNIT_ASSERT_MESSAGE("item2 hasn't been removed from its parent", !folder->containsSubItem("item2"));
    CPPUNIT_ASSERT_MESSAGE("folder is not empty", folder->getAllSubItems().size() == 0);
}

/*
  getParent test with a Folder object as parent.
  Parent is tested by its name.
 */
void TestItem::test_getParent()
{
    item1 = new Movie("2","item",folder1);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent()->getId() == folder1->getId());
}

/*
  getParent test with nullptr as parent.
 */
void TestItem::test_getParent_nullptr()
{
    item1 = new Movie("2","item",nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent() == nullptr);
}

/*
  getId test with basic constructed item.
 */
void TestItem::test_getId()
{
    item1 = new Movie("2","item",nullptr);
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
    item1 = new Movie("2","item",nullptr);
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
    item1 = new Movie("2","item",nullptr);
    item1->setParent(folder1);
    CPPUNIT_ASSERT_MESSAGE("Item Id has been updated (that should be impossible)", item1->getId() == "2");
}

/*
  getName test
 */
void TestItem::test_getName()
{
    item1 = new Movie("2","item");
    CPPUNIT_ASSERT_MESSAGE("Wrong Item name", item1->getName() == "item");
}

/*
  getType test
 */
void TestItem::test_getType()
{
    item1 = new Movie("2","item",nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item type", item1->getType() == ItemType::MOVIE_TYPE);
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
    item1 = new Movie("2","item",folder1);
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
    item1 = new Movie("2","item",folder1);
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
    item1 = new Movie("2","item",nullptr);
    item1->setName("item2");
    CPPUNIT_ASSERT_MESSAGE("Item name hasn't been updated",item1->getName() == "item2");
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
