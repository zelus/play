#include "ItemManager.h"
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
ItemList ItemManager::findItem(const string &itemName, ItemType itemType, Item *parentFolder) const
{
    ItemList foundedItems;
    Item* searchStart = parentFolder;
    if(parentFolder == nullptr) {
        searchStart = treeRoot_;
    }
    recursiveFindItem(itemName,itemType,searchStart,foundedItems);
    return foundedItems;
}

/*!
  \brief Find Movie method.

  This method is a shortcut for findItem call with MOVIE_TYPE property.
  It hides the ItemType enumeration to client. The returned list is then
  casted into a MovieList.
  \param movieName the name of the wanted Movie.
  \param parentFolder the Item to start the research from.
  \return the list of all the Movie corresponding to the given parameters. If no Movie
  corresponds the returned list is empty.
  \exception std::runtime_error if at least one type conversion can't be done.
 */
MovieList ItemManager::findMovie(const string &movieName, Item *parentFolder) const
{
    return itemListToMovieList(findItem(movieName,MOVIE_TYPE,parentFolder));
}

/*!
  \brief Find Folder method.

  This method is a shortcut for findItem call with FOLDER_TYPE property.
  It hides the ItemType enumeration to client. The returned list is then
  casted into a FolderList.
  \param folderName the name of the wanted Folder.
  \param parentFolder the Item to start the research from.
  \return the list of all the Folder corresponding to the given parameters. If no Folder
  corresponds the returned list is empty.
  \exception std::runtime_error if at least one type conversion can't be done.
 */
FolderList ItemManager::findFolder(const string &folderName, Item *parentFolder) const
{
    return itemListToFolderList(findItem(folderName,FOLDER_TYPE,parentFolder));
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
            return new Movie("0",movieName,movieSummary,movieNotation,treeRoot_);
        }
        else {
            return new Movie("0",movieName, movieSummary,movieNotation,parentFolder);
        }
        ++itemNumber_;
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
            return new Folder("0",folderName, treeRoot_);
        }
        else {
            return new Folder("0",folderName, parentFolder);
        }
        ++itemNumber_;
    }catch(logic_error& e) {
        throw e;
    }
}

/*!
  \brief Converts an Item pointer into a Movie pointer.

  \param item the Item to convert.
  \return the casted Movie if the conversion is successful, nullptr otherwhise.
  \exception std::runtime_error if the cast cannot be done (nullptr as given Item
  or not possible dynamic conversion).
 */
Movie* ItemManager::itemToMovie(Item *item) const
{
    Movie* movie =  dynamic_cast<Movie*>(item);
    if(movie == nullptr) {
        throw runtime_error("Unable to cast the given Item into Movie");
    }
    return movie;
}

/*!
  \brief Converts an Item pointer into a Folder pointer.

  \param item the Item to convert.
  \return the casted Folder.
  \exception std::runtime_error if the cast cannot be done (nullptr as given Item
  or not possible dynamic conversion).
 */
Folder* ItemManager::itemToFolder(Item *item) const
{
    Folder* folder = dynamic_cast<Folder*>(item);
    if(folder == nullptr) {
        throw runtime_error("Unable to cast the given Item into Folder");
    }
    return folder;
}

/*!
  \brief Converts an ItemList into a MovieList.

  \param itemList the ItemList to convert.
  \return a MovieList containing the casted Movies.
  \exception std::runtime_error if at least one type conversion can't be done.
*/
MovieList ItemManager::itemListToMovieList(const ItemList &itemList) const
{
    MovieList movieList;
    for(size_t i = 0; i < itemList.size(); ++i) {
        try {
            movieList.push_back(itemToMovie(itemList[i]));
        }catch(runtime_error& e) {
            throw runtime_error("Unable to cast an Item from given ItemList into Movie");
        }
    }
    return movieList;
}

/*!
  \brief Converts an ItemList into a FolderList.

  \param itemList the ItemList to convert.
  \return a FolderList containing the casted Folders.
  \exception std::runtime_error if at least one type conversion can't be done.
*/
FolderList ItemManager::itemListToFolderList(const ItemList &itemList) const
{
    FolderList folderList;
    for(size_t i = 0; i < itemList.size(); ++i) {
        try {
            folderList.push_back(itemToFolder(itemList[i]));
        }catch(runtime_error& e) {
            throw runtime_error("Unable to cast an Item from given ItemList into Folder");
        }
    }
    return folderList;
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
void ItemManager::recursiveFindItem(const string &itemName, ItemType itemType, Item *parentFolder, ItemList &foundedItems) const
{
    ItemList folderChilds;
    try {
        folderChilds = parentFolder->getAllSubItems();
    }catch(logic_error& e) {
        return;
    }
    for(size_t i = 0; i < folderChilds.size(); ++i) {
        if(folderChilds[i]->getName() == itemName && (folderChilds[i]->getType() == itemType || itemType == ANY_TYPE)) {
            foundedItems.push_back(folderChilds[i]);
        }
        recursiveFindItem(itemName,itemType,folderChilds[i],foundedItems);
    }
}

unsigned int ItemManager::getItemNumber() const
{
    return itemNumber_;
}
