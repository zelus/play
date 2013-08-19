/*!
  \file item.h
  \author Gwendal Daniel
  \date 2013-05-01
 */

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "Item.h"
#include "Folder.h"
#include "Movie.h"
#include <string>

/*!
  \brief High level interface providing \em CRUD operations on concrete Items.

  This class is used to store and navigate through an Item hierarchy
  (see Item and derivated classes for further informations).

  A part of the interface provides \em factory methods to create the different kinds of
  Items, the second one provides high-level methods on Item tree management.
 */
class ItemManager
{
public:
    ItemManager();
    ItemManager(const ItemManager& itemManager);
    ~ItemManager();

    vector<Item*> findItem(const string& itemName, Item::ItemType itemType = Item::ItemType::ANY_TYPE, Item* parentFolder = nullptr) const;
    vector<Movie*> findMovie(const string& movieName, Item* parentFolder = nullptr) const;
    vector<Folder*> findFolder(const string& folderName, Item* parentFolder = nullptr) const;

    Movie* createMovie(const string& movieName, Item* parentFolder = nullptr, const string& movieSummary = "", const short movieNotation = 0);
    Folder* createFolder(const string& folderName, Item* parentFolder = nullptr);

    Movie* itemToMovie(Item* item) const;
    Folder* itemToFolder(Item* item) const;

    vector<Movie*> itemListToMovieList(const vector<Item*>& itemList) const;
    vector<Folder*> itemListToFolderList(const vector<Item*>& itemList) const;

    unsigned int getItemNumber() const;

private:

    void recursiveFindItem(const string& itemName, Item::ItemType itemType, Item* parentFolder, vector<Item*>& foundedItems) const;

    Item* treeRoot_;

    unsigned int itemNumber_;
};

#endif // ITEMMANAGER_H
