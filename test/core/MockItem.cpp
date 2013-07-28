#include "MockItem.h"
#include <iostream>
/*
  MockItem constructor with basic Item constructor
  parameters. The parameter isDeleted is used
  to know if the MockItem destructor has been
  called.
 */
MockItem::MockItem(const string &name, ItemType type, Item *parent, bool *isDeleted) : Item(name,type,parent)
{
    isDeleted_ = isDeleted;
    *isDeleted_ = false;
}

/*
  MockItem destructor. Sets the value pointed
  by the isDeleted pointer to true.
 */
MockItem::~MockItem()
{
    *isDeleted_ = true;
}
