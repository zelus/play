#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "item.h"

class ItemManager
{
public:
    ItemManager();
    ItemManager(const ItemManager& itemManager);
    ~ItemManager();

    const Item* findItem(const string& itemName, ItemType itemType = ANY_TYPE, Item* folder = nullptr) const;

    void createMovie(const string& movieName, const string& movieSummary = "", const short movieNotation = 0, Item* folder = nullptr);

private:
    Item* treeRoot_;
};

#endif // ITEMMANAGER_H
