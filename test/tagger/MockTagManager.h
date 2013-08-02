#ifndef MOCKTAGMANAGER_H
#define MOCKTAGMANAGER_H

#include "TagManager.h"
#include "Tag.h"
#include "Item.h"

/*
  A mock of the TagManager class to test the TagManager destructor.
  This test also need MockTak class to test if the Tags contained
  in the TagManager are well deleted.
  This mock doesn't modify the base TagManager destructor, it
  just provides a addTag method to register the MockTag objects
  (which is not available in the base TagManager class).
*/
class MockTagManager : public TagManager<Item*>
{
public:
    MockTagManager();
    void addTag(Tag<Item*>* tag);
};

#endif // MOCKTAGMANAGER_H
