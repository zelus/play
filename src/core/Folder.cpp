#include "Folder.h"
#include "CoreException.h"
#include "ItemVisitor.h"
#include <sstream>
// debug
#include <iostream>

using namespace std;

/*!
  \brief Construct a Folder with the given name in the given context (ItemTree)

  \param name the name of the Folder.
  \param itemTree the tree the Folder belongs to.
 */
Folder::Folder(const std::string& name, ItemTree& itemTree) : Item(name,itemTree)
{

}

/*!
  \brief  Deletes the Folder and all its children recursively.

  The Folder is also removed of its parent child list.
 */
Folder::~Folder()
{
    for(size_t i = 0; i < items_.size(); i++) {
        try {
            deleteSubItem(items_[i]);
        }catch(CoreException&) {
            /*
              No exception could be thrown during the call, the
              current object is the current Folder (and it can
              handle children). Moreover, the calls are done during
              a children iteration, so each call will find the child
              to delete.
             */
        }
    }
}

/*!
  \brief Add the given Item to the child list.

  Add the Item to the managed child list and set its parent
  to the current folder.

  \param item the Item to add.

  \exception CoreException if the Folder already contains the Item.

  \note Previous Item's parent child list consistency is not ensured
  (no removeSubItem call). To move an Item and preserve parent consistency
  see ItemTree::moveItem(Item*, Item*).
 */
void Folder::addSubItem(Item* item)
{
    if(containsSubItem(item->getId())) {
        stringstream ss;
        ss << "The Folder " << name_ << " already contains an Item with the id " << item->getId();
        throw CoreException(ss.str(),__FILE__,__LINE__);
    }
    item->setParent(this);
    items_.push_back(item);
}

/*!
  \brief Remove the given Item from the child list.

  Remove the Item from the managed children list and set its parent
  to the default context parent (provided by TreeItem).

  \param item the Item to remove.

  \exception CoreException if the Folder doesn't contain the Item.

  \note The removed Item is not deleted.
  \see deleteSubItem method if you want to delete a child Item.
  */
void Folder::removeSubItem(Item *item)
{
    vector<Item*>::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == item->getId()) {
            items_.erase(it);
            (*it)->setParent(itemTree_.getDefaultItemParent());
            return;
        }
    }
    stringstream ss;
    ss << "The Folder " << name_ << " doesn't contain the Item " << item->getName();
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Delete the given Item and remove it from the child list.

  Remove the Item from the managed children list and delegate its destruction
  to the context (TreeItem::deleteItem) to ensure consistent destruction.

  \param item the Item to delete.

  \exception CoreException if the Folder doesn't contain the Item.
 */
void Folder::deleteSubItem(Item *item)
{
    vector<Item*>::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == item->getId()) {
            items_.erase(it);
            itemTree_.deleteItem(*it);
            return;
        }
    }
    stringstream ss;
    ss << "The Folder " << name_ << " doesn't contain the Item " << item->getName();
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Search if a child match the given ID and return it.

  \param id the ID of the wanted Item.
  \return a pointer to the Item if at least one child match the given ID,
  nullptr otherwise.
 */
Item* Folder::getSubItem(const string& id) const
{
    vector<Item*>::const_iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == id) {
            return *it;
        }
    }
    return nullptr;
}

/*!
  \brief Search if a child match the given ID.

  \param id the ID of the wanted Item.
  \return true if at least one child match the given ID, false otherwise.
 */
bool Folder::containsSubItem(const string& id) const
{
    vector<Item*>::const_iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == id) {
            return true;
        }
    }
    return false;
}

/*!
  \brief Calculate the position of the given item in the child list.

  \param item the Item to match in the child list.
  \return the index of the given Item, or -1 if there is no child matching it.
 */
int Folder::getSubItemIndex(Item* item) const
{
    for(size_t i = 0; i < items_.size(); ++i) {
        if(items_[i]->getId() == item->getId()) {
            return i;
        }
    }
    return -1;
}

/*!
  \return a vector containing the pointers to Item's children.
 */
const vector<Item*>& Folder::getAllSubItems() const
{
    return items_;
}

/*!
  \return the number of children handled by the Item.
 */
unsigned int Folder::getSubItemNumber() const
{
    return items_.size();
}


/*!
  \brief Call dedicated Folder handler in given visitor.

  \param visitor the ItemVisitor to use through the Folder.
 */
void Folder::accept(ItemVisitor& visitor)
{
    visitor.visitFolder(this);
}
