#include "Item.h"
#include "CoreException.h"
#include "InternalErrorException.h"
#include "IllegalOperationException.h"
#include "ItemVisitor.h"
#include <sstream>
// debug
#include <iostream>

using namespace std;

/*!
  \brief Construct an Item from the given parameters.

  \param id a unique ID associated to the Item.
  \param name the name of the Item.
  \param type the type of the Item.
  \param parent the parent of the Item (if not nullptr the Item is appended to the parent).
  \exception IllegalOperationException if the given parent cannot handle subItems.
  \exception CoreException if the parent even contains an Item with the same ID.
  \note There is no consistency checking done on the ID unicity.
  \see ItemManager::createItem and its derivated methods to create Items with valid and unique ID.
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
            /*
                The parent cannot handle sub Items or even
                contains the constructed Item (or an other
                one with the same ID). This would break tree
                consistency.
            */
            throw;
        }
    }
}

/*!
  \brief Deletes the Item.

  If the Item has a parent the reference contained in the parent is removed.
 */
Item::~Item()
{
    if(parent_ != nullptr) {
        try {
            parent_->removeSubItem(this);
        }catch(CoreException& e) {
            /*
                The parent doesn't contain the Item and cannot
                remove it. It may be a consequence of parent
                deletion. In any case this would not break tree
                consistency and nothing more needs to be done.
            */
        }
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

  \param newParent the new parent of the Item.

  \exception IllegalOperationException if the new parent cannot handle sub Items.
  \exception InternalErrorException if a consistency issue is found.
  \note If an exception happens during the process the original parent value
  is restored to keep tree consistency.
 */
void Item::setParent(Item* newParent)
{
    if(parent_ != newParent) {
        Item* old_parent = parent_;
        if(newParent != nullptr) {
            try {
                newParent->addSubItem(this);
            }catch(IllegalOperationException& e) {
                /*
                    The parent cannot handle sub Item, reset Item's
                    parent to its original value and throw the exception.
                */
                throw;
            }catch(InternalErrorException& e) {
                throw;
            }catch(CoreException& e) {
                /*
                    The parent even contains the Item, it may
                    be a consistency error but nothing more can
                    be done here.
                */
            }
        }
        parent_ = newParent;
        if(old_parent != nullptr) {
            try {
                old_parent->removeSubItem(this);
            }catch(IllegalOperationException& e) {
                /*
                    The actual parent cannot handle sub Item, this results
                    of a consistency error when it was set as the Item parent
                    and create a tree consistency issue.
                 */
                stringstream ss;
                ss << "Parent of Item " << id_ << " [" << name_ << "] cannot handle sub Item";
                throw InternalErrorException(ss.str(),__FILE__,__LINE__);
            }catch(CoreException& e) {
                /*
                    The parent doesn't contain the Item, it may
                    be a consistency error but nothing more can
                    be done here.
                */
            }
        }
    }
}

/*!
  \brief Set a new name to the Item.

  \param name the new name of the Item.
 */
void Item::setName(const string& name)
{
    name_ = name;
}

/*!
  \brief Basic implementation of the addSubItem method.
  \param item the Item to add to the child list.
  \exception IllegalOperationException if the Item can not have children.
  \warning This method fails default because basic Item is not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::addSubItem(Item*)
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the removeSubItem method.
  \param item the Item to remove from the child list.
  \exception IllegalOperationException if the Item can not have children.
  \warning This method fails default because basic Item is not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::removeSubItem(Item*)
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the deleteSubItem method.
  \param item the Item to remove from the child list.
  \exception IllegalOperationException if the Item can not have children.
  \warning This method fails default because basic Item is not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::deleteSubItem(Item*)
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the getSubItem method.

  \param id the ID of the wanted Item.
  \return a pointer to the found Item, nullptr otherwise.
  \exception IllegalOperationException if the Item can not have children.
  \warning This method fails default because basic Item is not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
Item* Item::getSubItem(const string&) const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the containsSubItem method.
  \param id the ID of the wanted Item.
  \return true if the Item is found in the children list, false otherwise.
  \exception IllegalOperationException if the Item can not have children.
  \warning This method fails default because basic Item is not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
bool Item::containsSubItem(const string&) const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" <<name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the getAllSubItems method.
  \return a vector containing the pointers to Item's children.
  \exception IllegalOperationException if the Item can not have children.
  \warning This method fails default because basic Item is not allowed to have children.
  See design pattern \em composite for further imformations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
const vector<Item*>& Item::getAllSubItems() const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}
