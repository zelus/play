#ifndef MOCK_ITEM_H
#define MOCK_ITEM_H

#include "item.h"
#include "common.h"
#include <string>

using namespace std;

/*
  A mock of the Item class to test the
  Folder destructor (subItems destructors
  calls).
 */
class MockItem : public Item
{
public:
    MockItem(const string& name, ItemType type, Item* parent, bool* isDeleted);
    ~MockItem();
private:
    bool* isDeleted_;
};

#endif // MOCK_ITEM_H
