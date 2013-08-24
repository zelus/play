#ifndef ITEMSEARCHER_H
#define ITEMSEARCHER_H

#include "ItemVisitor.h"

class ItemSearcher : public ItemVisitor
{
public:
    ItemSearcher();

    void visitFolder(Folder* folder);
    void visitMovie(Movie* movie);

    virtual const std::vector<Item*> getFoundItems() const;

protected:
    virtual int rankFolder(Folder* folder) const;
    virtual int rankMovie(Movie* movie) const;
    virtual bool sortItem(const int rank, Item* item);

};

#endif // ITEMSEARCHER_H
