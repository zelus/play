#include "itemmanager.h"

ItemManager::ItemManager()
{
}

ItemManager::ItemManager(const ItemManager &itemManager)
{
    treeRoot_ = itemManager.treeRoot_;
}

ItemManager::~ItemManager()
{
    delete treeRoot_;
}

const Item* ItemManager::findItem(const string &itemName, ItemType itemType, Item *folder) const
{
    // TODO
    return nullptr;
}

void ItemManager::createMovie(const string &movieName, const string &movieSummary, const short movieNotation, Item *folder)
{
    // TODO
}
