#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>
#include "ItemTree.h"

class ItemVisitor;

/*!
  \brief Represents an abstract Item.

  The Item class is the base class of the \em composite pattern used to store
  the Item tree.

  Abstract Item must be inherited by a concrete subclass implementing
  accept method.

  If the class inherited of Item defines a container it should override
  subItem management methods.

  Item are strongly coupled with their context (i.e. ItemTree) : it ensures
  base consistency of the composite tree by providing IDs and a global tree
  root.
 */
class Item
{

public:
    Item(const std::string& name, ItemTree& itemTree);
    /*!
      \warning Copy constructor is deleted to prevent ID
      duplication
    */
    Item(const Item& item) = delete;
    /*!
      \warning Assignment operator is deleted to prevent ID
      duplication.
     */
    Item& operator=(const Item&) = delete;

    virtual ~Item() = 0;

    Item*                               getParent()                             const;
    const std::string&                  getId()                                 const;
    const std::string&                  getName()                               const;

    void                                setName(const std::string& name);

    virtual void                        addSubItem(Item* item);
    virtual void                        removeSubItem(Item* item);
    virtual void                        deleteSubItem(Item* item);
    virtual Item*                       getSubItem(const std::string& id)       const;
    virtual bool                        containsSubItem(const std::string& id)  const;
    virtual int                         getSubItemIndex(Item* item)             const;
    virtual const std::vector<Item*>&   getAllSubItems()                        const;
    virtual unsigned int                getSubItemNumber()                      const;

    /*!
      \brief Generic accept method for ItemVisitor.

      This method needs to be overriden in each subclass to
      call the dedicated ItemVisitor::visit method.

      \param visitor the ItemVisitor to use through the Item.
     */
    virtual void accept(ItemVisitor& visitor) = 0;

    void setParent(Item* parent);
    void setId(const std::string& id);

protected:
    /*!
      The unique ID associated to the Item.
      This ID is given by the context (ItemTree) provided
      for the Item construction.
     */
    std::string id_;
    /*!
      The name of the Item.
     */
    std::string name_;
    /*!
      The parent of the Item. Default parent (at construction time)
      is provided by the context (ItemTree).
     */
    Item* parent_;
    /*!
      The tree the Item belongs to. This variable is used internally
      to get a unique ID (relative to the tree) during the creation.
      Some call also have impact on the ItemTree pointed (e.g. destructor
      call will forward the deletion to the ItemTree for counting issues).
     */
    ItemTree& itemTree_;

    /*!
      Enforce encapsulation by removing access to
      setParent and setId method to client. Parent management
      is provided by both parent Item and ItemTree. ID management
      is provided by the ItemTree.
     */
//friend void ItemTree::registerItem(Item*);
};

#endif // ITEM_H
