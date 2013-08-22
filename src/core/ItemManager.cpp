#include "ItemManager.h"
#include "Movie.h"
#include "Folder.h"
#include <stdexcept>

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


