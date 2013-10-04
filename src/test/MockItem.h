#ifndef MOCK_ITEM_H
#define MOCK_ITEM_H

#include "Item.h"
#include <string>

using namespace std;
using namespace play_core;
/*
  A mock of the Item class to test if its destruction
 */
class MockItem : public Item
{
public:
    MockItem(const string& name, bool& isDeleted);

    ~MockItem();

    void accept(ItemVisitor& visitor);
private:
    bool& isDeleted_;
};

#endif // MOCK_ITEM_H
