#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

#include "Item.h"
#include "Folder.h"
#include "Movie.h"

class ItemVisitor
{
public:
    ItemVisitor();

    virtual void visitFolder(Folder* folder) = 0;
    virtual void visitMovie(Movie* movie) = 0;
};

#endif // ITEMVISITOR_H
