#ifndef IDITEMSEARCHER_H
#define IDITEMSEARCHER_H

#include "ItemSearcher.h"
#include "Item.h"
#include <vector>

class IdItemSearcher : public ItemSearcher
{
public:
    IdItemSearcher(const std::string& searchedId);

    const std::vector<Item*> getFoundItems() const;
    Item* getFoundItem() const;

    void setSearchedId(const std::string& id);
    const std::string& getSearchedId() const;

protected:
    int rankItem(Item* item) const;
    int rankFolder(Folder* folder) const;
    int rankMovie(Movie* movie) const;
    bool sortItem(const int rank, Item* item);

private:
    std::string searchedId_;
    Item* foundedItem_;
};

#endif // IDITEMSEARCHER_H
