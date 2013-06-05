#ifndef TAG_H
#define TAG_H

#include "common.h"
#include <string>

using namespace std;

/*!
  \brief Represents a simple Tag (key-word)

  This class is managed by the TagManager class : it shouldn't
  be manipulated directly (it may break the global consistency of
  the application).
 */
class Tag
{
public:
    Tag(const string tagName = "");
    Tag(const Tag& tag);
    ~Tag();

    const string& getTagName() const;

    void registerItem(Item* item);
    void unregisterItem(Item* item);

    ItemList getAllRegisteredItems() const;

private:
    string tagName_;
    ItemList registeredItems_;
};

#endif // TAG_H
