#include "TreeContext.h"
#include "Item.h"
#include "ItemSearcher.h"
#include "Movie.h"
#include "Folder.h"
#include "CoreException.h"
#include <sstream>

// debug
#include <iostream>

namespace play_core {

using namespace std;

/*!
  \brief Constructs a new ItemManager.

  The root representing the managed tree is created with the
  generic name \em _root_ and the initial ID \em 0.
 */
TreeContext::TreeContext()
{
    nextId_ = 0;
    treeRoot_ = new Folder("_root_");
    treeRoot_->setId("0");
}

/*!
  \brief Deletes the ItemManager and the Item representing the hierarchy tree.

  All the Item contained in the tree are recursively deleted (see Folder::~Folder
  for further informations).
 */
TreeContext::~TreeContext()
{
    delete treeRoot_;
}

/*!
  \return the root of the current TreeContext.

  \note The returned pointer is const-qualified to avoid unsafe operations
  (like changing its name).
 */
const Item* TreeContext::getRootItem() const
{
    return treeRoot_;
}

/*!
  \brief Convenience accessor to the root's child Items.

  \return a vector containing the children of the root Item.
 */
const vector<Item*> TreeContext::getTopLevelItems() const
{
    return treeRoot_->getChildren();
}

/*!
  \brief Convenience accessor to the root's child count.

  \return the number of children handled by the root Item.
 */
unsigned int TreeContext::getTopLevelItemCount() const
{
    return treeRoot_->childCount();
}

/*!
  \brief Convenience method to add an Item to the root's child list.

  The Item is removed from its previous parent if it exists.

  \param item the Item to add at the top level of the tree.

  \exception CoreException if the given Item cannot be removed from its
  previous parent nor added to the root.

  \warning If the Item is not registered to the current TreeContext the
  behaviour is undefined. (ID unicity cannot be ensured between TreeContext
  and external Items).
 */
void TreeContext::addTopLevelItem(Item* item)
{
    try {
        moveItem(item,treeRoot_);
    }catch(CoreException&) {
        throw;
    }
}

/*!
  \brief Move an Item to the given new Parent.

  Tree consistency is ensured : the given Item is first
  removed from its previous parent and then added to the new one.

  \param item the Item to move.
  \param newParent the parent to add item to.

  \exception CoreException if the given Item cannot be removed from its
  previous parent nor added to the new one.

  \warning If at least one of the given Items is not registered to the current
  TreeContext the behaviour is undefined. (ID unicity cannot be ensured between
  TreeContext and external Items).
 */
void TreeContext::moveItem(Item* item, Item* newParent)
{
    if(item != nullptr && newParent != nullptr) {
        if(item->getParent() != nullptr) {
            try {
                item->getParent()->removeChild(item);
            }catch(CoreException&) {
                throw;
            }
        }
        try {
            newParent->addChild(item);
        }catch(CoreException&) {
            throw;
        }
    }
}

/*!
  \brief Generic search interface.

  Apply the given searcher to start Item (included it).
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
const vector<Item*> TreeContext::searchItem(ItemSearcher& searcher, Item* start) const
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
Item* TreeContext::searchSingleItem(ItemSearcher& searcher, Item* start) const
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
  \brief Register the given Item to the tree context.

  The registration is made by setting the Item ID with a calculated unique
  value in the context.

  \param item the Item to register to the context.
 */
void TreeContext::registerItem(Item* item)
{
    ostringstream oss;
    oss << nextId_;
    item->setId(oss.str());
    ++nextId_;
}

/*!
  \brief Delete consistently the given Item from the context.

  \param item the Item to delete from the context.

  \warning If the Item is not registered to the current TreeContext it is
  deleted but unique ID generation cannot be ensured anymore.
 */
void TreeContext::deleteItem(Item* item)
{
    try {
        if(item->getParent() != nullptr) {
            item->getParent()->deleteChild(item);
        }
        else {
          delete item;
        }
    }catch(CoreException& e) {
        /*
          There is a consistency error : the item is not registered
          has a child of its parent. This wouldn't cause any damage 
          in this case because a deletion is wanted. The item is just
          deleted regardless of consistency errors.
         */
        delete item;
    }
}

} // namespace
