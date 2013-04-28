#include "itemmanager.h"
#include <stdexcept>

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

const Item* ItemManager::findItem(const string &itemName, ItemType itemType, Item *parentFolder) const
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
        const Item* recursiveSearchResult = findItem(itemName,itemType,folderChilds[i]);
        if(recursiveSearchResult != nullptr) {
            return recursiveSearchResult;
        }
    }
}

void ItemManager::createMovie(const string &movieName, const string &movieSummary, const short movieNotation, Item *parentFolder)
{
    try {
        Movie* movie = new Movie(movieName,parentFolder);
        movie->setSummary(movieSummary);
        movie->setNotation(movieNotation);
    }catch(logic_error& e) {
        throw e;
    }
}
