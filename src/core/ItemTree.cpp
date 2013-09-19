#include "ItemTree.h"
#include "Item.h"
#include "ItemSearcher.h"
#include "Movie.h"
#include "Folder.h"
#include "CoreException.h"
#include <sstream>

// debug
#include <iostream>

using namespace std;

/*!
  \brief Constructs a new ItemManager.

  The root representing the managed tree is created with the
  generic name \em _root_ and the initial ID \em 0.

  \note The root Item is the only one in the hierarchy to have a parent
  set to nullptr.
 */
ItemTree::ItemTree()
{
    treeRoot_ = new Folder("_root_",*this);
    nextId_ = 0;
}

/*!
  \brief Deletes the ItemManager and the Item representing the hierarchy tree.

  All the Item contained in the tree are recursively deleted (see Folder::~Folder
  for further informations).
 */
ItemTree::~ItemTree()
{
    delete treeRoot_;
}

/*!
  \brief Generic search interface.

  Apply the given searcher to start Item descendants (included start).
  If start is nullptr then the research begin at the tree root Item (included).

  \param searcher the ItemSearcher used to perform the research.
  \param start the item to explore the descendants of (including itself).

  \return a vector containing the Items matched by the searcher, or an empty
  vector if no Item were found.

  \note Because ItemSearcher interface handle multiple-result searcher, the unified
  result is put in a vector.
  \see ItemTree::searchSingleItem method if you want to perform a single-result
  research.
 */
const vector<Item*> ItemTree::searchItem(ItemSearcher& searcher, Item* start) const
{
    Item* start_item = nullptr;
    if(start != nullptr) {
        start_item = start;
    }
    searcher.search(start_item);
    return searcher.getFoundItems();
}

/*!
  \brief Generic search interface.

  Apply the given searcher to start Item descendants (including start).
  If start is nullptr then the research begin at the tree root Item (included).

  \param searcher the ItemSearcher used to perform the research.
  \param start the item to explore the descendants of (including itself).

  \return the Item matched by the searcher, or nullptr if no Item were found.

  \note if this method is called with multiple-result searcher the result will
  be the first Item found.
  \see ItemTree::searchItem method if you want to perform a multiple-result
  research.
 */
Item* ItemTree::searchSingleItem(ItemSearcher& searcher, Item* start) const
{
    Item* start_item = nullptr;
    if(start != nullptr) {
        start_item = start;
    }
    searcher.search(start_item);
    if(searcher.getFoundItems().empty()) {
        return nullptr;
    }
    return searcher.getFoundItems()[0];
}

/*!
  \return the root Item of the Item tree.
  \note This Item doesn't store any information and should be used only
  for value comparisons.
 */
Item* ItemTree::getRootItem() const
{
    return treeRoot_;
}

/*!
  Return the default Item parent.

  Any Item created in the TreeItem context is appended
  to this default parent. It is also the Item where removed
  Item (with Item::removeSubItem) are appended.

  \return the default parent of any handled Item.
 */
Item* ItemTree::getDefaultItemParent() const
{
    return treeRoot_;
}

/*!
  \return the number of top level Item registered to the ItemManager.
 */
unsigned int ItemTree::getTopLevelItemNumber() const
{
    return treeRoot_->getAllSubItems().size();
}

/*!
  \brief Register the given Item to the tree context.

  The registration is made by setting the Item as a top level
  Item (direct child of tree root) and its ID with a calculated
  unique value.
  \param item the Item to register to the context.
 */
void ItemTree::registerItem(Item* item)
{
    ostringstream oss;
    oss << nextId_;
    /*
      The Item to construct is the root of the tree.
      It cannot have the default parent treeRoot.
     */
    if(nextId_ == 0) {
        item->setParent(nullptr);
        item->setId(oss.str());
    }
    else {
        // warning : unhandled exception.
        treeRoot_->addSubItem(getDefaultItemParent());
        item->setId(oss.str());
    }
    ++nextId_;
}

/*!
  \brief Delete consistently the given Item from the context.

  \param item the Item to delete from the context.
 */
void ItemTree::deleteItem(Item* item)
{
    /*
      Don't remove the Item from its parent child list, this is done
      in the Item destructor.
      Also don't delete Item's children, this is done in the concrete
      Item subclass if it can handle children.
     */
    delete item;
}
