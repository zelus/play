#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include <string>

using namespace std;

class Folder;

class Item
{

public:
    Item(const string& itemName = "", Item* parent = nullptr);
    Item(const Item& item);
    ~Item();

    const Item* getParent() const;
    const string& getName() const;

    void setParent(Folder* parent);
    virtual void addSubItem(Item* item);
    virtual void removeSubItem(Item* item);
    virtual Item* getSubItem(const string& itemName) const;
    virtual ItemList getAllSubItems() const;

protected:
    string itemName_;
    Item* parent_;
};

#endif // ITEM_H
