#include "TestTreeContext.h"
#include "Movie.h"
#include "Folder.h"
#include "MockItem.h"
#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION(TestTreeContext);

void TestTreeContext::setUp()
{
    treeContext_ = new TreeContext();
}

void TestTreeContext::tearDown()
{
    delete treeContext_;
}

/*
  constructor test.
  Initialization is checked on the tree root pointer.
 */
void TestTreeContext::test_constructor_basic()
{
    TreeContext* tree_context = new TreeContext();
    CPPUNIT_ASSERT_MESSAGE("Tree root is nullptr", tree_context->getRootItem() != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Tree root name is not _root_", tree_context->getRootItem()->getName() == "_root_");
    CPPUNIT_ASSERT_MESSAGE("Tree root ID is not 0", tree_context->getRootItem()->getId() == "0");
    CPPUNIT_ASSERT_MESSAGE("Tree root parent is not nullptr", tree_context->getRootItem()->getParent() == nullptr);
    CPPUNIT_ASSERT_MESSAGE("Top level Item list number not empty", tree_context->getTopLevelItemCount() == 0);
}

/*
  destructor test on an empty root Item is not possible because it is not
  possible to set the root Item of the TreeContext (which make impossible the
  use of a MockItem to check the deletion).
 */

/*
  destructor test with a root containing a single Item in its child list.

  This test use MockItem to check if the root child Item destructor has been
  called.
 */
void TestTreeContext::test_destructor_singleChildInRoot()
{
    TreeContext* tree_context = new TreeContext();
    bool item_deleted = false;
    MockItem* item = new MockItem("item1",item_deleted);
    tree_context->registerItem(item);
    tree_context->addTopLevelItem(item);
    delete tree_context;
    CPPUNIT_ASSERT_MESSAGE("Root child Item hasn't been deleted", item_deleted);
}

/*
  destructor test with a root containing several Item in its child list
  (here 2).

  This test use MockItem to check if the root children Items destructor has
  been called.
 */
void TestTreeContext::test_destructor_multipleChildrenInRoot()
{
    TreeContext* tree_context = new TreeContext();
    bool item1_deleted = false;
    bool item2_deleted = false;
    MockItem* item1 = new MockItem("item1",item1_deleted);
    MockItem* item2 = new MockItem("item2",item2_deleted);
    tree_context->registerItem(item1);
    tree_context->registerItem(item2);
    tree_context->addTopLevelItem(item1);
    tree_context->addTopLevelItem(item2);
    delete tree_context;
    CPPUNIT_ASSERT_MESSAGE("Root child item1 hasn't been deleted", item1_deleted);
    CPPUNIT_ASSERT_MESSAGE("Root child item2 hasn't been deleted", item2_deleted);
}

/*
  getRootItem test.
  Root Item is tested on its ID, name and parent.
 */
void TestTreeContext::test_getRootItem()
{
    const Item* tree_root = treeContext_->getRootItem();
    CPPUNIT_ASSERT_MESSAGE("Tree root is nullptr", tree_root != nullptr);
    CPPUNIT_ASSERT_MESSAGE("Tree root ID is not 0", tree_root->getId() == "0");
    CPPUNIT_ASSERT_MESSAGE("Tree root parent is not nullptr", tree_root->getParent() == nullptr);
}

/*
  getTopLevelItems test with an empty root child list.
  The test is done on the root child list size.
 */
void TestTreeContext::test_getTopLevelItems_emptyRoot()
{
    const vector<Item*>& top_items = treeContext_->getTopLevelItems();
    CPPUNIT_ASSERT_MESSAGE("Top level Item vector is not empty", top_items.empty());
}

/*
  getTopLevelItems test with a root containing a single Item in its child list.
  Root list consistency is checked with the root size and the child ID.
 */
void TestTreeContext::test_getTopLevelItems_singleChildInRoot()
{
    Item* item1 = new Movie("item1");
    treeContext_->registerItem(item1);
    treeContext_->addTopLevelItem(item1);
    const vector<Item*>& top_items = treeContext_->getTopLevelItems();
    CPPUNIT_ASSERT_MESSAGE("Top level Item vector is empty", !top_items.empty());
    CPPUNIT_ASSERT_MESSAGE("Top level Item vector contains more than one Item", top_items.size() == 1);
    CPPUNIT_ASSERT_MESSAGE("Wrong contained Item",top_items[0]->getId() == item1->getId());
}

/*
  getTopLevelItems test with a root containing several Item in its child list
  (here 2).
  Root list consistency is checked with the root size and the children IDs.
 */
void TestTreeContext::test_getTopLevelItems_multipleChildrenInRoot()
{
    Item* item1 = new Movie("item1");
    Item* item2 = new Movie("item2");
    treeContext_->registerItem(item1);
    treeContext_->registerItem(item2);
    treeContext_->addTopLevelItem(item1);
    treeContext_->addTopLevelItem(item2);
    const vector<Item*>& top_items = treeContext_->getTopLevelItems();
    CPPUNIT_ASSERT_MESSAGE("Top level Item vector is empty", !top_items.empty());
    CPPUNIT_ASSERT_MESSAGE("Top level Item vector contains a single Item", top_items.size() > 1);
    CPPUNIT_ASSERT_MESSAGE("Top level Item vector contains more than two Items", top_items.size() == 2);
    CPPUNIT_ASSERT_MESSAGE("Wrong first contained Item", top_items[0]->getId() == item1->getId());
    CPPUNIT_ASSERT_MESSAGE("Wrong second contained Item", top_items[1]->getId() == item2->getId());
}

/*
  getTopLevelItemCount test with an empty root child list.
  Expected returned value is 0.
 */
void TestTreeContext::test_getTopLevelItemCount_emptyRoot()
{
    CPPUNIT_ASSERT_MESSAGE("Wrong Item count", treeContext_->getTopLevelItemCount() == 0);
}

/*
  getTopLevelItemCount test with a root containing a single Item in its child
  list.
  Expected returned value is 1.
 */
void TestTreeContext::test_getTopLevelItemCount_singleChildInRoot()
{
    Item* item = new Movie("item");
    treeContext_->registerItem(item);
    treeContext_->addTopLevelItem(item);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item count", treeContext_->getTopLevelItemCount() == 1);
}

/*
  getTopLevelItemCount test with a root containing several Item in its child
  list (here 2).
  Expected returned value is 2.
 */
void TestTreeContext::test_getTopLevelItemCount_multipleChildrenInRoot()
{
    Item* item1 = new Movie("item1");
    Item* item2 = new Movie("item2");
    treeContext_->registerItem(item1);
    treeContext_->registerItem(item2);
    treeContext_->addTopLevelItem(item1);
    treeContext_->addTopLevelItem(item2);
    CPPUNIT_ASSERT_MESSAGE("Wrong Item count", treeContext_->getTopLevelItemCount() == 2);
}

/*
  There are no test to do about adding a top level Item in an empty (or not)
  root or check double addition because this method is a convenience method
  that wrap a delegate call to Folder::removeSubItem and Folder::addSubItem.
  See this test cases for those results.

  The tests below are about parent (previous and new) consistency, which is
  not ensured by both Folder::removeSubItem and Folder::addSubItem.
 */

/*
  addTopLevelItem test with an Item which doesn't have a parent set (nullptr).
  Item parent consistency is checked with the getParent method.
  Root child list consistency is checked with the containsChild method.
 */
void TestTreeContext::test_addTopLevelItem_nullParent()
{
    Item* item = new Movie("item");
    const Item* tree_root = treeContext_->getRootItem();
    treeContext_->registerItem(item);
    treeContext_->addTopLevelItem(item);
    CPPUNIT_ASSERT_MESSAGE("Wrong new Item parent", item->getParent()->getId() == tree_root->getId());
    CPPUNIT_ASSERT_MESSAGE("Root Item doesn't contain the added Item", tree_root->containsChild(item->getId()));
}

/*
  addTopLevelItem test with an Item which has a parent set, but this parent
  is not registered to the Item's context.
  Item parent consistency is checked with the getParent method.
  Root child list consistency is checked with the containsChild method.
  Previous Item's parent child list consistency is checked with the
  childCount and containsChild method.
 */
void TestTreeContext::test_addTopLevelItem_notNullParent_notInContext()
{
    Item* previous_parent = new Folder("folder");
    Item* item = new Movie("item");
    previous_parent->addChild(item);
    const Item* tree_root = treeContext_->getRootItem();
    treeContext_->registerItem(item);
    treeContext_->addTopLevelItem(item);
    CPPUNIT_ASSERT_MESSAGE("Wrong new Item parent", item->getParent()->getId() == tree_root->getId());
    CPPUNIT_ASSERT_MESSAGE("Root Item doesn't contain the added Item", tree_root->containsChild(item->getId()));
    CPPUNIT_ASSERT_MESSAGE("Item hasn't been erased of its previous parent child list", previous_parent->childCount() == 0);
}

/*
  addTopLevelItem test with an Item which has a parent set, and this parent
  is registered to the Item's context.
  Item parent consistency is checked with the getParent method.
  Root child list consistency is checked with the constainsChild method.
  Previous Item's parent child list consistency is checked with the
  childCount and constainsChild methods.
 */
void TestTreeContext::test_addTopLevelItem_notNullParent_inContext()
{
    Item* previous_parent = new Folder("folder");
    Item* item = new Movie("item");
    previous_parent->addChild(item);
    const Item* tree_root = treeContext_->getRootItem();
    treeContext_->registerItem(previous_parent);
    treeContext_->registerItem(item);
    treeContext_->addTopLevelItem(item);
    CPPUNIT_ASSERT_MESSAGE("Wrong new Item parent", item->getParent()->getId() == tree_root->getId());
    CPPUNIT_ASSERT_MESSAGE("Root Item doesn't contain the added Item", tree_root->containsChild(item->getId()));
    CPPUNIT_ASSERT_MESSAGE("Item hasn't been erased of its previous parent child list", previous_parent->childCount() == 0);
}

/*
  As addTopLevelItem tests, there are no test to do about moving an Item in an
  empty (or not) other Item or check double addition because this method is a
  convenience method that wrap a delegate call to Folder::removeSubItem and
  Folder::addSubItem. See this test cases for those results.

  The tests below are about parent (previous and new) consistency, which is
  not ensured by both Folder::removeSubItem and Folder::addSubItem.
 */

/*
  moveItem test with an Item which doesn't have a parent set (nullptr).
  New parent is registered to Item's context.
  Item parent consistency is checked with the getParent method.
  New parent child list consistency is checked with the containsChild method.
 */
void TestTreeContext::test_moveItem_nullparent()
{
    Item* item = new Movie("item");
    Item* folder = new Folder("folder");
    treeContext_->registerItem(item);
    treeContext_->registerItem(folder);
    treeContext_->moveItem(item,folder);
    CPPUNIT_ASSERT_MESSAGE("Wrong new Item parent", item->getParent()->getId() == folder->getId());
    CPPUNIT_ASSERT_MESSAGE("New parent doesn't contain the added Item", folder->containsChild(item->getId()));
}

/*
  moveItem test with an Item which has a parent set, but this parent
  is not registered to the Item's context.
  New parent is registered to Item's context.
  Item parent consistency is checked with the getParent method.
  New parent child list consistency is checked with the containsChild method.
  Previous parent child list consistency is checked with the childCount and
  containsChild methods.
 */
void TestTreeContext::test_moveItem_notNullParent_notInContext()
{
    Item* item = new Movie("item");
    Item* previous_parent = new Folder("previous_parent");
    previous_parent->addChild(item);
    Item* new_parent = new Folder("new_parent");
    treeContext_->registerItem(item);
    treeContext_->registerItem(new_parent);
    treeContext_->moveItem(item,new_parent);
    CPPUNIT_ASSERT_MESSAGE("Wrong new Item parent", item->getParent()->getId() == new_parent->getId());
    CPPUNIT_ASSERT_MESSAGE("New parent doesn't contain the added Item", new_parent->containsChild(item->getId()));
    CPPUNIT_ASSERT_MESSAGE("Item hasn't been erased of its previous parent child list", previous_parent->childCount() == 0);
}

/*
  moveItem test with an Item which has a parent set, and this parent
  is registered to the Item's context.
  New parent is registered to Item's context.
  Item parent consistency is checked with the getParent method.
  New parent child list consistency is checked with the constainsChild method.
  Previous parent child list consistency is checked with the childCount
  method.
 */
void TestTreeContext::test_moveItem_notNullParent_inContext()
{
    Item* item = new Movie("item");
    Item* previous_parent = new Folder("previous_parent");
    previous_parent->addChild(item);
    Item* new_parent = new Folder("new_parent");
    treeContext_->registerItem(item);
    treeContext_->registerItem(previous_parent);
    treeContext_->registerItem(new_parent);
    treeContext_->moveItem(item,new_parent);
    CPPUNIT_ASSERT_MESSAGE("Wrong new Item parent", item->getParent()->getId() == new_parent->getId());
    CPPUNIT_ASSERT_MESSAGE("New parent doesn't contain the added Item", new_parent->containsChild(item->getId()));
    CPPUNIT_ASSERT_MESSAGE("Item hasn't been erased of its previous parent child list", previous_parent->childCount() == 0);
}

/*
  There is no test to do on searchItem and searchSingleItem methods because
  they are just convinience method that delegates calls on the given searcher.
  See Test(ConcreteSearcher) methods for those tests.
 */

/*
  registerItem test with an empty context (no Item registered before) cannot be
  done because internal ID calculation is not ensured by the specification, and
  there is no way to know if some previous ID are kept or not.
 */

/*
  registerItem test with a non-empty context, which contains at least one Item
  with the same name as the registering one. (here 1).
  ID unicity check is done with getId method on previous registered Item.
 */
void TestTreeContext::test_registerItem_notEmptyContext_sameItemName()
{
    Item* item1 = new Movie("item");
    treeContext_->registerItem(item1);
    Item* item2 = new Movie("item");
    treeContext_->registerItem(item2);
    CPPUNIT_ASSERT_MESSAGE("The IDs of the two registered Item are the same", item1->getId() != item2->getId());
}

/*
  registerItem test with a non-empty context, where previous registered Item
  has been deleted.
  The goal of this test is to check if there is an auto-increment or an ID
  reallocation error (by calculating an ID which still is in the context).
  ID unicity check is done with getId method on other Items in the context.
 */
void TestTreeContext::test_registerItem_afterDeleteItem()
{
    Item* item1 = new Movie("item1");
    Item* item2 = new Movie("item2");
    treeContext_->registerItem(item1);
    treeContext_->registerItem(item2);
    Item* item3 = new Movie("item3");
    treeContext_->deleteItem(item1);
    treeContext_->registerItem(item3);
    CPPUNIT_ASSERT_MESSAGE("Registered Item ID is the same as the other Item still registered to the context", item3->getId() != item2->getId());
}

/*
  deleteItem test with an Item which doesn't have a parent set (nullptr).
  This test use a MockItem object to check if the Item destructor is called.
 */
void TestTreeContext::test_deleteItem_nullParent()
{
    bool item_deleted = false;
    MockItem* item = new MockItem("item",item_deleted);
    treeContext_->registerItem(item);
    treeContext_->deleteItem(item);
    CPPUNIT_ASSERT_MESSAGE("Item hasn't been deleted", item_deleted);
}

/*
  deleteItem test with an Item which has a parent set.
  This test use a MockItem object to check if the Item destructor is called.
  Parent child list consistency is checked with childCount method.
 */
void TestTreeContext::test_deleteItem_notNullParent()
{
    Item* parent = new Folder("folder");
    bool item_deleted = false;
    MockItem* item = new MockItem("item", item_deleted);
    treeContext_->registerItem(parent);
    treeContext_->registerItem(item);
    treeContext_->deleteItem(item);
    CPPUNIT_ASSERT_MESSAGE("Item hasn't been deleted", item_deleted);
    CPPUNIT_ASSERT_MESSAGE("Item hasn't been removed from its parent child list", parent->childCount() == 0);
}
