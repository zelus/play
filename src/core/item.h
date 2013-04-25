#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Folder;

class Item
{

public:
    Item(const string& itemName = "", Folder* parent = nullptr);
    Item(const Item& item);
    ~Item();

    const Item* getParent() const;
    const string& getName() const;

    void setParent(Folder* parent);
    virtual void addSubItem(Item* item);
    virtual void removeSubItem(Item* item);
    virtual Item* getSubItem(const string& itemName) const;

protected:
    string itemName_;
    Folder* parent_;
};

#endif // ITEM_H
