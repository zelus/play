#include "folder.h"

Folder::Folder(const string& folderName) : Item(folderName)
{

}

Folder::Folder(const Folder &folder) : Item(folder.getName())
{

}

Folder::~Folder() {

}
