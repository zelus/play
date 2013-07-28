#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include "common.h"
#include <string>

using namespace std;

/*!
  \brief High level interface ensuring Tag unicity. (see
  \em Singleton pattern for further informations.

  Every client code has to use this interface to get existing
  Tags and / or create new Tags.
 */
class TagManager
{
public:
    TagManager();
    TagManager(TagManager& tagManager);
    ~TagManager();

    Tag* getTag(const string& tagName);
    TagList getTagList() const;

private:
    TagList tagList_;
};

#endif // TAGMANAGER_H
