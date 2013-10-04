#ifndef ITEMCONTROLLER_H
#define ITEMCONTROLLER_H

#include "TreeContext.h"
#include "Item.h"
#include <QVariant>
class ItemController
{
public:
    ItemController(play_core::TreeContext& treeContext);
    QVariant getData(play_core::Item* item, int field) const;
    play_core::Item* getParent(play_core::Item* item) const;
    const play_core::Item* getRootItem() const;
    int getTopLevelItemNumber() const;
    int getChildNumber(play_core::Item* item) const;

private:
    play_core::TreeContext& treeContext_;
};

#endif // ITEMCONTROLLER_H
