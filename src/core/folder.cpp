#include "folder.h"

Folder::Folder(const string& folderName) : Item(folderName)
{

}

Folder::Folder(const Folder &folder) : Item(folder.getItemName())
{

}

Folder::~Folder() {

}
