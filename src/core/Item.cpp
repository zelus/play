#include "Item.h"
#include "Folder.h"
#include "Tag.h"
#include <stdexcept>
#include <sstream>
// debug
#include <iostream>

/*!
  \brief Constructs an Item from the given parameters.
  \note If a parent is given the constructed Item is added to its parent child list.
  \param itemName The name of the Item.
  \param itemType The type of the Item.
  \param parent The parent of the Item.
  \exception std::logic_error if the given parent cannot handle subItems.
 */
Item::Item(const string& itemName, ItemType itemType, Item* parent)
{
    itemName_ = itemName;
    parent_ = parent;
    itemType_ = itemType;
    if(parent_ != nullptr) {
        try {
            parent_->addSubItem(this);
        }catch(logic_error& e) {
            throw e;
        }
    }
}

/*!
  \brief Deletes the Item and its references into its Tags.

  The Item reference into the registered Item list of each Tag is
  removed.
  \warning This method doesn't ensure consistency of the
  composite pattern : no deletion on eventual parent is done,
  if you want to delete an Item wich has a parent you have to
  use Item::deleteSubItem parent method instead.
 */
Item::~Item()
{
    for(size_t i = 0; i < tagList_.size(); ++i) {
        tagList_[i]->unregisterItem(this);
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
    return itemName_;
}

/*!
  \return the name of the Item.
 */
const string& Item::getName() const
{
    return itemName_;
}

/*!
  \return the ItemType of the Item.
 */
ItemType Item::getType() const
{
    return itemType_;
}

/*!
  \brief Set a new parent to the Item.
  \param parent the new parent.
  \warning This method doesn't ensure consistency of the
  composite pattern : the Item is not removed from its eventual parent,
  if you want to remove an Item from its parent you have to use
  Item::removeSubItem parent method instead.
 */
void Item::setParent(Item *parent)
{
    parent_ = parent;
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
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
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
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
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
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
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
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
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
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
}

/*!
  \brief Basic implementation of the getAllSubItems method.

  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further imformations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
ItemList Item::getAllSubItems() const
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
}

/*!
  \brief Adds a new Tag to the Tag list.

  If the addition succeeds the Item is then registered to the Tag.
  \exception std::logic_error if the Item is already tagged by the Tag or
  if the Tag has even registered the Item.
  \note This method ensure Tag and Item lists consistency.
 */
void Item::addTag(Tag<Item*> *tag)
{
    for(size_t i = 0; i < tagList_.size(); i++) {
        if(tagList_[i]->getName() == tag->getName()) {
            stringstream ss;
            ss << "Cannot add Tag " << tag->getName() << " to the Item " << itemName_ << " : Item is already tagged with this Tag.";
            throw logic_error(ss.str());
        }
    }
    tagList_.push_back(tag);
    try {
        tag->registerItem(this);
    }catch(logic_error& e) {
        throw e;
    }
}

/*!
  \brief Removes a Tag from the Tag list.

  If the removal succeeds the Item is then unregistered to the Tag.
  \exception std::logic_error if the Item is not tagged by the Tag or
  if the Tag has not registered the Item.
  \note This method ensure Tag and Item lists consistency.
 */
void Item::removeTag(Tag<Item*> *tag)
{
    bool updated = false;
    TagList::iterator it;
    for(it = tagList_.begin(); it != tagList_.end(); ++it) {
        if((*it)->getName() == tag->getName()) {
            tagList_.erase(it);
            updated = true;
            break;
        }
    }
    if(updated) {
        try {
            tag->unregisterItem(this);
        }catch(logic_error& e) {
            throw e;
        }
    }
    else {
        stringstream ss;
        ss << "Cannot erase the Tag " << tag->getName() << " from the Item " << itemName_ << " : the Item is not tagged with the Tag.";
        throw logic_error(ss.str());
    }
}

/*!
  \return the list of Tag associated to the Item.
 */
Item::TagList Item::getAllTags() const
{
    return tagList_;
}
