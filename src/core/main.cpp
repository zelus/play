#include <iostream>
#include "item.h"
#include "folder.h"

using namespace std;

int main()
{
    Item* item1 = new Item("test1");
    Folder* folder = new Folder("fold1");
    Item* item2 = new Item("test2",folder);
    folder->addSubItem(item1);
    cout << folder->getName() << endl;
    for(size_t i = 0; i < folder->getAllItems().size(); i++) {
        cout << "\t-" << folder->getAllItems()[i]->getName() << endl;
    }
    cout << "folder size : " << folder->getAllItems().size() << endl;
    cout << folder->getItem("test1")->getName() << endl;
    delete item1;
    cout << "folder size : " << folder->getAllItems().size() << endl;
    return 0;
}

