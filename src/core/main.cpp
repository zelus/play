#include <iostream>
#include "item.h"
#include "folder.h"

using namespace std;

int main()
{
    Item* item1 = new Item("test1");
    Item* item2 = new Item("test2");
    Folder* folder = new Folder("fold1");
    folder->addItem(item1);
    folder->addItem(item2);
    cout << folder->getName() << endl;
    for(int i = 0; i < folder->getAllItems().size(); i++) {
        cout << "\t-" << folder->getAllItems()[i]->getName() << endl;
    }
    delete folder;
    return 0;
}

