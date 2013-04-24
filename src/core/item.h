#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item
{

public:
    Item(const string& itemName = "", Item* parent = nullptr);
    Item(const Item& item);
    ~Item();

    const Item* getParent() const;
    const string& getName() const;

    void setParent(Item* parent);
    virtual void removeSubItem(Item* item);

private:
    string itemName_;
    Item* parent_;
};

#endif // ITEM_H
