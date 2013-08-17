#include "Folder.h"
#include "Item.h"

#include <stdexcept>
#include <sstream>
// debug
#include <iostream>

/*!
  \brief Constructs a Folder from the given parameters.

  The given name and parent are delegated to the Item constructor, and
  the ItemType is statically defined to FOLDER_TYPE .
  \param id a unique ID associated to the Folder.
  \param folderName the name of the Folder.
  \param parent the parent of the Folder.
  \note There is no consistency checking done on the ID unicity. To create Folders with consistent
  unique ID see \see ItemManager::createFolder method.
 */
Folder::Folder(const string& id, const string& folderName, Item* parent, TagManager<Item*>* tagManager) : Item(id,folderName,FOLDER_TYPE,parent,tagManager)
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
    if(containsSubItem(item->getName())) {
        stringstream ss;
        ss << "The Folder " << itemName_ << " already contains an Item with the name " << item->getName();
        throw logic_error(ss.str());
    }
    Item* itemParent = item->getParent();
    if(itemParent != this && itemParent != nullptr) {
        itemParent->removeSubItem(item);
    }
    item->setParent(this);
    items_.push_back(item);
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
            (*it)->setParent(nullptr);
            items_.erase(it);
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
            delete (*it);
            items_.erase(it);
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
  \brief Overrides the basic containsSubItem method defined in Item class.
  \param itemName the name of the wanted Item.
  \return true if the wanted Item is in the child list, false
  otherwise.
 */
bool Folder::containsSubItem(const string &itemName) const
{
    ItemList::const_iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getName() == itemName) {
            return true;
        }
    }
    return false;
}

/*!
  \brief Overrides the basic getAllSubItems method defined in the Item class.
  \return the direct subItems list of the Folder.
 */
ItemList Folder::getAllSubItems() const
{
    return items_;
}
