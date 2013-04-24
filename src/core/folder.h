#ifndef FOLDER_H
#define FOLDER_H

#include "item.h"

class Folder : public Item
{
public:
    Folder(const string& folderName = "");
    Folder(const Folder& folder);
    ~Folder();

};

#endif // FOLDER_H
