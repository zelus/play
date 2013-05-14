#include "itemmanager.h"
#include <stdexcept>

// debug
#include <iostream>

ItemManager::ItemManager()
{
    treeRoot_ = new Folder("_root_");
}

ItemManager::ItemManager(const ItemManager &itemManager)
{
    treeRoot_ = itemManager.treeRoot_;
}

ItemManager::~ItemManager()
{
    delete treeRoot_;
}

Item* ItemManager::findItem(const string &itemName, ItemType itemType, Item *parentFolder) const
{
    Item* searchStart = parentFolder;
    if(parentFolder == nullptr) {
        searchStart = treeRoot_;
    }
    ItemList folderChilds;
    try {
        folderChilds = searchStart->getAllSubItems();
    }catch(logic_error& e) {
        return nullptr;
    }
    for(size_t i = 0; i < folderChilds.size(); ++i) {
        if(folderChilds[i]->getName() == itemName && folderChilds[i]->getType() == itemType) {
            return folderChilds[i];
        }
        Item* recursiveSearchResult = findItem(itemName,itemType,folderChilds[i]);
        if(recursiveSearchResult != nullptr) {
            return recursiveSearchResult;
        }
    }
    return nullptr;
}

Movie* ItemManager::findMovie(const string &movieName, Item *parentFolder) const
{
    return dynamic_cast<Movie*>(findItem(movieName,MOVIE_TYPE,parentFolder));
}

Folder* ItemManager::findFolder(const string &folderName, Item *parentFolder) const
{
    return dynamic_cast<Folder*>(findItem(folderName, FOLDER_TYPE, parentFolder));
}

Movie* ItemManager::createMovie(const string &movieName, const string &movieSummary, const short movieNotation, Item *parentFolder)
{
    try {
        if(parentFolder == nullptr) {
            return new Movie(movieName,movieSummary,movieNotation,treeRoot_);
        }
        else {
            return new Movie(movieName, movieSummary,movieNotation,parentFolder);
        }
    }catch(logic_error& e) {
        throw e;
    }
}

Folder* ItemManager::createFolder(const string &folderName, Item *parentFolder)
{
    try {
        if(parentFolder == nullptr) {
            return new Folder(folderName, treeRoot_);
        }
        else {
            return new Folder(folderName, parentFolder);
        }
    }catch(logic_error& e) {
        throw e;
    }
}
