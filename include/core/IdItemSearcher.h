#ifndef IDITEMSEARCHER_H
#define IDITEMSEARCHER_H

#include "ItemSearcher.h"
#include "Item.h"
#include <string>
#include <vector>

/*!
  \brief Searcher based on ID comparisons.

  Search an Item with the parametrized ID. The result of
  such a search is unique and the tree is not entirely covered :
  the search stops at the first matching.

  To work well, IdItemSearcher needs a ID-consistent Item
  tree.
 */
class IdItemSearcher : public ItemSearcher
{
public:
    IdItemSearcher(const std::string& searchedId);

    const std::vector<Item*>    getFoundItems()                         const;
    Item*                       getFoundItem()                          const;
    const std::string&          getSearchedId()                         const;

    void                        setSearchedId(const std::string& id);

protected:
    void                        reset();
    int                         rankFolder(Folder* folder)              const;
    int                         rankMovie(Movie* movie)                 const;
    bool                        sortItem(const int rank, Item* item);

private:
    int                         rankItem(Item* item)                    const;

    std::string searchedId_;
    Item* foundedItem_;
};

#endif // IDITEMSEARCHER_H
