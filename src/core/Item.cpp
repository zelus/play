#include "Item.h"
#include "CoreException.h"
#include "ItemVisitor.h"
#include <sstream>
// debug
#include <iostream>

using namespace std;

/*!
  \brief Constructs an Item from the given parameters.

  \note If a parent is given the constructed Item is added to its parent child list.
  \param id A unique ID associated to the Item.
  \param name The name of the Item.
  \param type The type of the Item.
  \param parent The parent of the Item.
  \exception CoreException if the given parent cannot handle subItems.
  \note There is no consistency checking done on the ID unicity. To create Items with consistent
  unique ID see \see ItemManager::createItem and its derivated methods.
 */
Item::Item(const std::string& id, const std::string& name, ItemType type, Item* parent)
{
    id_ = id;
    name_ = name;
    parent_ = parent;
    type_ = type;
    if(parent_ != nullptr) {
        try {
            parent_->addSubItem(this);
        }catch(CoreException& e) {
            throw e;
        }
    }
}

/*!
  \brief Deletes the Item.

  If the Item has a parent the reference contained in the parent is removed.
 */
Item::~Item()
{
    /*
        Check if the parent contains the subItem to avoid infinite
        call loop (if the delete method is called from the parent
        it has even remove the Item from it subItem list, and the
        removeSubItem method doesn't need to be called. Doing this
        might cause a call loop between setParent and removeSubItem
        methods).
    */
    if(parent_ != nullptr && parent_->containsSubItem(id_)) {
        parent_->removeSubItem(this);
    }
}

/*!
  \return the parent of the Item.
 */
Item* Item::getParent() const
{
    return parent_;
}

/*!
  \return the id of the Item.
  \note This method is required by the Tag template.
  \bug The method return the name of the Item, a unique ID must
  be returned containing the full path of the item.
 */
const string& Item::getId() const
{
    return id_;
}

/*!
  \return the name of the Item.
 */
const string& Item::getName() const
{
    return name_;
}

/*!
  \return the ItemType of the Item.
 */
ItemType Item::getType() const
{
    return type_;
}

/*!
  \brief Set a new parent to the Item.

  If the new parent is not nullptr then try to add the Item to
  the new parent.

  \param parent the new parent.

  \exception CoreException if the new parent cannot handle subItems.
 */
void Item::setParent(Item* newParent)
{
    if(parent_ != newParent) {
        Item* old_parent = parent_;
        parent_ = newParent;
        if(old_parent != nullptr && old_parent->containsSubItem(id_)) {
            old_parent->removeSubItem(this);
        }
        if(parent_ != nullptr && !parent_->containsSubItem(id_)) {
            try {
                parent_->addSubItem(this);
            }catch(CoreException& e) {
                throw;
            }
        }
    }
}

/*!
  \brief Set a new name to the Item.

  The Tag list is also updated with the new name.

  \param name the new name of the Item.
 */
void Item::setName(const string& name)
{
    name_ = name;
}

/*!
  \brief Basic implementation of the addSubItem method.
  \param item the Item to add to the child list.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::addSubItem(Item *item)
{
    stringstream ss;
    ss << "The Item " << name_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the removeSubItem method.
  \param item the Item to remove from the child list.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::removeSubItem(Item *item)
{
    stringstream ss;
    ss << "The Item " << name_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the deleteSubItem method.
  \param item the Item to remove from the child list.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::deleteSubItem(Item *item)
{
    stringstream ss;
    ss << "The Item " << name_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the getSubItem method.
  \param itemId the ID of the wanted Item.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
Item* Item::getSubItem(const string &itemId) const
{
    stringstream ss;
    ss << "The Item " << name_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the containsSubItem method.
  \param itemId the ID of the wanted Item.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
bool Item::containsSubItem(const string& itemId) const
{
    stringstream ss;
    ss << "The Item " << name_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the getAllSubItems method.

  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further imformations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
const vector<Item*>& Item::getAllSubItems() const
{
    stringstream ss;
    ss << "The Item " << name_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}
