#include <iostream>
#include "itemmanager.h"

using namespace std;

int main()
{
    ItemManager im;
    cout << "test" << endl;

    /*cout << "test2" << endl;
    cout << mov1->getParent()->getName() << endl;
    cout << "root size = " << mov1->getParent()->getAllSubItems().size() << endl;*/
    Item* fold = im.createFolder("fold");
    Item* mov1 = im.createMovie("mov1","this is a wonderful movie",10,fold);
    /*cout << "test3" << endl;
    cout << fold->getParent()->getName() << endl;
    cout << mov1->getParent()->getName() << endl;
    cout << "root size = " << mov1->getParent()->getAllSubItems().size() << endl;*/
    fold->addSubItem(mov1);
    cout << "test4" << endl;
    cout << fold->getAllSubItems().size() << endl;
    cout << fold->getParent()->getName() << endl;
    cout << mov1->getParent()->getName() << endl;
    //im.findMovie("mov1");
    cout << im.findMovie("mov1")->getSummary() << endl;
    return 0;
}

