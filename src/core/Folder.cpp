#include "Folder.h"
#include "CoreException.h"
#include "ItemVisitor.h"
#include <sstream>
// debug
#include <iostream>

using namespace std;

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
Folder::Folder(const string& id, const string& name, Item* parent) : Item(id,name,ItemType::FOLDER_TYPE,parent)
{

}

/*!
  \brief  Deletes the Folder and all its subItems recursively.
  \note Parent management is handled in Item superclass.
 */
Folder::~Folder()
{
    cout << "delete folder" << endl;
    /*
        A local copy is needed because a clear method is
        called on the subItem vector to prevent multiple
        iteration when deleting subItems.
    */
    vector<Item*> items(items_);
    /*
        Clean the vector to prevent multiple and useless iterations
        through the subItem list.
        (Item destructor call removeSubItem and containsSubItem
        methods which iterate all the subItem list). This iteration
        is multiplied by the number of subItem (each one will call
        those methods).
    */
    items_.clear();
    for(size_t i = 0; i < items.size(); i++) {
        delete items[i];
    }
}

/*!
  \brief Overrides the basic addSubItem method defined in Item class.

  Set the parent of the Item to the current folder.

  \param item the Item to add to the child list.

  \exception CoreException if the Folder even contains the Item.
 */
void Folder::addSubItem(Item *item)
{
    if(containsSubItem(item->getId())) {
        stringstream ss;
        ss << "The Folder " << name_ << " already contains an Item with the name " << item->getName();
        throw CoreException(ss.str(),__FILE__,__LINE__);
    }
    /*
        Push the Item reference before update its parent
        because Item::setParent calls containsSubItem method,
        which needs to return true to avoid infinite loop
        call.
    */
    items_.push_back(item);
    /*
        Check if the item has ever changed its parent. This verification
        avoid infinite call loop between Item and Folder (the Item sets
        its parent and then calls the addSubItem method to ensure composite
        consistency).
    */
    if(item->getParent() == nullptr || item->getParent()->getId() != id_) {
        item->setParent(this);
    }
}

/*!
  \brief Overrides the basic removeSubItem method defined in Item class.

  The Item parent is restored to its default value : nullptr.

  \param item the Item to remove from the child list.

  \exception CoreException if the Folder doesn't contain the Item.
  \note The removed Item is not deleted. To delete a child Item \see deleteSubItem method instead.
  */
void Folder::removeSubItem(Item *item)
{
    vector<Item*>::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == item->getId()) {
            /*
                Store the iterator value in a variable because
                vector::erase method invalidates the iterator of
                the removed Item.
            */
            Item* erased_item = (*it);
            /*
                Erase the Item reference before update its parent
                because Item::setParent calls containsSubItem method,
                which needs to return false to avoid infinite loop
                call.
            */
            items_.erase(it);
            /*
                Check if the item has ever changed its parent. This verification
                avoid infinite call loop between Item and Folder (the Item sets
                its parent to nullptr and then calls the removeSubItem method to
                ensure composite consistency).
            */
            if(erased_item->getParent() != nullptr && erased_item->getParent()->getId() == id_) {
                erased_item->setParent(nullptr);
            }
            return;
        }
    }
    stringstream ss;
    ss << "The Folder " << name_ << " doesn't contain the Item " << item->getName();
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Overrides the basic deleteSubItem method defined in Item class.

  The given Item is removed from the child list and its destructor is called.

  \param item the Item to delete.

  \exception CoreException if the Folder doesn't contain the Item.
 */
void Folder::deleteSubItem(Item *item)
{
    vector<Item*>::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == item->getId()) {
            /*
                Store the iterator value in a variable because
                vector::erase method invalidates the iterator of
                the removed Item.
            */
            Item* erased_item = (*it);
            /*
                Erase the Item reference before call its destructor
                because it calls containsSubItem method, which needs
                to return false to avoid infinite loop call.
            */
            items_.erase(it);
            /*
                Call the destructor safely (the containsSubItem method
                will return false, avoiding an infinite call to removeSubItem.
            */
            delete erased_item;
            return;
        }
    }
    stringstream ss;
    ss << "The Folder " << name_ << " doesn't contain the Item " << item->getName();
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Overrides the basic getSubItem method defined in Item class.

  Return the subItem with the given ID.

  \param itemId the ID of the wanted Item.

  \return the Item pointer if the wanted Item is in the child list, nullptr
  otherwise.
 */
Item* Folder::getSubItem(const string& itemId) const
{
    vector<Item*>::const_iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getId() == itemId) {
            return *it;
        }
    }
    return nullptr;
}

/*!
  \brief Overrides the basic containsSubItem method defined in Item class.

  \param itemId the ID of the wanted Item.
  \return true if the wanted Item is in the child list, false
  otherwise.
 */
bool Folder::containsSubItem(const string &id) const
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
  \brief Overrides the basic getAllSubItems method defined in the Item class.
  \return the subItems list of the Folder.
 */
const vector<Item*>& Folder::getAllSubItems() const
{
    return items_;
}


void Folder::accept(ItemVisitor* visitor)
{
    visitor->visitFolder(this);
}
