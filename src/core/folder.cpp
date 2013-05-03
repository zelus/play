#include "folder.h"
#include "item.h"

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
  \param item the Item to add to the child list.
 */
void Folder::addSubItem(Item *item)
{
    items_.push_back(item);
    item->setParent(this);
}

/*!
  \brief Overrides the basic removeSubItem method defined in Item class.
  \param item the Item to remove from the child list.
  \note The removed Item is not deleted.
  \todo Raise an exception if the item is not in the child list.
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
