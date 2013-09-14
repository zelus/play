#ifndef ITEMCONTROLLER_H
#define ITEMCONTROLLER_H

#include "ItemManager.h"
#include "Item.h"
#include <QVariant>
class ItemController
{
public:
    ItemController(ItemManager& itemManager);
    QVariant getData(Item* item, int field) const;
    Item* getParent(Item* item) const;
    Item* getRootItem() const;
    int getTopLevelItemNumber() const;
    int getChildNumber(Item* item) const;

private:
    ItemManager& itemManager_;
};

#endif // ITEMCONTROLLER_H
