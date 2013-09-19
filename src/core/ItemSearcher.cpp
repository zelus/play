#include "ItemSearcher.h"
#include <vector>
// debug
#include <iostream>

using namespace std;

/*!
  \brief Construct an ItemSearcher.

  Initialize the recursion flag to true (enable recursion).
 */
ItemSearcher::ItemSearcher() : ItemVisitor()
{
    continueRecursiveSearch_ = true;
}

/*!
  \brief Basic visit method for Folder.

  The Folder is ranked first and then the accept method
  is called to each one of its children.

  The loop ends when all the children have been processed
  or if the recursion flag has been put to false.

  \param folder the folder to visit.
 */
void ItemSearcher::visitFolder(Folder* folder)
{
    continueRecursiveSearch_ = sortItem(rankFolder(folder),folder);
    if(!continueRecursiveSearch_) {
        return;
    }
    const vector<Item*>& folder_children = folder->getAllSubItems();
    vector<Item*>::const_iterator it;
    for(it = folder_children.begin(); it != folder_children.end(); ++it) {
        if(continueRecursiveSearch_) {
            (*it)->accept(*this);
        }
        else {
            return;
        }
    }
}

/*!
  \brief Basic visit method for Movie.

  The Movie is ranked and the recursion flag is updated.

  \param movie the Movie to visit.
 */
void ItemSearcher::visitMovie(Movie* movie)
{
    continueRecursiveSearch_ = sortItem(rankMovie(movie),movie);
}

/*!
  \brief Basic search method.

  Cleans the recursion flag and launch a new research.

  \param item the Item to start the research from.
 */
void ItemSearcher::search(Item* item)
{
    reset();
    item->accept(*this);
}

/*!
  \brief Basic reset method.

  Reset the variable member to start a new research from
  scratch.

  \note this method needs to be override if the inherited class
  store its result (otherwise the returned value correctness cannot
  be ensured.
 */
void ItemSearcher::reset()
{
    continueRecursiveSearch_ = true;
}
