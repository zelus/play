#include "ItemController.h"
#include <QString>

ItemController::ItemController(ItemManager& itemManager) : itemManager_(itemManager)
{

}

QVariant ItemController::getData(Item* item, int field) const
{
    switch(field) {
        case 0 :
        return QString::fromStdString(item->getName());
    }
    return QVariant();
}

Item* ItemController::getParent(Item* item) const
{
    Item* item_parent = item->getParent();
    // parent du parent pour supprimer l'item racine
    if(item_parent == nullptr || item_parent->getParent() == nullptr) {
        return nullptr;
    }
    return item_parent;
}

int ItemController::getTopLevelItemNumber() const
{
    return itemManager_.getTopLevelItemNumber();
}

int ItemController::getChildNumber(Item* item) const
{
    return item->getAllSubItems().size();
}
