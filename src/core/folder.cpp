#include "folder.h"
#include "item.h"

Folder::Folder(const string& folderName) : Item(folderName)
{

}

Folder::Folder(const Folder &folder) : Item(folder.getName())
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

void Folder::addItem(const Item *item)
{
    items_.push_back(item);
}
