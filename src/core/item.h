/*!
  \file item.h
  \author Gwendal Daniel
  \date 2013-04-28
 */

#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include <string>

using namespace std;

class Folder;

/*!
  \brief Represents an abstract Item.
 */
class Item
{

public:
    Item(const string& itemName = "", ItemType itemType = ANY_TYPE, Item* parent = nullptr);
    Item(const Item& item) = delete;
    virtual ~Item();

    Item* getParent() const;
    const string& getName() const;
    ItemType getType() const;

    void setParent(Item* parent);
    virtual void addSubItem(Item* item);
    virtual void removeSubItem(Item* item);
    virtual void deleteSubItem(Item* item);
    virtual Item* getSubItem(const string& itemName) const;
    virtual bool containsSubItem(const string& itemName) const;
    virtual ItemList getAllSubItems() const;

    void addTag(Tag* tag);
    void removeTag(Tag* tag);
    TagList getAllTags() const;

protected:
    string itemName_;
    Item* parent_;
    ItemType itemType_;
    TagList tagList_;
};

#endif // ITEM_H
