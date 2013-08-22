/*!
  \file folder.h
  \author Gwendal Daniel
  \date 2013-04-28
 */

#ifndef FOLDER_H
#define FOLDER_H

#include "Item.h"
#include <vector>
#include <string>

/*!
  \brief Represents a concrete Item with folder properties.

  The Folder class is a part of the \em composite pattern used to store
  the Item tree. It is derivated from the Item class and represents an Item
  with children management methods.
  It overrides children management default methods defined in Item class.
 */
class Folder : public Item
{
public:
    Folder(const std::string& id, const std::string& folderName, Item* parent = nullptr);
    Folder(const Folder& folder) = delete;
    ~Folder();

    void addSubItem(Item* item);
    void removeSubItem(Item *item);
    void deleteSubItem(Item *item);
    Item* getSubItem(const std::string& itemName) const;
    bool containsSubItem(const std::string& id) const;
    const std::vector<Item*>& getAllSubItems() const;

private:
    std::vector<Item*> items_;

};

#endif // FOLDER_H
