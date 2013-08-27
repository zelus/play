#include "MockItemVisitor.h"

/*
  MockItemVisitor constructor.
  The parameter calledMethod is used to know which "visit" method
  has been called by the Item::accept method.

  calledMethod_ values are :
    - 1 if visitFolder has been called.
    - 2 if visitMovie has been called.
 */
MockItemVisitor::MockItemVisitor(int& calledMethod) : ItemVisitor(), calledMethod_(calledMethod)
{
    calledMethod_ = 0;
}

/*
  Set the calledMethod value to 1.
  See constructor details for explanation about calledMethod values.
 */
void MockItemVisitor::visitFolder(Folder*)
{
    calledMethod_ = 1;
}

/*
  Set the calledMethod value to 2.
  See constructor details for explanation about calledMethod values.
 */
void MockItemVisitor::visitMovie(Movie*)
{
    calledMethod_ = 2;
}
