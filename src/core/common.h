#ifndef COMMON_H
#define COMMON_H

#include <vector>

class Item;

enum ItemType {
    ANY_TYPE,
    FOLDER_TYPE,
    MOVIE_TYPE
};

typedef std::vector<Item*> ItemList;

#endif // COMMON_H
