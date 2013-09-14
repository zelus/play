#include <QtGui/QApplication>

#include "ItemManager.h"
#include "Workbench.h"
#include "ItemController.h"
#include "LibraryTreeModel.h"
// debug
#include <iostream>

using namespace std;

int main( int argc, char **argv )
{
    cout << "Launching app ..." << endl;
    QApplication a(argc, argv);
    Workbench w;
    ItemManager item_manager;
    item_manager.createMovie("movie1",nullptr,"this is movie1",2);
    item_manager.createMovie("movie2",nullptr,"this is movie 2", 3);
    Item* folder1 = item_manager.createFolder("folder1");
    item_manager.createMovie("movie3",folder1,"this is movie3", 5);
    item_manager.createMovie("movie4",folder1,"this is movie4", 6);
    cout << "Test Item tree structure created." << endl;
    ItemController item_controller(item_manager);
    LibraryTreeModel library_tree_model(item_controller);
    w.getLibraryTreeView()->setModel(&library_tree_model);
    cout << "Abstract LibraryTreeModel set to LibraryTreeView." << endl;
    w.show();
    cout << "Workbench shown." << endl;

    return a.exec();
}
