#include "item.h"
#include "folder.h"
#include "tag.h"
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
  \brief Constructs an Item from the given Item.
  \param item The Item to contruct from.
 */
Item::Item(const Item &item)
{
    itemName_ = item.itemName_;
    parent_ = item.parent_;
    itemType_ = item.itemType_;
    if(parent_ != nullptr) {
        try {
            parent_->addSubItem(this);
        }catch(logic_error& e) {
            throw e;
        }
    }
}

/*!
  \brief Deletes the Item.
  \warning This method doesn't ensure consistency of the
  composite pattern : no deletion on eventual parent is done,
  if you want to delete an Item wich has a parent you have to
  use Item::deleteSubItem parent method instead.
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

void Item::addTag(Tag *tag)
{
    for(size_t i = 0; i < tagList_.size(); i++) {
        if(tagList_[i]->getTagName() == tag->getTagName()) {
            stringstream ss;
            ss << "Cannot add Tag " << tag->getTagName() << " to the Item " << itemName_ << " : Item is already tagged with this Tag.";
            throw logic_error(ss.str());
        }
    }
}

void Item::removeTag(Tag *tag)
{
    TagList::iterator it;
    for(it = tagList_.begin(); it != tagList_.end(); ++it) {
        if((*it)->getTagName() == tag->getTagName()) {
            tagList_.erase(it);
            break;
        }
    }
    if(it == tagList_.end()) {
        stringstream ss;
        ss << "Cannot erase the Tag " << tag->getTagName() << " from the Item " << itemName_ << " : the Item is not tagged with the Tag.";
        throw logic_error(ss.str());
    }
}

TagList Item::getAllTags() const
{
    return tagList_;
}
