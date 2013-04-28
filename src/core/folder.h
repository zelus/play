#ifndef FOLDER_H
#define FOLDER_H

#include "item.h"
#include <string>
#include <vector>

using namespace std;

typedef vector<Item*> itemList;

class Folder : public Item
{
public:
    Folder(const string& folderName = "", Item* parent = nullptr);
    Folder(const Folder& folder);
    ~Folder();

    itemList getAllItems() const;

    void addSubItem(Item* item);
    void removeSubItem(Item *item);
    Item* getSubItem(const string& itemName) const;

private:
    itemList items_;

};

#endif // FOLDER_H
