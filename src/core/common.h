#ifndef COMMON_H
#define COMMON_H

#include <vector>

class Item;

enum ItemType {
    ANY_TYPE,
    MOVIE
};

typedef std::vector<Item*> ItemList;

#endif // COMMON_H
