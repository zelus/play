#ifndef FOLDER_H
#define FOLDER_H

#include "item.h"
#include <vector>

using namespace std;

typedef vector<Item*> itemList;

class Folder : public Item
{
public:
    Folder(const string& folderName = "", Folder* parent = nullptr);
    Folder(const Folder& folder);
    ~Folder();

    itemList getAllItems() const;
    Item* getItem(const string& itemName) const;

    void addSubItem(Item* item);
    void removeSubItem(Item *item);

private:
    itemList items_;

};

#endif // FOLDER_H
