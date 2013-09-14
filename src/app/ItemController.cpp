#include "ItemController.h"
#include "IllegalOperationException.h"
#include <QString>
// debug
#include <iostream>

ItemController::ItemController(ItemManager& itemManager) : itemManager_(itemManager)
{

}

QVariant ItemController::getData(Item* item, int field) const
{
    std::cout << "call ItemController::data" << std::endl;
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

Item* ItemController::getRootItem() const
{
    return itemManager_.getRootItem();
}

int ItemController::getTopLevelItemNumber() const
{
    return itemManager_.getTopLevelItemNumber();
}

int ItemController::getChildNumber(Item* item) const
{
    try {
        return item->getAllSubItems().size();
    }catch(IllegalOperationException&) {
        return 0;
    }
}
