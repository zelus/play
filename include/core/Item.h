#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>

namespace play_core {

class ItemVisitor;

/*!
  \brief Represents an abstract Item.

  The Item class is the base class of the \em composite pattern used to store
  the Item tree.

  Abstract Item must be inherited by a concrete subclass implementing
  accept method.

  If the class inherited of Item defines a container it should override
  child management methods.
 */
class Item
{

public:
    Item(const std::string& name);
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

    virtual void                        addChild(Item* item);
    virtual void                        removeChild(Item* item);
    virtual void                        deleteChild(Item* item);
    virtual Item*                       getChild(const std::string& id)         const;
    virtual bool                        containsChild(const std::string& id)    const;
    virtual int                         getChildIndex(Item* item)               const;
    virtual const std::vector<Item*>&   getChildren()                           const;
    virtual unsigned int                childCount()                            const;

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
};

} // namespace

#endif // ITEM_H
