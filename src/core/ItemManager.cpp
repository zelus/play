#include "ItemManager.h"
#include "Movie.h"
#include "Folder.h"
#include "CoreException.h"
#include "IllegalOperationException.h"
#include "InternalErrorException.h"
#include <sstream>

// debug
#include <iostream>

using namespace std;

/*!
  \brief Constructs a new ItemManager.

  The root representing the managed tree is created with the
  generic name \em _root_.
  The Item counter is initialized.

  \note The root Item is the only one in the hierarchy to have a parent
  setted to nullptr.
 */
ItemManager::ItemManager()
{
    treeRoot_ = new Folder("0", "_root_");
    itemNumber_ = 0;
}

/*!
  \brief Deletes the ItemManager and the Item representing the hierarchy tree.

  All the Item contained in the tree are recursively deleted (see Folder::~Folder
  for further informations).
 */
ItemManager::~ItemManager()
{
    delete treeRoot_;
}

/*!
  \brief Construct a Folder from the given parameters.

  The Folder is constructed with a valid and unique ID calculated from
  the existing Item tree.

  The Item counter is updated.

  \param name the name of the Folder.
  \param parent the parent of the Folder. If set to nullptr the created
  Folder is appended to the root Item.
  \return the created Folder.
  \exception IllegalOperationException if the given parent cannot handle subItems.
  \exception InternalErrorException if an ID consistency issue is found.
 */
Item* ItemManager::createFolder(const string &name, Item* parent)
{
    Item* local_parent = treeRoot_;
    if(parent != nullptr) {
        local_parent = parent;
    }
    ostringstream oss;
    oss << ++itemNumber_;
    try {
        return new Folder(oss.str(),name,local_parent);
    }catch(IllegalOperationException& e) {
        --itemNumber_;
        throw;
    }
    catch(CoreException& e) {
        stringstream ss;
        ss << "Generated ID for Folder " << name << " (" << itemNumber_ << ") is not unique";
        --itemNumber_;
        throw InternalErrorException(ss.str(),__FILE__,__LINE__);
    }
}

/*!
  \brief Construct a Movie from the given parameters.

  The Movie is constructed with a valid and unique ID calculated from
  the existing Item tree.

  The Item counter is updated.

  \param name the name of the Movie.
  \param parent the parent of the Movie. If set to nullptr the created
  Folder is appended to the root Item.
  \param summary the summary of the Movie.
  \param notation the notation of the Movie.
  \return the created Movie.
  \exception IllegalOperationException if the given parent cannot handle subItems.
  \exception InternalErrorException if an ID consistency issue is found.
 */
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
    }catch(IllegalOperationException& e) {
        --itemNumber_;
        throw;
    }catch(CoreException& e) {
        stringstream ss;
        ss << "Generated ID for Movie " << name << " (" << itemNumber_ << ") is not unique";
        --itemNumber_;
        throw InternalErrorException(ss.str(),__FILE__,__LINE__);
    }
}

/*!
  \brief Delete the given Item.

  The Item counter is updated.

  \param item the Item to delete.
 */
void ItemManager::deleteItem(Item* item)
{
    delete item;
    --itemNumber_;
}

/*!
  \return the number of Item registered to the ItemManager.
 */
unsigned int ItemManager::getItemNumber() const
{
    return itemNumber_;
}

/*!
  \return the root Item of the Item tree.
  \note This Item doesn't store any information and should be used only
  for value comparisons.
 */
Item* ItemManager::getRootItem() const
{
    return treeRoot_;
}

/*!
  \return the number of top level Item registered to the ItemManager.
 */
unsigned int ItemManager::getTopLevelItemNumber() const
{
    return treeRoot_->getAllSubItems().size();
}
