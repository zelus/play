#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <vector>
#include <string>

class ItemSearcher;
class Item;
/*!
  \brief High level interface providing a tree context for Item objects.

  This class is used to store and navigate through an Item hierarchy
  (see Item and derivated classes for further informations).

  Provides convenience methods such as top level Item management,
  total Item counting and unified search interface.

  This class is strongly coupled with Item class : it is called during Item
  construction to calculate a unique ID and to set Item's default parent. Search
  interface and top level Item management are also coupled with Item.
 */
class ItemTree
{
public:
    ItemTree();

    ~ItemTree();

    const std::vector<Item*>  searchItem(ItemSearcher& searcher,
                                         Item* start = nullptr)         const;
    Item*                     searchSingleItem(ItemSearcher& searcher,
                                               Item* start = nullptr)   const;

    Item*                     getRootItem()                             const;
    Item*                     getDefaultItemParent()                    const;
    unsigned int              getTopLevelItemNumber()                   const;

    void                      registerItem(Item* item);
    void                      deleteItem(Item* item);

private:

    Item* treeRoot_;
    unsigned int nextId_;
};

#endif // ITEMMANAGER_H
