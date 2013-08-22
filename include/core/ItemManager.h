/*!
  \file item.h
  \author Gwendal Daniel
  \date 2013-05-01
 */

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "Item.h"
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
    ItemManager(const ItemManager& itemManager) = delete;
    ItemManager& operator=(const ItemManager&) = delete;
    ~ItemManager();

    vector<Item*> searchItem(const string& itemName, ItemType itemType = ItemType::ANY_TYPE, Item* parentFolder = nullptr) const;

    unsigned int getItemNumber() const;

private:

    void recursiveFindItem(const string& itemName, ItemType itemType, Item* parentFolder, vector<Item*>& foundedItems) const;

    Item* treeRoot_;

    unsigned int itemNumber_;
};

#endif // ITEMMANAGER_H
