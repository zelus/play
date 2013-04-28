#include "item.h"
#include "folder.h"
#include <stdexcept>
#include <sstream>
// debug
#include <iostream>

Item::Item(const string& itemName, Item* parent)
{
    itemName_ = itemName;
    parent_ = parent;
    if(parent_ != nullptr) {
        try {
            parent_->addSubItem(this);
        }catch(logic_error& e) {
            throw e;
        }
    }
}

Item::Item(const Item &item)
{
    itemName_ = item.itemName_;
    parent_ = item.parent_;
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
