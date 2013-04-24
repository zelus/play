#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item
{

public:
    Item(const string& itemName = "");
    Item(const Item& item);
    ~Item();

    const string& getName() const;

private:
    string itemName_;
};

#endif // ITEM_H
