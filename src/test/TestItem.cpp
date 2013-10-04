#include "TestItem.h"

#include "TreeContext.h"
#include "Folder.h"
#include "Movie.h"
#include "MockItem.h"

#include <string>
#include <vector>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);

void TestItem::setUp()
{
    folder1 = new Folder("folder1");
    folder2 = new Folder("folder2");
    item1 = new Movie("item1");
    item2 = new Movie("item2");
}

void TestItem::tearDown()
{

}

/*
  Constructor test with basic parameters.
  ID generation and default parent management are not tested in this test
  suite (see TestITemTree class for those tests).
 */
void TestItem::test_constructor_basic()
{
    string movie_name = "movie";
    item1 = new Movie(movie_name);
    CPPUNIT_ASSERT_MESSAGE("Wrong movie name", item1->getName() == movie_name);
}

/*
  Destructor test with nullptr as the Item parent.

  This test use MockItem to check if the Item destructor
  has been called.

  This test should never fail on its condition. It would only fail if
  an internal Item error occured.
 */
void TestItem::test_destructor_nullparent()
{
    bool is_deleted = false;
    MockItem* item = new MockItem("item",is_deleted);
    delete item;
    CPPUNIT_ASSERT_MESSAGE("The Item hasn't been deleted", is_deleted);
}

/*
  Destructor test with Folder registered as parent.
  Because tree consistency is not ensured by direct Item destructor
  the Folder child list is not updated.

  Folder child list is checked by size (cannot check by children IDs :
  the Folder contains an invalid pointer).
 */
void TestItem::test_destructor_folderparent()
{
    Item* folder = new Folder("folder");
    Item* item1 = new Movie("item1");
    Item* item2 = new Movie("item2");
    folder->addChild(item1);
    folder->addChild(item2);
    delete item1;
    CPPUNIT_ASSERT_MESSAGE("Folder has removed the deleted Item item1", folder->childCount() == 2);
    delete item2;
    CPPUNIT_ASSERT_MESSAGE("Folder has removed the deleted Item item2", folder->childCount() == 2);
}

/*
  getParent test with Folder as parent.
  Parent is tested by its ID.
 */
void TestItem::test_getParent()
{
    item1 = new Movie("item1");
    item1->setParent(folder1);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item parent", item1->getParent()->getId() == folder1->getId());
}

/*
  getParent test with nullptr as parent.
  Parent is tested by the pointer value.
 */
void TestItem::test_getParent_nullptr()
{
    item1 = new Movie("item1");
    item1->setParent(nullptr);
    CPPUNIT_ASSERT_MESSAGE("Item parent is different of nullptr", item1->getParent() == nullptr);
}

/*
  getId test with basic set ID.
  The test cannot be done on a new constructed Item : the construction delegates
  ID calculation to the context, which use setId method.
 */
void TestItem::test_getId()
{
    item1 = new Movie("item");
    string item_id = "item_id";
    item1->setId(item_id);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item Id", item1->getId() == item_id);
}

/*
  getId test after setName method call.
  The test is done by checking that the Id hasn't been updated
  in any way after setName method call (that would cause consistency
  problems : names doesn't have to be unique in a given context).
 */
void TestItem::test_getId_namechanged()
{
    item1 = new Movie("item");
    string item_id = "item_id";
    item1->setId(item_id);
    item1->setName("item2");
    CPPUNIT_ASSERT_MESSAGE("Consistency error : item ID has been updated", item1->getId() == item_id);
}

/*
  getId test after setParent method call
  The test is done by checking that the Id hasn't been updated
  in any way after setParent method call (that would cause consistency
  problems : names doesn't have to be unique in a given context).
 */
void TestItem::test_getId_parentchanged()
{
    item1 = new Movie("item");
    string item_id = "item_id";
    item1->setId(item_id);
    item1->setParent(folder1);
    CPPUNIT_ASSERT_MESSAGE("Consistency error : item ID has been updated", item1->getId() == item_id);
}

/*
  getName test.
 */
void TestItem::test_getName()
{
    string item_name = "item_name";
    item1 = new Movie(item_name);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item name", item1->getName() == item_name);
}

/*
  setParent test with any Item subclass as new parent (here Movie). Previous
  parent is nullptr.
  The test cannot be done on a new constructed Item : the construction delegates
  default parent assignment to the context, which use setParent method.
  Parent is tested by its ID. Parent child list consistency is not checked
  because setParent method doesn't ensure context consistency.
 */
void TestItem::test_setParent_fromnullptrtoitem()
{
    item1->setParent(nullptr);
    item1->setParent(item2);
    CPPUNIT_ASSERT_MESSAGE("Wrong parent Item", item1->getParent()->getId() == item2->getId());
}

/*
  setParent test with nullptr as new parent. Previous parent is any Item subclass
  (here Movie).
  The test cannot be done on a new constructed Item : the construction delegates
  default parent assignment to the context, which use setParent method.
  Parent is tested by its pointer value. Parent child list consistency is not checked
  because setParent method doesn't ensure context consistency.
 */
void TestItem::test_setParent_fromitemtonullptr()
{
    item1->setParent(item2);
    item1->setParent(nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong parent Item", item1->getParent() == nullptr);
}

/*
  setParent test with any Item subclass (here Folder) as new parent. Previous
  parent is any Item subclass (here Movie).
  The test cannot be done on a new constructed Item : the construction delegates
  default parent assignment to the context, which use setParent method.
  Parent is tested by its ID. Parent child list consistency is not checked
  because setParent method doesn't ensure context consistency.
 */
void TestItem::test_setParent_fromitemtoitem()
{
    item1->setParent(item2);
    item1->setParent(folder1);
    CPPUNIT_ASSERT_MESSAGE("Wrong parent Item", item1->getParent()->getId() == folder1->getId());
}

/*
  setName test.
 */
void TestItem::test_setName()
{
    item1 = new Movie("item");
    string item_name = "item2";
    item1->setName(item_name);
    CPPUNIT_ASSERT_MESSAGE("Item name hasn't been updated",item1->getName() == item_name);
}

/*
  addChild test.
  A core::IllegalOperationException is expected (Item cannot handle sub Items).
 */
void TestItem::test_addChild()
{
    item1->addChild(item2);
}

/*
  removeChild test.
  A core::IllegalOperationException is expected (Item cannot handle sub Items).
 */
void TestItem::test_removeChild()
{
    item1->removeChild(item2);
}

/*
  deleteChild test.
  A core::IllegalOperationException is expected (Item cannot handle sub Items).
 */
void TestItem::test_deleteChild()
{
    item1->deleteChild(item2);
}

/*
  getChild test.
  A core::IllegalOperationException is expected (Item cannot handle sub Items).
 */
void TestItem::test_getChild()
{
    item1->getChild("item2");
}

/*
  containsChild test.
  A core::IllegalOperationException is expected (Item cannot handle sub Items).
 */
void TestItem::test_containsChild()
{
    item1->containsChild("item2");
}

/*
  getChildIndex test.
  A core::IllegalOperationException is expected (Item cannot handle sub Items).
 */
void TestItem::test_getChildIndex()
{
    item1->getChildIndex(item2);
}

/*
  getAllChildren test.
  A core::IllegalOperationException is expected (Item cannot handle sub Items).
 */
void TestItem::test_getChildren()
{
    item1->getChildren();
}

/*
  childCount test.
  A core::IllegalOperationException is expected (Item cannot handle sub Items).
 */
void TestItem::test_childCount()
{
    item1->childCount();
}
