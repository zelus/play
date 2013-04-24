#include "item.h"

Item::Item(const string& itemName)
{
    itemName_ = itemName;
}

Item::Item(const Item &item)
{
    itemName_ = item.itemName_;
}

Item::~Item()
{

}

const string& Item::getName() const
{
    return itemName_;
}
