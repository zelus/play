/*!
  \file item.h
  \author Gwendal Daniel
  \date 2013-04-28
 */

#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include "TagManager.h"
#include "Tag.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

class Folder;

/*!
  \brief Represents an abstract Item.
 */
class Item
{

public:

    static const int name_priority;

    typedef std::map<unsigned int, std::vector<Tag<Item*>*> > Tags;
    Item(const string& id, const string& itemName, ItemType itemType = ANY_TYPE, Item* parent = nullptr, TagManager<Item*>* tagManager = nullptr);
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
    virtual ItemList getAllSubItems() const;

    Tags getAllTags() const;

protected:

    virtual void addTags(const std::string& value, unsigned int priority);
    virtual void deleteTags(const std::string& value, unsigned int priority);
    virtual void updateTags(const std::string& oldValue, const std::string& newValue, unsigned int priority);

    string id_;
    string itemName_;
    Item* parent_;
    ItemType itemType_;
    Tags tagList_;
    TagManager<Item*>* tagManager_;
};

#endif // ITEM_H
