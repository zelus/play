#include <iostream>
#include "common.h"
#include "itemmanager.h"
#include "tag.h";

using namespace std;

int main()
{
    ItemManager im;
    Item* fold = im.createFolder("fold");
    Item* mov1 = im.createMovie("mov1",fold,"this is a wonderful movie",10);
    Item* fold1 = im.createFolder("fold1",fold);
    Item* mov1bis = im.createMovie("mov1",fold1,"mov1 bis sum",7);
    Item* mov2 = im.createMovie("mov2",fold1,"mov2 sum",3);
    cout << fold->getAllSubItems().size() << endl;
    cout << fold->getParent()->getName() << endl;
    cout << mov1->getParent()->getName() << endl;
    cout << mov1bis->getParent()->getName() << endl;
    cout << mov2->getParent()->getName() << endl;
    ItemList il = im.findItem("mov1");
    cout << "findItem test" << endl;
    for(size_t i = 0; i < il.size(); ++i) {
        cout << il[i]->getParent()->getName() << endl;
    }
    MovieList il1 = im.itemListToMovieList(im.findItem("mov1"));
    cout << "itemListToMovieList & findItem test" << endl;
    for(size_t i = 0; i < il1.size(); ++i) {
        cout << il1[i]->getParent()->getName() << endl;
    }
    MovieList il2 = im.findMovie("mov1");
    cout << "findMovie test" << endl;
    for(size_t i = 0; i < il2.size(); ++i) {
        cout << il2[i]->getParent()->getName() << endl;
    }
    //cout << im.itemToMovie(im.findItem("mov1",MOVIE_TYPE)[0])->getSummary() << endl;
    cout << "Tag tests" << endl;
    Tag* tag1 = new Tag("tag1");
    mov1->addTag(tag1);
    cout << tag1->getAllRegisteredItems()[0]->getName() << endl;
    cout << mov1->getAllTags()[0]->getTagName() << endl;
    return 0;
}

