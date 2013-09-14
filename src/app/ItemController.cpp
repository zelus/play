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

}

int ItemController::getTopLevelItemNumber() const
{

}

int ItemController::getChildNumber(Item* item) const
{
    return item->getAllSubItems().size();
}
