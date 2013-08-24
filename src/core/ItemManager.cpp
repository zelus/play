#include "ItemManager.h"
#include "Movie.h"
#include "Folder.h"
#include "CoreException.h"
#include <sstream>

// debug
#include <iostream>

using namespace std;

/*!
  \brief Constructs a new ItemManager.

  The root representing the managed tree is created with the
  generic name \em _root_.

  \note The root Item is the only one in the hierarchy to have a parent
  setted to nullptr.
 */
ItemManager::ItemManager()
{
    treeRoot_ = new Folder("0", "_root_");
    itemNumber_ = 0;
}

/*!
  \brief Deletes the ItemManager and the Item representing the herarchy tree.

  All the Item contained in the tree are recursively deleted (see Folder::~Folder
  for further informations).
  \warning In case of root sharing between ItemManagers, this deletion invalidates
  the other ItemManagers referencing the root.
 */
ItemManager::~ItemManager()
{
    delete treeRoot_;
}

Item* ItemManager::createFolder(const string &name, Item *parent)
{
    Item* local_parent = treeRoot_;
    if(parent != nullptr) {
        local_parent = parent;
    }
    ostringstream oss;
    oss << ++itemNumber_;
    try {
        return new Folder(oss.str(),name,local_parent);
    }catch(CoreException& e) {
        --itemNumber_;
        throw;
    }
}

Item* ItemManager::createMovie(const string &name, Item *parent, const string &summary, const short notation)
{
    Item* local_parent = treeRoot_;
    if(parent != nullptr) {
        local_parent = parent;
    }
    ostringstream oss;
    oss << ++itemNumber_;
    try {
        return new Movie(oss.str(),name,summary,notation,local_parent);
    }catch(CoreException& e) {
        --itemNumber_;
        throw;
    }
}

void ItemManager::deleteItem(Item* item)
{
    delete item;
    --itemNumber_;
}

unsigned int ItemManager::getItemNumber() const
{
    return itemNumber_;
}
