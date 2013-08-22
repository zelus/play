#include "MockItem.h"
#include <iostream>
/*
  MockItem constructor with basic Item constructor
  parameters. The parameter isDeleted is used
  to know if the MockItem destructor has been
  called.
 */
MockItem::MockItem(const string& id, const string &name, ItemType type, Item *parent, bool& isDeleted) : Item(id,name,type,parent), isDeleted_(isDeleted)
{

}

/*
  MockItem destructor. Sets the value pointed
  by the isDeleted pointer to true.
 */
MockItem::~MockItem()
{
    isDeleted_ = true;
}
