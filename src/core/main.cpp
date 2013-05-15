#include <iostream>
#include "itemmanager.h"

using namespace std;

int main()
{
    ItemManager im;
    Item* fold = im.createFolder("fold");
    Item* mov1 = im.createMovie("mov1",fold,"this is a wonderful movie",10);
    // fixme #2
    //fold->addSubItem(mov1);
    cout << fold->getAllSubItems().size() << endl;
    cout << fold->getParent()->getName() << endl;
    cout << mov1->getParent()->getName() << endl;
    cout << im.findMovie("mov1")->getSummary() << endl;
    return 0;
}

