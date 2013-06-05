#ifndef TAG_H
#define TAG_H

#include "common.h"
#include <string>

using namespace std;

class Tag
{
public:
    Tag(const string tagName = "");
    Tag(const Tag& tag);
    ~Tag();

    const string& getTagName() const;

    void registerItem(Item* item);
    void unregisterItem(Item* item);

private:
    string tagName_;
    ItemList registeredItems_;
};

#endif // TAG_H
