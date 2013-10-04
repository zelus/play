#include "TestFolder.h"
#include "Folder.h"
#include "Movie.h"
#include "MockItem.h"
#include "MockItemVisitor.h"

#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(TestFolder);

void TestFolder::setUp()
{
    folder1 = new Folder("folder1");
    item1 = new Movie("item1");
    item2 = new Movie("item2");
}

void TestFolder::tearDown()
{

}

/*
  Constructor test with basic parameters.
  Initialization is checked with the child list size.
  Name setting is not tested (see TestItem::test_constructor_basic
  for this test).
 */
void TestFolder::test_constructor_basic()
{
    folder1 = new Folder("folder1");
    CPPUNIT_ASSERT_MESSAGE("Wrong Item type",folder1->childCount() == 0);
}

/*
  Destructor test with a Folder containing two Items.
  Sub Item deletion checking is done with the MockItem mock : a boolean is
  setted to true if the Item mocked destructor has been called.
  Folder parent management is not tested (see TestItem::test_destructor_*
  for those tests).
 */
void TestFolder::test_destructor()
{
    Item* folder = new Folder("folder");
    bool item1Deleted = false;
    bool item2Deleted = false;
    folder->addChild(new MockItem("mockItem1",item1Deleted));
    folder->addChild(new MockItem("mockItem2",item2Deleted));
    delete folder;
    CPPUNIT_ASSERT_MESSAGE("item1 hasn't been deleted",item1Deleted);
    CPPUNIT_ASSERT_MESSAGE("item2 hasn't been deleted",item2Deleted);
}

/*
  addChild test with an initial empty Folder.
  Folder child list consistency is checked with the folder size and the
  contains method. Item parent consistency is checked by the getParent method.
 */
void TestFolder::test_addChild_emptyfolder()
{
    string item_id = "item1";
    item1->setId(item_id);
    folder1->addChild(item1);
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain the added Item",folder1->childCount() == 1);
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain item1", folder1->containsChild(item_id));
    CPPUNIT_ASSERT_MESSAGE("Wrong item1 parent", item1->getParent()->getId() == folder1->getId());
}

/*
  addChild test with an initial non-empty Folder.
  Folder child list consistency is checked with the folder size and the
  contains method. Item parent consistency is checked by the getParent method.
 */
void TestFolder::test_addChild_notemptyfolder()
{
    string item_id1 = "item1";
    string item_id2 = "item2";
    item1->setId(item_id1);
    item2->setId(item_id2);
    folder1->addChild(item1);
    folder1->addChild(item2);
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain the added Item", folder1->childCount() == 2);
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain item1", folder1->containsChild(item_id1));
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain item2", folder1->containsChild(item_id2));
    CPPUNIT_ASSERT_MESSAGE("Wrong item1 parent", item1->getParent()->getId() == folder1->getId());
    CPPUNIT_ASSERT_MESSAGE("Wrong item2 parent", item2->getParent()->getId() == folder1->getId());
}

/*
  addChild test with addition of an Item already in the child list (or
  an other Item with the same ID).
  A core::CoreException is expected (Folder cannot have the same child twice).
 */
void TestFolder::test_addChild_doubleaddition()
{
    folder1->addChild(item1);
    folder1->addChild(item1);
}

/*
  removeChild test with an initial empty Folder.
  A core::CoreException is expected (Folder cannot remove a child it doesn't
  handle).
 */
void TestFolder::test_removeChild_emptyfolder()
{
    folder1->removeChild(item1);
}

/*
  removeChild test with a folder containing a single Item in its child list.
  Folder child list consistency is checked with the folder size and the
  contains method. Item parent consistency is checked by the getParent method.
 */
void TestFolder::test_removeChild_singlechild()
{
    folder1->addChild(item1);
    size_t child_number = folder1->childCount();
    folder1->removeChild(item1);
    CPPUNIT_ASSERT_MESSAGE("Folder is not empty", folder1->childCount() == child_number - 1);
    CPPUNIT_ASSERT_MESSAGE("Folder contains the removed Item", !folder1->containsChild(item1->getId()));
    CPPUNIT_ASSERT_MESSAGE("Item's parent hasn't been reset", item1->getParent() == nullptr);
}

/*
  removeChild test with a folder containing several Item in its child list
  (here 2).
  Folder child list consistency is checked with the folder size and the contains
  method. Item parent consistency is checked by the getParent method.
 */
void TestFolder::test_removeChild_multiplechild()
{
    folder1->addChild(item1);
    folder1->addChild(item2);
    size_t child_number = folder1->childCount();
    folder1->removeChild(item1);
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain a single child", folder1->childCount() == child_number - 1);
    CPPUNIT_ASSERT_MESSAGE("Folder contains the first removed Item", !folder1->containsChild(item1->getId()));
    CPPUNIT_ASSERT_MESSAGE("First Item's parent hasn't been reset", item1->getParent() == nullptr);
    child_number--;
    folder1->removeChild(item2);
    CPPUNIT_ASSERT_MESSAGE("Folder isn't empty", folder1->childCount() == child_number - 1);
    CPPUNIT_ASSERT_MESSAGE("Folder contains the second removed Item", !folder1->containsChild(item2->getId()));
    CPPUNIT_ASSERT_MESSAGE("Second Item's parent hasn't been reset", item2->getParent() == nullptr);
}

/*
  removeChild test with an Item not handled by the Folder.
  A core::CoreException is expected (Folder cannot remove a child it doesn't
  handle).
 */
void TestFolder::test_removeChild_notchild()
{
    folder1->removeChild(item1);
}

/*
  deleteChild test with an initial empty Folder.
  A core::CoreException is expected (Folder cannot delete a child it doesn't
  handle).
 */
void TestFolder::test_deleteChild_emptyfolder()
{
    folder1->deleteChild(item1);
}

/*
  deleteChild test with a folder containing a single Item in its child list.
  Folder child list consistency is checked with the folder size and the
  contains method. Item deletion is checked with a MockItem object.
 */
void TestFolder::test_deleteChild_singlechild()
{
    bool item_deleted = false;
    MockItem* item = new MockItem("item",item_deleted);
    folder1->addChild(item);
    size_t child_number = folder1->childCount();
    folder1->deleteChild(item);
    CPPUNIT_ASSERT_MESSAGE("Folder is not empty", folder1->childCount() == child_number - 1);
    CPPUNIT_ASSERT_MESSAGE("Folder contains the removed Item", !folder1->containsChild(item->getId()));
    CPPUNIT_ASSERT_MESSAGE("Item hasn't been deleted", item_deleted);
}

/*
  deleteChild test with a folder containing several Item in its child list
  (here 2).
  Folder child list consistency is checked with the folder size and the contains
  method. Item deletion is checked with MockItem objects.
 */
void TestFolder::test_deleteChild_multiplechild()
{
    bool item1_deleted = false;
    bool item2_deleted = false;
    MockItem* item1 = new MockItem("item1",item1_deleted);
    MockItem* item2 = new MockItem("item2",item2_deleted);
    folder1->addChild(item1);
    folder1->addChild(item2);
    size_t child_number = folder1->childCount();
    folder1->deleteChild(item1);
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain a single child", folder1->childCount() == child_number - 1);
    CPPUNIT_ASSERT_MESSAGE("Folder contains the first deleted Item", !folder1->containsChild(item1->getId()));
    CPPUNIT_ASSERT_MESSAGE("Item1 hasn't been deleted", item1_deleted);
    child_number--;
    folder1->deleteChild(item2);
    CPPUNIT_ASSERT_MESSAGE("Folder isn't empty", folder1->childCount() == child_number - 1);
    CPPUNIT_ASSERT_MESSAGE("Folder contains the second deleted Item", !folder1->containsChild(item2->getId()));
    CPPUNIT_ASSERT_MESSAGE("Item2 hasn't been deleted", item2_deleted);
}

/*
  deleteChild test with an Item not handled by the Folder.
  A core::CoreException is expected (Folder cannot remove a child it doesn't
  handle).
 */
void TestFolder::test_deleteChild_notChild()
{
    folder1->deleteChild(item1);
}

/*
  getChild test with an initial empty Folder.
  Expected returned value is nullptr (default getChild method return).
 */
void TestFolder::test_getChild_emptyfolder()
{
    Item* found_item = folder1->getChild(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Returned Item is not nullptr", found_item == nullptr);
}

/*
  getChild test with a folder containing a single Item in its child list.
  Returned Item is checked with its ID.
 */
void TestFolder::test_getChild_singlechild()
{
    folder1->addChild(item1);
    Item* found_item = folder1->getChild(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Returned Item is nullptr", found_item != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item returned", found_item->getId() == item1->getId());
}

/*
  getChild test with a folder containing several Item in its child list
  (here 2).
  Returned Item is checked with its ID.
 */
void TestFolder::test_getChild_multiplechild()
{
    folder1->addChild(item1);
    folder1->addChild(item2);
    Item* found_item1 = folder1->getChild(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Returned Item(1) is nullptr", found_item1 != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item(1) returned", found_item1->getId() == item1->getId());
    Item* found_item2 = folder1->getChild(item2->getId());
    CPPUNIT_ASSERT_MESSAGE("Returned Item(2) is nullptr", found_item2 != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item(2) returned", found_item2->getId() == item2->getId());
}

/*
  getChild test with an Item not handled by the Folder.
  Expected returned value is nullptr (default getChild method return).
 */
void TestFolder::test_getChild_notchild()
{
    Item* returned_item = folder1->getChild(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Returned Item is not nullptr", returned_item == nullptr);
}

/*
  containsChild test with an initial empty Folder.
  Expected returned value is false (default containsChild method return).
 */
void TestFolder::test_containsChild_emptyfolder()
{
    bool contains_item = folder1->containsChild(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Folder contains the Item", !contains_item);
}

/*
  containsChild test with a folder containing a single Item in its child list.
  Expected returned value is true.
 */
void TestFolder::test_containsChild_singlechild()
{
    folder1->addChild(item1);
    bool contains_item = folder1->containsChild(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain the Item", contains_item);
}

/*
  containsChild test with a folder containing several Item in its child list
  (here 2).
  Expected returned value is true.
 */
void TestFolder::test_containsChild_multiplechild()
{
    folder1->addChild(item1);
    folder1->addChild(item2);
    bool contains_item1 = folder1->containsChild(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain the first Item", contains_item1);
    bool contains_item2 = folder1->containsChild(item2->getId());
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain the second Item", contains_item2);
}

/*
  containsChild test with an Item not handled by the Folder.
  Expected returned value is false (default containsChild method return).
 */
void TestFolder::test_containsChild_notchild()
{
    bool contained_item1 = folder1->containsChild(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Folder1 contains first Item", !contained_item1);
}

/*
  getChildIndex test with an initial empty Folder.
  Expected returned value is -1 (invalid index).
 */
void TestFolder::test_getChildIndex_emptyfolder()
{
    int found_index = folder1->getChildIndex(item1);
    CPPUNIT_ASSERT_MESSAGE("Index is not invalid", found_index == -1);
}

/*
  getChildIndex test with a folder containing a single Item in its child
  list.
  Expected returned value is 0 (the index of the first element).
 */
void TestFolder::test_getChildIndex_singlechild()
{
    folder1->addChild(item1);
    int found_index = folder1->getChildIndex(item1);
    CPPUNIT_ASSERT_MESSAGE("Wrong index returned", found_index == 0);
}

/*
  getChildIndex test with a folder containing several Item in its child
  list (here 2).
  Expected returned value is 0 (the index of the first element).
 */
void TestFolder::test_getChildIndex_multiplechild_first()
{
    folder1->addChild(item1);
    folder1->addChild(item2);
    int found_index_first = folder1->getChildIndex(item1);
    CPPUNIT_ASSERT_MESSAGE("Wrong index returned", found_index_first == 0);
}

/*
  getChildIndex test with a folder containing several Item in its child
  list (here 2).
  Expected returned value is 1 (the index of the last element).
 */
void TestFolder::test_getChildIndex_multiplechild_last()
{
    folder1->addChild(item1);
    folder1->addChild(item2);
    int found_index_last = folder1->getChildIndex(item2);
    CPPUNIT_ASSERT_MESSAGE("Wrong index returned", found_index_last == 1);
}

/*
  getChildIndex test with an Item not handled by the Folder.
  Expected returned value is -1 (invalid index).
 */
void TestFolder::test_getChildIndex_notchild()
{
    folder1->addChild(item1);
    int found_index = folder1->getChildIndex(item2);
    CPPUNIT_ASSERT_MESSAGE("Index is not invalid", found_index == -1);
}

/*
  getChildren test with an initial empty Folder.
  Expected returned value is an empty vector.
 */
void TestFolder::test_getChildren_emptyfolder()
{
    const vector<Item*>& all_sub_items = folder1->getChildren();
    CPPUNIT_ASSERT_MESSAGE("Returned vector is not empty", all_sub_items.empty());
}

/*
  getChildren test with a folder containing a single Item in its child
  list.
  Expected returned value is a vector containing the only Folder's child.
  Child is checked with its ID.
 */
void TestFolder::test_getChildren_singlechild()
{
    folder1->addChild(item1);
    const vector<Item*>& all_sub_items = folder1->getChildren();
    CPPUNIT_ASSERT_MESSAGE("Returned vector is empty", !all_sub_items.empty());
    CPPUNIT_ASSERT_MESSAGE("Wrong vector size", all_sub_items.size() == 1);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item in returned vector", all_sub_items[0]->getId() == item1->getId());
}

/*
  getChildren test with a folder containing several Item in its child
  list (here 2).
  Expected returned value is a vector containing the 2 Folder's children.
  Children are checked with their ID.
 */
void TestFolder::test_getChildren_multiplechild()
{
    folder1->addChild(item1);
    folder1->addChild(item2);
    const vector<Item*>& all_sub_items = folder1->getChildren();
    CPPUNIT_ASSERT_MESSAGE("Returned vector is empty", !all_sub_items.empty());
    CPPUNIT_ASSERT_MESSAGE("Wrong vector size", all_sub_items.size() == 2);
    CPPUNIT_ASSERT_MESSAGE("Wrong first Item in returned vector", all_sub_items[0]->getId() == item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Wrong second Item in returned vector", all_sub_items[1]->getId() == item2->getId());
}

/*
  childCount test with an initial empty Folder.
  Expected returned value is 0.
 */
void TestFolder::test_childCount_emptyfolder()
{
    size_t child_number = folder1->childCount();
    CPPUNIT_ASSERT_MESSAGE("Invalid sub Item number", child_number == 0);
}

/*
  childCount test with a folder containing a single Item in its child
  list.
  Expected returned value is 1.
 */
void TestFolder::test_childCount_singlechild()
{
    folder1->addChild(item1);
    size_t child_number = folder1->childCount();
    CPPUNIT_ASSERT_MESSAGE("Invalid sub Item number", child_number == 1);
}

/*
  childCount test with a folder containing several Item in its child
  list (here 2).
  Expected returned value is 2.
 */
void TestFolder::test_childCount_multiplechild()
{
    folder1->addChild(item1);
    folder1->addChild(item2);
    size_t child_number = folder1->childCount();
    CPPUNIT_ASSERT_MESSAGE("Invalid sub Itme number", child_number == 2);
}

/*
  accept test.
  Check is done by using a MockItemVisitor class that sets an integer
  according to the method called.
  See MockItemVisitor constructor documentation for explanation
  about values given.
 */
void TestFolder::test_accept()
{
    int called_method = 0;
    MockItemVisitor mock_visitor(called_method);
    folder1->accept(mock_visitor);
    CPPUNIT_ASSERT_MESSAGE("Wrong method called in Visitor", called_method == 1);
}
