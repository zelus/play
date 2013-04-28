#ifndef FOLDER_H
#define FOLDER_H

#include "item.h"
#include "common.h"
#include <string>

using namespace std;

class Folder : public Item
{
public:
    Folder(const string& folderName = "", Item* parent = nullptr);
    Folder(const Folder& folder);
    ~Folder();

    void addSubItem(Item* item);
    void removeSubItem(Item *item);
    Item* getSubItem(const string& itemName) const;
    ItemList getAllSubItems() const;

private:
    ItemList items_;

};

#endif // FOLDER_H
