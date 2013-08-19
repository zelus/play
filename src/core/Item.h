/*!
  \file item.h
  \author Gwendal Daniel
  \date 2013-04-28
 */

#ifndef ITEM_H
#define ITEM_H

#include <map>
#include <vector>
#include <string>

using namespace std;

/*!
  \brief Represents an abstract Item.
 */
class Item
{

public:

    enum class ItemType { ANY_TYPE, FOLDER_TYPE, MOVIE_TYPE };

    Item(const string& id, const string& itemName, ItemType itemType = ItemType::ANY_TYPE, Item* parent = nullptr);
    Item(const Item& item) = delete;
    virtual ~Item();

    Item* getParent() const;
    const string& getId() const;
    const string& getName() const;
    ItemType getType() const;

    void setParent(Item* parent);
    void setName(const std::string& name);
    virtual void addSubItem(Item* item);
    virtual void removeSubItem(Item* item);
    virtual void deleteSubItem(Item* item);
    virtual Item* getSubItem(const string& itemName) const;
    virtual bool containsSubItem(const string& itemName) const;
    virtual const vector<Item*>& getAllSubItems() const;

protected:

    string id_;
    string itemName_;
    Item* parent_;
    ItemType itemType_;
};

#endif // ITEM_H
