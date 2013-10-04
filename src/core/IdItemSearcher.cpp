#include "IdItemSearcher.h"
// debug
#include <iostream>

namespace play_core {

using namespace std;

/*!
  \brief Construct an IdItemSearcher with the given id to search.

  \param searchedId the id to search for.
 */
IdItemSearcher::IdItemSearcher(const std::string& searchedId) : ItemSearcher()
{
    searchedId_ = searchedId;
    foundedItem_ = nullptr;
}

/*!
  \brief Construct a vector containing the result of the search.

  \return a vector containing the search result.

  \note this method is needed for API uniformity, but the returned
  vector will always contain 0 or 1 element (depending if an Item
  has been found or not).
  \see getFoundItem for specific return method (not in the common
  interface).
 */
const vector<Item*> IdItemSearcher::getFoundItems() const
{
    vector<Item*> founded_items;
    if(foundedItem_ != nullptr) {
        founded_items.push_back(foundedItem_);
    }
    return founded_items;
}

/*!
  \return a pointer to an Item if the ID was found, nullptr otherwise.
 */
Item* IdItemSearcher::getFoundItem() const
{
    return foundedItem_;
}

/*!
  \return the current id assigned to the searcher.
 */
const string& IdItemSearcher::getSearchedId() const
{
    return searchedId_;
}

/*!
  \brief Set a new id to search for.

  \param id the new id to search for.
  \note this function allow multiple researches using the
  same IdItemSearcher object.
 */
void IdItemSearcher::setSearchedId(const string& id)
{
    searchedId_ = id;
}

/*!
  \brief Reset the search parameters.

  Previous found Item is erased (and set to nullptr) and
  recursive flag is reset.
 */
void IdItemSearcher::reset()
{
    foundedItem_ = nullptr;
    ItemSearcher::reset();
}

/*!
  \brief Rank the given Folder according to its ID.

  \param folder the Folder to rank.
  \return 1 if the ID match the searched one, 0 otherwise.
 */
int IdItemSearcher::rankFolder(Folder* folder) const
{
    return rankItem(folder);
}

/*!
  \brief Rank the given Movie according to its ID.

  \param movie the Movie to rank.
  \return 1 if the ID match the searched one, 0 otherwise.
 */
int IdItemSearcher::rankMovie(Movie* movie) const
{
    return rankItem(movie);
}

/*!
  \brief Sort the given Item according to the rank provided
  and the search parameters.

  \param rank the rank of the Item to sort.
  \param item the Item to sort.
  \return false if the given rank corresponds to a matching
  between item's ID and searched ID, true otherwhise.

  \note because the visit methods are not overriden, the returned
  value is used to stop the recursion.
 */
bool IdItemSearcher::sortItem(const int rank, Item* item)
{
    if(rank != 0) {
        foundedItem_ = item;
        return false;
    }
    return true;
}

/*!
  \brief Rank the given Item according to its ID.

  IdItemSearcher search Item by ID, regardless to their
  concrete type, each rank method delegates to this method.

  \param item the Item to rank.
  \return 1 if the ID match the searched one, 0 otherwise.
 */
int IdItemSearcher::rankItem(Item *item) const
{
    if(item->getId() == searchedId_) {
        return 1;
    }
    return 0;
}

} // namespace
