#include "TestFolder.h"
#include "Folder.h"
#include "Movie.h"
#include "MockItem.h"
#include "MockItemVisitor.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestFolder);

void TestFolder::setUp()
{
    folder1 = new Folder("0","folder1",nullptr);
    item1 = new Movie("1","item1",nullptr);
    item2 = new Movie("2","item2",nullptr);
}

void TestFolder::tearDown()
{
    if(!folder1->containsSubItem(item1->getId())) {
        delete item1;
    }
    if(!folder1->containsSubItem(item2->getId())) {
        delete item2;
    }
    delete folder1;
}

/*
  Constructor test with basic parameters.
  Only check if the type of the Item is valid, other
  verifications are done in the TestItem class.
 */
void TestFolder::test_constructor()
{
    folder1 = new Folder("id","name",nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item type",folder1->getType() == ItemType::FOLDER_TYPE);
}

/*
  Destructor test with a Folder containing two Items.
  SubItem deletion checking is done with the MockItem
  mock : a boolean is setted to true if the Item mocked
  destructor has been called.
  No checking done to parent management, see TestItem class for
  those tests.
 */
void TestFolder::test_destructor()
{
    Item* folder = new Folder("3", "folder");
    bool item1Deleted = false;
    bool item2Deleted = false;
    new MockItem("4", "mockItem1",ItemType::ANY_TYPE,folder,item1Deleted);
    new MockItem("5", "mockItem2",ItemType::ANY_TYPE,folder,item2Deleted);
    delete folder;
    CPPUNIT_ASSERT_MESSAGE("item1 hasn't been deleted",item1Deleted);
    CPPUNIT_ASSERT_MESSAGE("item2 hasn't been deleted",item2Deleted);
}

/*
  addSubItem test. Folder consistency is checked by
  the folder size and the contain method. Item
  consistency is checked by the getParent method.
 */
void TestFolder::test_addSubItem()
{
    folder1->addSubItem(item1);
    folder1->addSubItem(item2);
    CPPUNIT_ASSERT_MESSAGE("folder doesn't contain the two items",folder1->getAllSubItems().size() == 2);
    CPPUNIT_ASSERT_MESSAGE("folder doesn't contain item1", folder1->containsSubItem("1"));
    CPPUNIT_ASSERT_MESSAGE("folder doesn't contain item2", folder1->containsSubItem("2"));
    CPPUNIT_ASSERT_MESSAGE("wrong item1 parent", item1->getParent()->getId() == "0");
    CPPUNIT_ASSERT_MESSAGE("wrong item2 parent", item2->getParent()->getId() == "0");
}

/*
  addSubItem test with addition of an Item already in the sub item list.
  A core::CoreException is expected (Folder cannot have the same child twice).
 */
void TestFolder::test_addSubItem_doubleaddition()
{
    folder1->addSubItem(item1);
    folder1->addSubItem(item1);
}

/*
  removeSubItem test with a valid Item to remove (the Folder
  contains the Item).
  Check done on Item parent and children ID for Folder.
 */
void TestFolder::test_removeSubItem()
{
    folder1->addSubItem(item1);
    folder1->addSubItem(item2);
    folder1->removeSubItem(item1);
    CPPUNIT_ASSERT_MESSAGE("Item1 doesn't have the right parent", item1->getParent() == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Folder's children list doesn't have the right size", folder1->getAllSubItems().size() == 1);
    CPPUNIT_ASSERT_MESSAGE("Folder's children list contains Item1", !folder1->containsSubItem(item1->getId()));
    CPPUNIT_ASSERT_MESSAGE("Folder's child list doesn't contain Item2", folder1->containsSubItem(item2->getId()));
}

/*
  removeSubItem test with an invalid Item to remove (the Folder
  doesn't contain the Item).
  A core::CoreException is expected (Folder cannot remove a child it doesn't
  contain).
 */
void TestFolder::test_removeSubItem_notchild()
{
    folder1->removeSubItem(item1);
}

/*
  deleteSubItem test with a valid Item to delete (the Folder
  contains the Item).
  Check done by using the MockItem class and children ID for Folder.
 */
void TestFolder::test_deleteSubItem()
{
    Item* folder = new Folder("folder","folder",nullptr);
    bool item1_deleted = false;
    bool item2_deleted = false;
    Item* item1 = new MockItem("mock1","mock1",ItemType::MOVIE_TYPE,folder,item1_deleted);
    new MockItem("mock2","mock2",ItemType::MOVIE_TYPE,folder,item2_deleted);
    folder->deleteSubItem(item1);
    CPPUNIT_ASSERT_MESSAGE("Item1 hasn't been deleted", item1_deleted);
    CPPUNIT_ASSERT_MESSAGE("Item2 has been deleted", !item2_deleted);
    CPPUNIT_ASSERT_MESSAGE("Folder's child list size doesn't have the right size", folder->getAllSubItems().size() == 1);
    CPPUNIT_ASSERT_MESSAGE("Folder contains Item1", !folder->containsSubItem("mock1"));
    CPPUNIT_ASSERT_MESSAGE("Folder doesn't contain Item2", folder->containsSubItem("mock2"));
    delete folder;
}

/*
  deleteSubItem test with an invalid Item to delete (the Folder
  doesn't contain the Item).
  A core::CoreException is expected (Folder cannot delete a child it doesn't
  contain).
 */
void TestFolder::test_deleteSubItem_notChild()
{
    folder1->deleteSubItem(item1);
}

/*
  getSubItem test with a valid Item to get (the Folder
  contains the Item).
  Check is done by comparing searched and base Item's ID.
 */
void TestFolder::test_getSubItem()
{
    folder1->addSubItem(item1);
    folder1->addSubItem(item2);
    Item* returned_item = folder1->getSubItem(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Returned Item is nullptr", returned_item != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item returned", returned_item->getId() == item1->getId());
}

/*
  getSubItem test with an invalid Item to get (the Folder
  doesn't contain the Item).
 */
void TestFolder::test_getSubItem_notchild()
{
    Item* returned_item = folder1->getSubItem(item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Returned Item is not nullptr", returned_item == nullptr);
}

/*
   containsSubItem test with a valid Item to look for (the Folder
   contains the Item).
  */
void TestFolder::test_containsSubItem()
{
    folder1->addSubItem(item1);
    folder1->addSubItem(item2);
    bool contained_item1 = folder1->containsSubItem(item1->getId());
    bool contained_item2 = folder1->containsSubItem(item2->getId());
    CPPUNIT_ASSERT_MESSAGE("Folder1 doesn't contain Item1", contained_item1);
    CPPUNIT_ASSERT_MESSAGE("Folder1 doesn't contain Item2", contained_item2);
}

/*
  containsSubItem test with an invalid Item to look for (the Folder
  doesn't contain the Item).
 */
void TestFolder::test_containsSubItem_notchild()
{
    bool contained_item1 = folder1->containsSubItem(item1->getId());
    bool contained_item2 = folder1->containsSubItem(item2->getId());
    CPPUNIT_ASSERT_MESSAGE("Folder1 contains Item1", !contained_item1);
    CPPUNIT_ASSERT_MESSAGE("Folder1 contains Item2", !contained_item2);
}

/*
  getAllSubItems test with a non empty children list.
  Check is done on returned vector size and Item's ID.
 */
void TestFolder::test_getAllSubItems()
{
    folder1->addSubItem(item1);
    folder1->addSubItem(item2);
    const vector<Item*>& all_sub_items = folder1->getAllSubItems();
    CPPUNIT_ASSERT_MESSAGE("Wrong returned vector size", all_sub_items.size() == 2);
    CPPUNIT_ASSERT_MESSAGE("First Item is not Item1", all_sub_items[0]->getId() == item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Second Item is not Item2", all_sub_items[1]->getId() == item2->getId());
}

/*
  getAllSubItems test with an empty children list.
  Check is done on returned vector size.
 */
void TestFolder::test_getAllSubItems_emptychildrenlist()
{
    const vector<Item*>& all_sub_items = folder1->getAllSubItems();
    CPPUNIT_ASSERT_MESSAGE("Returned vector is not empty", all_sub_items.empty());
}

/*
  accept test.
  Check is done by using a MockItemVisitor class
  that set an integer according to the method called.
  See MockItemVisitor constructor documentation for explanation
  about values given.
 */
void TestFolder::test_accept()
{
    int called_method = 0;
    MockItemVisitor* mock_visitor = new MockItemVisitor(called_method);
    folder1->accept(mock_visitor);
    CPPUNIT_ASSERT_MESSAGE("Wrong method called in Visitor", called_method == 1);
    delete mock_visitor;
}
