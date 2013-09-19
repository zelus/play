#ifndef FOLDER_H
#define FOLDER_H

#include "Item.h"
#include <vector>
#include <string>

/*!
  \brief Represents a concrete Item which can handle children (sub Items).

  The Folder class is a part of the \em composite pattern used to store
  the Item tree. It is derivated from the Item class and represents an Item
  with children management methods.

  It overrides children management default methods defined in Item class.
 */
class Folder : public Item
{
public:
    Folder(const std::string& name, ItemTree& itemTree);
    /*!
      \warning Copy constructor is deleted to prevent ID
      duplication
    */
    Folder(const Folder& folder) = delete;
    ~Folder();

    void                        addSubItem(Item* item);
    void                        removeSubItem(Item *item);
    void                        deleteSubItem(Item *item);
    Item*                       getSubItem(const std::string& id)       const;
    bool                        containsSubItem(const std::string& id)  const;
    int                         getSubItemIndex(Item* item)             const;
    const std::vector<Item*>&   getAllSubItems()                        const;
    unsigned int                getSubItemNumber()                      const;

    void accept(ItemVisitor& visitor);

private:
    std::vector<Item*> items_;

};

#endif // FOLDER_H
