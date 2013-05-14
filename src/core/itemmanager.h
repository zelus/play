#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "item.h"
#include "folder.h"
#include "movie.h"
#include "common.h"
#include <string>

class ItemManager
{
public:
    ItemManager();
    ItemManager(const ItemManager& itemManager);
    ~ItemManager();

    Item* findItem(const string& itemName, ItemType itemType = ANY_TYPE, Item* parentFolder = nullptr) const;
    Movie* findMovie(const string& movieName, Item* parentFolder = nullptr) const;
    Folder* findFolder(const string& folderName, Item* parentFolder = nullptr) const;

    Movie* createMovie(const string& movieName, const string& movieSummary = "", const short movieNotation = 0, Item* parentFolder = nullptr);
    Folder* createFolder(const string& folderName, Item* parentFolder = nullptr);

private:
    Item* treeRoot_;
};

#endif // ITEMMANAGER_H
