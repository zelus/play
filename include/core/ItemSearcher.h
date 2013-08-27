#ifndef ITEMSEARCHER_H
#define ITEMSEARCHER_H

#include "ItemVisitor.h"
#include "Item.h"
#include "Movie.h"
#include "Folder.h"
#include <vector>

/*!
  \brief Base searcher class.

  All the searcher used in the core package have to inherite
  from ItemSearcher.

  ItemSearcher provides default and common behaviour for
  visit methods (associated to each Item type) that allow
  basic subclass to just override rank methods.

  ItemSearcher default behavious only provides descendant research
  (it cannot find Item at a higher level than the one provided by the search
  method parameter. If such a behavious is needed by a specific subclass it
  needs to override the visit methods.
 */
class ItemSearcher : public ItemVisitor
{
public:
    ItemSearcher();

    void visitFolder(Folder* folder);
    void visitMovie(Movie* movie);
    virtual void search(Item* item);

    /*!
      \return eturn the list of found Items matching the
      rank methods.
    */
    virtual const std::vector<Item*> getFoundItems() const = 0;

protected:
    virtual void reset();
    /*!
      \brief Rank the given Folder according to the search
      parameters.

      \param folder the Folder to rank.
      \return the rank calculated for the Folder.
    */
    virtual int rankFolder(Folder* folder) const = 0;

    /*!
      \brief Rank the given Movie according to the search
      parameters.

      \param movie the Movie to rank.
      \return the rank calculated for the Movie.
     */
    virtual int rankMovie(Movie* movie) const = 0;
    /*!
      \brief Sort the given Item according to the rank provided
      and the search parameters.

      This method is a hook for custom research on multi-criteria
      (for example a relevancy research).

      \param rank the rank of the Item to sort.
      \param item the Item to sort.

      \return true if the research needs to continue, false otherwise.

      \note the return value is used in default visit methods to
      set the continueRecursion flag.
     */
    virtual bool sortItem(const int rank, Item* item) = 0;

    /*!
      The flag used to stop the recursion when the search
      is complete.
     */
    bool continueRecursiveSearch_;
};

#endif // ITEMSEARCHER_H
