#include "IdItemSearcher.h"
// debug
#include <iostream>

using namespace std;

IdItemSearcher::IdItemSearcher(const std::string& searchedId)
{
    searchedId_ = searchedId;
    foundedItem_ = nullptr;
}

const vector<Item*> IdItemSearcher::getFoundItems() const
{
    vector<Item*> founded_items;
    if(foundedItem_ != nullptr) {
        founded_items.push_back(foundedItem_);
    }
    return founded_items;
}

Item* IdItemSearcher::getFoundItem() const
{
    return foundedItem_;
}

void IdItemSearcher::setSearchedId(const std::string& id)
{
    searchedId_ = id;
}

const string& IdItemSearcher::getSearchedId() const
{
    return searchedId_;
}

int IdItemSearcher::rankItem(Item *item) const
{
    if(item->getId() == searchedId_) {
        cout << "item founded" << endl;
        return 1;
    }
    cout << "test lol" << endl;
    return 0;
}

int IdItemSearcher::rankFolder(Folder* folder) const
{
    return rankItem(folder);
}

int IdItemSearcher::rankMovie(Movie* movie) const
{
    return rankItem(movie);
}

bool IdItemSearcher::sortItem(const int rank, Item* item)
{
    if(rank != 0) {
        foundedItem_ = item;
        return false;
    }
    return true;
}
