#include "Folder.h"
#include "CoreException.h"
#include "ItemVisitor.h"
#include <sstream>
// debug
#include <iostream>

namespace play_core {

using namespace std;

/*!
  \brief Construct a Folder with the given name.

  \param name the name of the Folder.
 */
Folder::Folder(const std::string& name) : Item(name)
{

}

/*!
  \brief  Delete the Folder and all its children recursively.

  \warning Consistency with the eventual parent child list is not ensured.
  \see Item::deleteChild for a parent-consistent deletion.

 */
Folder::~Folder()
{
    /*
      Don't call Folder::deleteItem here : each call will check
      if the child to delete is actually a child of the Folder, which
      is useless in that case.
     */
    for(size_t i = 0; i < items_.size(); ++i) {
        delete items_[i];
    }
}

/*!
  \brief Add the given Item to the child list.

  Add the Item to the child list and set its parent to the current Folder.

  \param item the Item to add.

  \exception CoreException if the Folder already contains the Item.

  \note Previous Item's parent child list consistency is not ensured
  (no removeSubItem call). To move an Item and preserve parent consistency
  see TreeContext::moveItem.

  \bug There is no simple way to add a child at a given position (all additions
  are done at the end of the vector), see #11.
 */
void Folder::addChild(Item* item)
{
    if(containsChild(item->getId())) {
        stringstream ss;
        ss << "The Folder " << name_ << " already contains an Item with the id " << item->getId();
        throw CoreException(ss.str(),__FILE__,__LINE__);
    }
    item->setParent(this);
    items_.push_back(item);
}

/*!
  \brief Remove the given Item from the child list.

  Remove the Item from the child list and set its parent to nullptr.

  \param item the Item to remove.

  \exception CoreException if the Folder doesn't contain the Item.

  \note The removed Item is not deleted.
  \see deleteChild method if you want to delete a child Item.
  */
void Folder::removeChild(Item *item)
{
    vector<Item*>::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == item->getId()) {
            (*it)->setParent(nullptr);
            items_.erase(it);
            return;
        }
    }
    stringstream ss;
    ss << "The Folder " << name_ << " doesn't contain the Item " << item->getName();
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Delete the given Item and remove it from the child list.

  \param item the Item to delete.

  \exception CoreException if the Folder doesn't contain the Item.
 */
void Folder::deleteChild(Item *item)
{
    vector<Item*>::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == item->getId()) {
            delete *it;
            items_.erase(it);
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
Item* Folder::getChild(const string& id) const
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
  \brief Search if there is at least one child matching the given ID.

  \param id the ID of the wanted Item.
  \return true if at least one child match the given ID, false otherwise.
 */
bool Folder::containsChild(const string& id) const
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
  \brief Calculate the position of the given Item in the child list.

  \param item the Item to match in the child list.
  \return the index of the given Item, or -1 if there is no child matching it.
 */
int Folder::getChildIndex(Item* item) const
{
    for(size_t i = 0; i < items_.size(); ++i) {
        if(items_[i]->getId() == item->getId()) {
            return i;
        }
    }
    return -1;
}

/*!
  \return a vector containing the pointers to the Folder's children.
 */
const vector<Item*>& Folder::getChildren() const
{
    return items_;
}

/*!
  \return the number of children handled by the current Folder.
 */
unsigned int Folder::childCount() const
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

} // namespace
