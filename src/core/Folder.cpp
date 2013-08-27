#include "Folder.h"
#include "CoreException.h"
#include "InternalErrorException.h"
#include "IllegalOperationException.h"
#include "ItemVisitor.h"
#include <sstream>
// debug
#include <iostream>

using namespace std;

/*!
  \brief Constructs a Folder from the given parameters.

  The given name and parent are delegated to the Item constructor, and
  the ItemType is statically defined to FOLDER_TYPE.

  \param id a unique ID associated to the Folder.
  \param name the name of the Folder.
  \param parent the parent of the Folder.
  \exception IllegalOperationException if the given parent cannot handle subItems.
  \exception CoreException if the parent even contains an Item with the same ID.
  \note There is no consistency checking done on the ID unicity.
  \see ItemManager::createFolder to create Items with valid and unique ID.
 */
Folder::Folder(const std::string& id, const std::string& name, Item* parent) : Item(id,name,ItemType::FOLDER_TYPE,parent)
{

}

/*!
  \brief  Deletes the Folder and all its subItems recursively.

  If the Folder has a parent it is removed from its children list.
 */
Folder::~Folder()
{
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

  Set the parent of item to the current folder.

  \param item the Item to add to the child list.

  \exception CoreException if the Folder even contains the Item.
  \exception InternalErrorException if a consistency issue is found.
 */
void Folder::addSubItem(Item *item)
{
    if(containsSubItem(item->getId())) {
        stringstream ss;
        ss << "The Folder " << name_ << " already contains an Item with the id " << item->getId();
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
        try {
            item->setParent(this);
        }catch(IllegalOperationException& e) {
            /*
                No exception should be thrown by the call because
                the parent of the sub Item is the current Item which
                can handle sub Items.
            */
            stringstream ss;
            ss << "Parent of Item " << item->getId() << " [" << item->getName() << "] cannot handle sub Item";
            throw InternalErrorException(ss.str(),__FILE__,__LINE__);
        }
    }
}

/*!
  \brief Overrides the basic removeSubItem method defined in Item class.

  Set the parent of item to nullptr.

  \param item the Item to remove from the child list.

  \exception CoreException if the Folder doesn't contain the Item.
  \exception InternalErrorException if a consistency issue is found.
  \note The removed Item is not deleted.
  \see deleteSubItem method if you want to delete a child Item.
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
                try {
                    erased_item->setParent(nullptr);
                }catch(IllegalOperationException& e) {
                    /*
                        No exception should be thrown because
                        the parent of the sub Item is the current
                        Item which can handle sub Items.
                    */
                    stringstream ss;
                    ss << "Parent of Item " << item->getId() << " [" << item->getName() << "] cannot handle sub Item";
                    throw InternalErrorException(ss.str(),__FILE__,__LINE__);
                }
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

  Remove item from the child list and its destructor is called.

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

  \param id the ID of the wanted Item.

  \return the Item pointer if the wanted Item's ID is in the child list, nullptr
  otherwise.
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
  \brief Overrides the basic containsSubItem method defined in Item class.

  \param id the ID of the wanted Item.
  \return true if the wanted Item's ID is in the child list, false
  otherwise.
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
  \brief Overrides the basic getAllSubItems method defined in the Item class.
  \return the subItems list of the Folder.
 */
const vector<Item*>& Folder::getAllSubItems() const
{
    return items_;
}


/*!
  \brief Overrides the basic accept method defined in the Item class.

  Call dedicated method in visitor.

  \param visitor the ItemVisitor to use through the Folder.
 */
void Folder::accept(ItemVisitor* visitor)
{
    visitor->visitFolder(this);
}
