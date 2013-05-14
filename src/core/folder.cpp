#include "folder.h"
#include "item.h"

#include <stdexcept>
#include <sstream>
// debug
#include <iostream>

/*!
  \brief Constructs a Folder from the given parameters.

  The given name and parent are delegated to the Item constructor, and
  the ItemType is statically defined to FOLDER_TYPE .
  \param folderName the name of the Folder.
  \param parent the parent of the Folder.
 */
Folder::Folder(const string& folderName, Item* parent) : Item(folderName,FOLDER_TYPE,parent)
{

}

/*!
  \brief Constructs a Folder from the given Folder.
  \param folder the Folder to construct from.
 */
Folder::Folder(const Folder &folder) : Item(folder.itemName_,FOLDER_TYPE,folder.parent_)
{

}

/*!
  \brief  Deletes the Folder and all its subItems recursively.
  \note Parent management is handled in Item superclass.
 */
Folder::~Folder()
{
    for(size_t i = 0; i < items_.size(); i++) {
        delete items_[i];
    }
}

/*!
  \brief Overrides the basic addSubItem method defined in Item class.

  If the Item already has a not nullptr parent, it is removed from its parent child list.
  The Item parent is then setted to the current Folder.
  \param item the Item to add to the child list.
 */
void Folder::addSubItem(Item *item)
{
    Item* itemParent = item->getParent();
    if(itemParent != this) {
        if(itemParent != nullptr) {
            itemParent->removeSubItem(item);
        }
        item->setParent(this);
        items_.push_back(item);
    }
}

/*!
  \brief Overrides the basic removeSubItem method defined in Item class.

  The Item parent is restored to its default value : nullptr.
  \param item the Item to remove from the child list.
  \exception std::logic_error if the Folder doesn't contain the Item.
  \note The removed Item is not deleted. To delete a child Item see deleteSubItem method instead.
  */
void Folder::removeSubItem(Item *item)
{
    ItemList::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getName() == item->getName()) {            
            items_.erase(it);
            (*it)->setParent(nullptr);
            return;
        }
    }
    stringstream ss;
    ss << "The Folder " << itemName_ << " doesn't contain the Item " << item->getName();
    throw logic_error(ss.str());
}

/*!
  \brief Overrides the basic deleteSubItem method defined in Item class.

  The given Item is removed from the child list and the destructor is called.
  \param item the Item to delete.
  \exception std::logic_error if the Folder doesn't contain the Item.
 */
void Folder::deleteSubItem(Item *item)
{
    ItemList::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getName() == item->getName()) {
            items_.erase(it);
            delete (*it);
            return;
        }
    }
    stringstream ss;
    ss << "The Folder " << itemName_ << " doesn't contain the Item " << item->getName();
    throw logic_error(ss.str());
}

/*!
  \brief Overrides the basic getSubItem method defined in Item class.
  \param itemName the name of the wanted Item.
  \return the Item pointer if the wanted Item is in the child list, nullptr
  otherwise.
 */
Item* Folder::getSubItem(const string &itemName) const
{
    ItemList::const_iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getName() == itemName) {
            return *it;
        }
    }
    return nullptr;
}

/*!
  \brief Overrides the basic getAllSubItems method defined in the Item class.
  \return the direct subItems list of the Folder.
 */
ItemList Folder::getAllSubItems() const
{
    return items_;
}
