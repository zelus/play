#include "LibraryTreeModel.h"

LibraryTreeModel::LibraryTreeModel(ItemController& itemController, QObject *parent) :
    QAbstractItemModel(parent), itemController_(itemController)
{

}

LibraryTreeModel::~LibraryTreeModel()
{

}

QVariant LibraryTreeModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    if(role != Qt::DisplayRole) {
        return QVariant();
    }
    // Investigate pro and cons for storing the Item pointer in the
    // index. (faster but not really clear for encapsulation.
    Item* item = static_cast<Item*>(index.internalPointer());
    return itemController_.getData(item,index.column());
}

QModelIndex LibraryTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if(!hasIndex(row,column,parent)) {
        return QModelIndex();
    }
    Item* parent_item;
    if(!parent.isValid()) {
        // invalide parent = top level, à traiter avec null dans le controller sans doute
    }
    else {
        parent_item = static_cast<Item*>(parent.internalPointer());
        // todo : une méthode dans Item qui permet de retourner le ième fils d'un item
        // plus simple que l'accès au tableau dans sa globalité
        Item* child_item = nullptr;
        const std::vector<Item*>& children = parent_item->getAllSubItems();
        if(children.size() > row) {
            // Invalid item
            return QModelIndex();
        }
        else {
            // The child exits
            child_item = children[row];
        }
        if(child_item != nullptr) {
            return createIndex(row,column,child_item);
        }
        else {
            return QModelIndex();
        }
    }
}

QModelIndex LibraryTreeModel::parent(const QModelIndex& child) const
{
    if(child.isValid()) {
        return QModelIndex();
    }
    Item* child_item = static_cast<Item*>(child.internalPointer());
    Item* parent_item = itemController_.getParent(child_item);
    if(parent_item == nullptr) {
        return QModelIndex();
    }
    else {
        // pb ici, trouver la position de l'item par rapport à
        // son parent, obligatoire pour l'argument row
        // 0 comme colonne : seules les premiers éléments (le nom en gros
        // dans un arbre peuvent avoir des enfants, convention).
        return createIndex(parent_item->index,0,parent_item);
    }
}

int LibraryTreeModel::rowCount(const QModelIndex& parent) const
{
    // convention, les éléments autres que les nom de ligne ne peuvent
    // pas avoir de fils dans les arbres
    if(parent.column() > 0) {
        return 0;
    }
    if(!parent.isValid()) {
        return itemController_.getTopLevelItemNumber();
    }
    else {
        Item* parent_item = static_cast<Item*>(parent.internalPointer());
        return itemController_.getChildNumber(parent_item);
    }
}

int LibraryTreeModel::columnCount(const QModelIndex& parent) const
{
    // on affiche que le nom des items
    return 1;
}
