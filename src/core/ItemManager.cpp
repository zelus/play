#include "ItemManager.h"
#include "Movie.h"
#include "Folder.h"
#include "CoreException.h"
#include <stdexcept>
#include <sstream>

// debug
#include <iostream>

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

Item* ItemManager::searchItemWithId(const string& id, Item* parent) const
{
    Item* search_start = parent;
    if(parent == nullptr) {
        search_start = treeRoot_;
    }
    return recursiveFindItemWithId(id,search_start);
}

/*!
  \brief Generic find Item method.

  Searches Items with given name and type in all or part of the
  Item tree.
  \param itemName the name of the wanted Item.
  \param itemType the type of the wanted Item.
  \param parentFolder the Item to start the research from. It allow research
  in subtrees, wich is faster than a complete research.
  \return the list of all the Item corresponding to the given parameters. If no Item
  corresponds the returned list is empty.
  \note The Item is returned through the global interface Item, to get
  concrete Item types object use the appropriated find method. You can also
  use this method with the appropriated cast method.
  \note If ANY_TYPE is given as itemType all the items corresponding to the other
  parameters are returned.
 */
vector<Item*> ItemManager::searchItem(const string &itemName, ItemType itemType, Item *parentFolder) const
{
    vector<Item*> foundedItems;
    Item* searchStart = parentFolder;
    if(parentFolder == nullptr) {
        searchStart = treeRoot_;
    }
    recursiveFindItem(itemName,itemType,searchStart,foundedItems);
    return foundedItems;
}

unsigned int ItemManager::getItemNumber() const
{
    return itemNumber_;
}

/*!
  \brief Private findItemWithId method.

  Searches the Item with the given ID recursively in all the descendants of
  the from Item.

  \param id the ID of the wanted item.
  \param from the Item to start the research from.

  \return the founded Item if it exists, nullptr otherwise.
  \note If the tree is not consistent (manual Item addition with double ID), the returned
  Item is the first found.
 */
Item* ItemManager::recursiveFindItemWithId(const string& id, Item* from) const {
    vector<Item*> from_children;
    try {
        from_children = from->getAllSubItems();
    }catch(CoreException& e) {
        return nullptr;
    }
    vector<Item*>::iterator it;
    for(it = from_children.begin(); it != from_children.end(); ++it) {
        if((*it)->getId() == id) {
            return *it;
        }
        else {
            Item* local_founded =  recursiveFindItemWithId(id,(*it));
            if(local_founded != nullptr) {
                return local_founded;
            }
        }
    }
    return nullptr;
}

/*!
  \brief Private findItem method.

  Searches Items with given name and type in all or part of the
  Item tree. All matching Items are put recursively in the foundedItems list.
  This method hides the recursive list management to client.
  \param itemName the name of the wanted Item.
  \param itemType the type of the wanted Item.
  \param parentFolder the Item to start the research from. It allow research
  in subtrees, wich is faster than a complete research.
  \param foundedItems the list containing the foundedItems. This list is a parameter
  (and not the return value of the method) because of the recursive aspect of the search
  process.
*/
void ItemManager::recursiveFindItem(const string &itemName, ItemType itemType, Item *parentFolder, vector<Item*> &foundedItems) const
{
    vector<Item*> folderChilds;
    try {
        folderChilds = parentFolder->getAllSubItems();
    }catch(logic_error& e) {
        return;
    }
    for(size_t i = 0; i < folderChilds.size(); ++i) {
        if(folderChilds[i]->getName() == itemName && (folderChilds[i]->getType() == itemType || itemType == ItemType::ANY_TYPE)) {
            foundedItems.push_back(folderChilds[i]);
        }
        recursiveFindItem(itemName,itemType,folderChilds[i],foundedItems);
    }
}


