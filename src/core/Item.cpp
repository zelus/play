#include "Item.h"
#include "CoreException.h"
#include <sstream>
// debug
#include <iostream>

/*!
  \brief Constructs an Item from the given parameters.
  \note If a parent is given the constructed Item is added to its parent child list.
  \param id A unique ID associated to the Item.
  \param itemName The name of the Item.
  \param itemType The type of the Item.
  \param parent The parent of the Item.
  \exception std::logic_error if the given parent cannot handle subItems.
  \note There is no consistency checking done on the ID unicity. To create Items with consistent
  unique ID see \see ItemManager::createItem and its derivated methods.
 */
Item::Item(const string& id, const string& name, ItemType type, Item* parent)
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
  \brief Deletes the Item and its references into its Tags.

  The reference of the Item in each Tag it is registered to is
  deleted.

  \bug No composite pattern consistency checking.
 */
Item::~Item()
{

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
  \param parent the new parent.
  \bug This method doesn't ensure consistency of the
  composite pattern : the Item is not removed from its eventual parent,
  if you want to remove an Item from its parent you have to use
  Item::removeSubItem parent method instead.
 */
void Item::setParent(Item *parent)
{
    parent_ = parent;
}

/*!
  \brief Set a new name to the Item.

  The Tag list is also updated with the new name.

  \param name the new name of the Item.
 */
void Item::setName(const std::string& name)
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
  \param itemName the name of the wanted Item.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
Item* Item::getSubItem(const string &itemName) const
{
    stringstream ss;
    ss << "The Item " << name_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the containsSubItem method.
  \param itemName the name of the wanted Item.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
bool Item::containsSubItem(const string &itemName) const
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
