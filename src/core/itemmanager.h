/*!
  \file item.h
  \author Gwendal Daniel
  \date 2013-05-01
 */

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "item.h"
#include "folder.h"
#include "movie.h"
#include "common.h"
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

    Item* findItem(const string& itemName, ItemType itemType = ANY_TYPE, Item* parentFolder = nullptr) const;
    Movie* findMovie(const string& movieName, Item* parentFolder = nullptr) const;
    Folder* findFolder(const string& folderName, Item* parentFolder = nullptr) const;

    Movie* createMovie(const string& movieName, Item* parentFolder = nullptr, const string& movieSummary = "", const short movieNotation = 0);
    Folder* createFolder(const string& folderName, Item* parentFolder = nullptr);

    Movie* itemToMovie(Item* item) const;
    Folder* itemToFolder(Item* item) const;

private:
    Item* treeRoot_;
};

#endif // ITEMMANAGER_H
