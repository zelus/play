#include <iostream>
#include "item.h"
#include "folder.h"

using namespace std;

int main()
{
    Item* item1 = new Item("test1");
    Folder* folder = new Folder("fold1");
    //Item* item2 = new Item("test2",item1);
    folder->addSubItem(item1);
    cout << folder->getName() << endl;
    for(size_t i = 0; i < folder->getAllSubItems().size(); i++) {
        cout << "\t-" << folder->getAllSubItems()[i]->getName() << endl;
    }
    cout << "folder size : " << folder->getAllSubItems().size() << endl;
    cout << folder->getSubItem("test1")->getName() << endl;

    Folder* folder2 = new Folder("fold2");
    folder2->addSubItem(item1);

    folder2->deleteSubItem(item1);

    cout << "folder1 size : " << folder->getAllSubItems().size() << endl;
    cout << "folder2 size : " << folder2 ->getAllSubItems().size() << endl;
    return 0;
}

