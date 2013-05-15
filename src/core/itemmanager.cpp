#include "itemmanager.h"
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
    treeRoot_ = new Folder("_root_");
}

/*!
  \brief Constructs an ItemManager from the given ItemManager.

  The Item's tree root pointer is setted as the root of the
  constructed ItemManager.
  \warning The root of the constructed ItemManager is not a copy
  of the given one. The two ItemManager share and manage the same
  hierarchy.
 */
ItemManager::ItemManager(const ItemManager &itemManager)
{
    treeRoot_ = itemManager.treeRoot_;
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

  Searches the Item with the given name and type in all or part of the
  Item tree.
  \param itemName the name of the wanted Item.
  \param itemType the type of the wanted Item.
  \param parentFolder the Item to start the research from. It allow research
  in subtrees, wich is faster than a complete research.
  \return the Item pointer if the wanted Item is in the Item tree, nullptr
  otherwhise.
  \note The Item is returned through the global interface Item, to get
  concrete Item types object use the appropriated find method. You can also
  use this method with the appropriated cast method.
 */
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

/*!
  \brief Find Movie method.

  This method is a shortcut for findItem call with MOVIE_TYPE property.
  It hides the ItemType enumeration to client. The returned object is then
  casted into a Movie pointer.
  \param movieName the name of the wanted Movie.
  \param parentFolder the Item to start the research from.
  \return the Movie pointer if the Movie is in the Item tree, nullptr otherwhise.
  \note If for some reasons the type conversion can't be done, it returns nullptr.
 */
Movie* ItemManager::findMovie(const string &movieName, Item *parentFolder) const
{
    return itemToMovie(findItem(movieName,MOVIE_TYPE,parentFolder));
}

/*!
  \brief Find Folder method.

  This method is a shortcut for findItem call with FOLDER_TYPE property.
  It hides the ItemType enumeration to client. The returned object is then
  casted into a Folder pointer.
  \param folderName the name of the wanted Folder.
  \param parentFolder the Item to start the research from.
  \return the Folder pointer if the Folder is in the Item tree, nullptr otherwhise.
  \note If for some reasons the type conversion can't be done, it returns nullptr.
 */
Folder* ItemManager::findFolder(const string &folderName, Item *parentFolder) const
{
    return itemToFolder(findItem(folderName, FOLDER_TYPE, parentFolder));
}

/*!
  \brief Creates a new Movie from the given parameters.

  \param movieName the name of the Movie to create.
  \param parentFolder the Item containing the Movie to create.
  \param movieSummary the summary of the Movie to create.
  \param movieNotation the notation of the Movie to create.
  \return a pointer to the created Movie.
  \exception std::logic_error if parent management fails during the creation.
 */
Movie* ItemManager::createMovie(const string &movieName, Item* parentFolder, const string &movieSummary, const short movieNotation)
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

/*!
  \brief Creates a new Folder from the given parameters.

  \param folderName the name of the Folder to create.
  \param parentFolder the Item containing the Folder to create.
  \return a pointer to the created Folder.
  \exception std::logic_error if parent management fails during the creation.
 */
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

/*!
  \brief Converts an Item pointer into a Movie pointer.

  \param item the Item to convert.
  \return the casted Movie if the conversion is successful, nullptr otherwhise.
 */
Movie* ItemManager::itemToMovie(Item *item) const
{
    return dynamic_cast<Movie*>(item);
}

/*!
  \brief Converts an Item pointer into a Folder pointer.

  \param item the Item to convert.
  \return the casted Folder if the conversion is successful, nullptr otherwhise.
 */
Folder* ItemManager::itemToFolder(Item *item) const
{
    return dynamic_cast<Folder*>(item);
}
