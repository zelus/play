#include "ItemController.h"
#include "IllegalOperationException.h"
#include <QString>
// debug
#include <iostream>

ItemController::ItemController(play_core::TreeContext& treeContext) : treeContext_(treeContext)
{

}

QVariant ItemController::getData(play_core::Item* item, int field) const
{
    std::cout << "call ItemController::data" << std::endl;
    switch(field) {
        case 0 :
        return QString::fromStdString(item->getName());
    }
    return QVariant();
}

play_core::Item* ItemController::getParent(play_core::Item* item) const
{
    play_core::Item* item_parent = item->getParent();
    // parent du parent pour supprimer l'item racine
    if(item_parent == nullptr || item_parent->getParent() == nullptr) {
        return nullptr;
    }
    return item_parent;
}

const play_core::Item* ItemController::getRootItem() const
{
    return treeContext_.getRootItem();
}

int ItemController::getTopLevelItemNumber() const
{
    return treeContext_.getTopLevelItemCount();
}

int ItemController::getChildNumber(play_core::Item* item) const
{
    try {
        return item->childCount();
    }catch(play_core::IllegalOperationException&) {
        return 0;
    }
}
