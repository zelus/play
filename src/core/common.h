#ifndef COMMON_H
#define COMMON_H

#include <vector>

class Item;
class Folder;
class Movie;
class Tag;

enum ItemType {
    ANY_TYPE,
    FOLDER_TYPE,
    MOVIE_TYPE
};

typedef std::vector<Item*> ItemList;
typedef std::vector<Folder*> FolderList;
typedef std::vector<Movie*> MovieList;
typedef std::vector<Tag*> TagList;

#endif // COMMON_H
