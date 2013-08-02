#include "MockTagManager.h"

/*
  MockTagManager constructor.
*/
MockTagManager::MockTagManager() : TagManager()
{

}

/*
  Add a Tag to the TagManager list.
*/
void MockTagManager::addTag(Tag<Item*>* tag)
{
    tags_.push_back(tag);
}
