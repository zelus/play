#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>

class ItemVisitor;

enum class ItemType { ANY_TYPE, FOLDER_TYPE, MOVIE_TYPE };

/*!
  \brief Represents an abstract Item.
 */
class Item
{

public:
    Item(const std::string& id, const std::string& name, ItemType type = ItemType::ANY_TYPE, Item* parent = nullptr);
    Item(const Item& item) = delete;
    virtual ~Item() = 0;

    Item* getParent() const;
    const std::string& getId() const;
    const std::string& getName() const;
    ItemType getType() const;

    void setParent(Item* newParent);
    void setName(const std::string& name);
    virtual void addSubItem(Item* item);
    virtual void removeSubItem(Item* item);
    virtual void deleteSubItem(Item* item);
    virtual Item* getSubItem(const std::string& itemId) const;
    virtual bool containsSubItem(const std::string& itemId) const;
    virtual const std::vector<Item*>& getAllSubItems() const;

    virtual void accept(ItemVisitor* visitor) = 0;

protected:

    std::string id_;
    std::string name_;
    Item* parent_;
    ItemType type_;
};

#endif // ITEM_H
