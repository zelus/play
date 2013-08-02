#ifndef MOCKTAG_H
#define MOCKTAG_H

#include <string>

#include "Tag.h"
#include "Item.h"

/*
  A mock of the Tag class to test the TagManager destructor.
  This test also needs MockTagManager class to add the mocked
  Tags to the TagManager (no public method in TagManager)
*/
class MockTag : public Tag<Item*>
{
public:
    MockTag(std::string tagName, bool& isDeleted);
    ~MockTag();
private:
    bool& isDeleted_;
};

#endif // MOCKTAG_H
