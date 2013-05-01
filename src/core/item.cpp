#include "item.h"
#include "folder.h"
#include <stdexcept>
#include <sstream>
// debug
#include <iostream>

/*!
  \brief Construct an Item from the given parameters.
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
  \brief Construct an Item from the given Item.
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

Item::~Item()
{
    if(parent_ != nullptr) {
        parent_->removeSubItem(this);
    }
}

const Item* Item::getParent() const
{
    return parent_;
}

const string& Item::getName() const
{
    return itemName_;
}

ItemType Item::getType() const
{
    return itemType_;
}

void Item::setParent(Folder *parent)
{
    parent_ = parent;
}

void Item::addSubItem(Item *item)
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
}

void Item::removeSubItem(Item *item)
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
}

Item* Item::getSubItem(const string &itemName) const
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
}

ItemList Item::getAllSubItems() const
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw logic_error(ss.str());
}
