#include "MockItem.h"
#include "ItemVisitor.h"
#include <iostream>
/*
  MockItem constructor with basic Item constructor
  parameters. The parameter isDeleted is used
  to know if the MockItem destructor has been
  called.
 */
MockItem::MockItem(const string &name, bool& isDeleted) : Item(name), isDeleted_(isDeleted)
{

}

/*
  MockItem destructor. Sets the value pointed
  by isDeleted to true.
 */
MockItem::~MockItem()
{
    isDeleted_ = true;
}

/*
  Needed override to allow MockItem instanciation.
 */
void MockItem::accept(ItemVisitor&)
{

}
