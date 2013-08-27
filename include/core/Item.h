#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>

class ItemVisitor;

enum class ItemType { ANY_TYPE, FOLDER_TYPE, MOVIE_TYPE };

/*!
  \brief Represents an abstract Item.

  The Item class is the base class of the \em composite pattern used to store
  the Item tree.

  Abstract Item must be inherited by a concrete subclass implementing
  accept method.

  If the class inherited of Item defines a container it should override
  subItem management methods.
 */
class Item
{

public:
    Item(const std::string& id, const std::string& name, ItemType type = ItemType::ANY_TYPE, Item* parent = nullptr);
    /*!
      \warning Copy constructor is deleted to prevent ID
      duplication
    */
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
    virtual Item* getSubItem(const std::string& id) const;
    virtual bool containsSubItem(const std::string& id) const;
    virtual const std::vector<Item*>& getAllSubItems() const;

    /*!
      \brief Generic accept method for ItemVisitor.

      This method needs to be overriden in each subclass to
      call the dedicated ItemVisitor::visit method.

      \param visitor the ItemVisitor use through the Item.
     */
    virtual void accept(ItemVisitor* visitor) = 0;

protected:
    /*!
      The unique ID associated to the Item.
      See ItemManager creation methods to create Item with
      consistent and valid ID.
     */
    std::string id_;
    /*!
      The name of the Item.
     */
    std::string name_;
    /*!
      The parent of the Item.
     */
    Item* parent_;
    /*!
      The type of the Item. This is a convenience member
      variable to avoid type cast in polymorphic Item
      management (for example dispatch Item between different
      manager and delegate the specific processing part).
     */
    ItemType type_;
};

#endif // ITEM_H
