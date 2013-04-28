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
    if(parentFolder == nullptr) {
        /*
         * Search from tree root
         */
    }
    else {
        /*
         * Search in the item below the given folder
         */

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
