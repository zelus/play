#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

#include "Item.h"
#include "Folder.h"
#include "Movie.h"

class ItemVisitor
{
public:
    ItemVisitor();

    virtual void visitItem(Item* item);
    virtual void visitFolder(Folder* folder);
    virtual void visitMovie(Movie* movie);
};

#endif // ITEMVISITOR_H
