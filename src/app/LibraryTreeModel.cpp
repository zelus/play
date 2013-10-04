#include "LibraryTreeModel.h"
// debug
#include <iostream>

LibraryTreeModel::LibraryTreeModel(ItemController& itemController, QObject *parent) :
    QAbstractItemModel(parent), itemController_(itemController)
{

}

LibraryTreeModel::~LibraryTreeModel()
{

}

QVariant LibraryTreeModel::data(const QModelIndex& index, int role) const
{
    //std::cout << "call LibraryTreeModel::data" << std::endl;
    if(!index.isValid()) {
        return QVariant();
    }
    if(role != Qt::DisplayRole) {
        return QVariant();
    }
    // Investigate pro and cons for storing the Item pointer in the
    // index. (faster but not really clear for encapsulation.
    play_core::Item* item = static_cast<play_core::Item*>(index.internalPointer());
    return itemController_.getData(item,index.column());
}

QVariant LibraryTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section) {
            case 0 :
            return QString(tr("Title"));
        }
    }
    return QVariant();
}

QModelIndex LibraryTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    std::cout << "call LibraryTreeModel::index(" << row << "," << column << ")" << std::endl;
    if(!hasIndex(row,column,parent)) {
        std::cout << "no index" << std::endl;
        return QModelIndex();
    }
    const play_core::Item* parent_item;
    if(!parent.isValid()) {
        std::cout << "LibraryTreeModel::index, invalid parent" << std::endl;
        // invalide parent = top level, à traiter avec null dans le controller sans doute
        parent_item = itemController_.getRootItem();
    }
    else {
        std::cout << "LibraryTreeModel::index, valid parent" << std::endl;
        parent_item = static_cast<play_core::Item*>(parent.internalPointer());
        // todo : une méthode dans Item qui permet de retourner le ième fils d'un item
        // plus simple que l'accès au tableau dans sa globalité
    }
    play_core::Item* child_item = nullptr;
    const std::vector<play_core::Item*>& children = parent_item->getChildren();
    /*
        Can do the cast without any problem : if the row value is negative then
        the hasIndex method has failed and an invalid QModelIndex has been returned.
    */
    if(children.size() < static_cast<unsigned int>(row)) {
        std::cout << "size error" << std::endl;
        // Invalid item
        return QModelIndex();
    }
    else {
        // The child exits
        child_item = children[row];
        std::cout << "create index for " << child_item->getName() << std::endl;
        return createIndex(row,column,child_item);
    }
    return QModelIndex();
}

QModelIndex LibraryTreeModel::parent(const QModelIndex& child) const
{
    std::cout << "call LibraryTreeModel::parent" << std::endl;
    if(!child.isValid()) {
        std::cout << "invalid child" << std::endl;
        return QModelIndex();
    }
    play_core::Item* child_item = static_cast<play_core::Item*>(child.internalPointer());
    std::cout << "LibraryTreeModel::parent child = " << child_item->getName() << std::endl;
    play_core::Item* parent_item = itemController_.getParent(child_item);
    if(parent_item == nullptr) {
        std::cout << "LibraryTreeModel::parent parent_item == nullptr" << std::endl;
        return QModelIndex();
    }
    else {
        // pb ici, trouver la position de l'item par rapport à
        // son parent, obligatoire pour l'argument row
        // 0 comme colonne : seules les premiers éléments (le nom en gros
        // dans un arbre peuvent avoir des enfants, convention).
        return createIndex(parent_item->getChildIndex(child_item),0,parent_item);
    }
}

int LibraryTreeModel::rowCount(const QModelIndex& parent) const
{
    std::cout << "call LibraryTreeModel::rowCount" << std::endl;
    // convention, les éléments autres que les nom de ligne ne peuvent
    // pas avoir de fils dans les arbres
    if(parent.column() > 0) {
        return 0;
    }
    if(!parent.isValid()) {
        return itemController_.getTopLevelItemNumber();
    }
    else {
        play_core::Item* parent_item = static_cast<play_core::Item*>(parent.internalPointer());
        return itemController_.getChildNumber(parent_item);
    }
}

int LibraryTreeModel::columnCount(const QModelIndex&) const
{
    std::cout << "call LibraryTreeModel::columnCount" << std::endl;
    // on affiche que le nom des items
    return 1;
}
