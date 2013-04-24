#ifndef FOLDER_H
#define FOLDER_H

#include "item.h"
#include <vector>

using namespace std;

typedef vector<const Item*> itemList;

class Folder : public Item
{
public:
    Folder(const string& folderName = "");
    Folder(const Folder& folder);
    ~Folder();

    itemList getAllItems() const;

    void addItem(const Item* item);

private:
    itemList items_;

};

#endif // FOLDER_H
