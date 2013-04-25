#include "folder.h"
#include "item.h"

// debug
#include <iostream>

Folder::Folder(const string& folderName, Folder* parent) : Item(folderName,parent)
{

}

Folder::Folder(const Folder &folder) : Item(folder.itemName_,folder.parent_)
{

}

Folder::~Folder()
{
    for(size_t i = 0; i < items_.size(); i++) {
        delete items_[i];
    }
}

itemList Folder::getAllItems() const
{
    return items_;
}

Item* Folder::getItem(const string &itemName) const
{
    itemList::const_iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getName() == itemName) {
            return *it;
        }
    }
    return nullptr;
}

void Folder::addSubItem(Item *item)
{
    items_.push_back(item);
    item->setParent(this);
}

void Folder::removeSubItem(Item *item) {
    itemList::iterator it;
    for(it = items_.begin(); it != items_.end(); ++it) {
        if((*it)->getName() == item->getName()) {
            (*it)->setParent(nullptr);
            items_.erase(it);
            return;
        }
    }
}
