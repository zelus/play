#ifndef FOLDER_H
#define FOLDER_H

#include "Item.h"
#include <vector>
#include <string>

namespace play_core {

/*!
  \brief Represents a concrete Item which can handle children.

  The Folder class is a part of the \em composite pattern used to store
  the Item tree. It is derivated from the Item class and represents an Item
  with children management methods.

  It overrides children management default methods defined in Item class.
 */
class Folder : public Item
{
public:
    Folder(const std::string& name);
    /*!
      \warning Copy constructor is deleted to prevent ID
      duplication
    */
    Folder(const Folder& folder) = delete;
    /*!
      \warning Assignment operator is deleted to prevent ID
      duplication
     */

    ~Folder();

    void                        addChild(Item* item);
    void                        removeChild(Item *item);
    void                        deleteChild(Item *item);
    Item*                       getChild(const std::string& id)       const;
    bool                        containsChild(const std::string& id)  const;
    int                         getChildIndex(Item* item)             const;
    const std::vector<Item*>&   getChildren()                         const;
    unsigned int                childCount()                          const;

    void accept(ItemVisitor& visitor);

private:
    std::vector<Item*> items_;

};

} // namespace
#endif // FOLDER_H
