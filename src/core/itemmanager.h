#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "item.h"
#include "movie.h"
#include "common.h"
#include <string>

class ItemManager
{
public:
    ItemManager();
    ItemManager(const ItemManager& itemManager);
    ~ItemManager();

    const Item* findItem(const string& itemName, ItemType itemType = ANY_TYPE, Item* parentFolder = nullptr) const;

    Movie* createMovie(const string& movieName, const string& movieSummary = "", const short movieNotation = 0, Item* parentFolder = nullptr);

private:
    Item* treeRoot_;
};

#endif // ITEMMANAGER_H
