#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

#include "Item.h"
#include "Folder.h"
#include "Movie.h"

namespace play_core {

/*!
  \brief Abstract Item visitor class.

  All the \em composite visitors used in the core package have
  to inherite from ItemVisitor.

  Provide an interface containing each Item specific handle method.
  They are all pure virtual and have to be overriden in subclasses.

  ItemVisitor is an implementation of \em Visitor design pattern.
 */
class ItemVisitor
{
public:
    /*!
      \brief Abstract visit method for Folder.

      \param folder the Folder to visit.
     */
    virtual void visitFolder(Folder* folder) = 0;
    /*!
      \brief Abstract visit method for Movie.

      \param movie the Movie to visit.
     */
    virtual void visitMovie(Movie* movie) = 0;
};

} // namespace

#endif // ITEMVISITOR_H
