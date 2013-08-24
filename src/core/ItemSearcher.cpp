#include "ItemSearcher.h"
#include <vector>
// debug
#include <iostream>

using namespace std;

ItemSearcher::ItemSearcher() : ItemVisitor()
{
}

// basic, parcours de l'arbre en entier.
// Faire un retour dans la méthode sortITem qui permet de stoper la récursion
// (permet comme ça de rechercher le premier Item et ne pas continuer à explorer
// l'arbre inutilement (par exemple dans le cas d'une recherche par ID)
void ItemSearcher::visitFolder(Folder* folder)
{
    cout << "visit folder" << endl;
    bool continue_recursivity = sortItem(rankFolder(folder),folder);
    if(!continue_recursivity) {
        return;
    }
    const vector<Item*>& folder_children = folder->getAllSubItems();
    vector<Item*>::const_iterator it;
    for(it = folder_children.begin(); it != folder_children.end(); ++it) {
        (*it)->accept(this);
    }
}

void ItemSearcher::visitMovie(Movie* movie)
{
    cout << "visit movie" << endl;
    sortItem(rankMovie(movie),movie);
}

const vector<Item*> ItemSearcher::getFoundItems() const
{
    return vector<Item*>();
}

int ItemSearcher::rankFolder(Folder* folder) const
{
    return -1;
}

int ItemSearcher::rankMovie(Movie* movie) const
{
    return -1;
}

bool ItemSearcher::sortItem(const int rank, Item* item)
{
    return false;
}
