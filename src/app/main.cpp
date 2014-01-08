#include <QApplication>

#include "TreeContext.h"
#include "Item.h"
#include "Movie.h"
#include "Folder.h"
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
    play_core::TreeContext tree_context;
    play_core::Item* movie1 = new play_core::Movie("movie1","this is movie1",2);
    play_core::Item* movie2 = new play_core::Movie("movie2","this is movie 2",3);
    play_core::Item* folder1 = new play_core::Folder("folder1");
    play_core::Item* movie3 = new play_core::Movie("movie3","this is movie3",5);
    play_core::Item* movie4 = new play_core::Movie("movie4","this is movie4",6);
    tree_context.registerItem(movie1);
    tree_context.registerItem(movie2);
    tree_context.registerItem(folder1);
    tree_context.registerItem(movie3);
    tree_context.registerItem(movie4);
    tree_context.addTopLevelItem(movie1);
    tree_context.addTopLevelItem(movie2);
    tree_context.addTopLevelItem(folder1);
    tree_context.moveItem(movie3,folder1);
    tree_context.moveItem(movie4,folder1);
    cout << "Test Item tree structure created." << endl;
    ItemController item_controller(tree_context);
    LibraryTreeModel library_tree_model(item_controller);
    w.getLibraryTreeView()->setModel(&library_tree_model);
    cout << "Abstract LibraryTreeModel set to LibraryTreeView." << endl;
    w.show();
    cout << "Workbench shown." << endl;

    return a.exec();
}
