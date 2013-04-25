#include "item.h"
#include "folder.h"
// debug
#include <iostream>

Item::Item(const string& itemName, Folder* parent)
{
    itemName_ = itemName;
    parent_ = parent;
}

Item::Item(const Item &item)
{
    itemName_ = item.itemName_;
}

Item::~Item()
{
    if(parent_ != nullptr) {
        parent_->removeSubItem(this);
    }
}

const Item* Item::getParent() const {
    return parent_;
}

const string& Item::getName() const
{
    return itemName_;
}

void Item::setParent(Folder *parent) {
    parent_ = parent;
}
