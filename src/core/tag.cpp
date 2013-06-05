#include "tag.h"
#include "item.h"

#include <stdexcept>
#include <sstream>

Tag::Tag(const string tagName)
{
    tagName_ = tagName;
}

Tag::Tag(const Tag &tag)
{
    tagName_ = tag.tagName_;
}

Tag::~Tag()
{
    for(size_t i = 0; i < registeredItems_.size(); i++) {
        try {
            registeredItems_[i]->removeTag(this);
        }catch(logic_error& e) {

        }
    }
}

const string& Tag::getTagName() const
{
    return tagName_;
}

void Tag::registerItem(Item *item)
{
    for(size_t i = 0; i < registeredItems_.size(); i++) {
        if(registeredItems_[i]->getName() == item->getName()) {
            stringstream ss;
            ss << "The Item " << item->getName() << " is already tagged by the Tag " << tagName_;
            throw logic_error(ss.str());
        }
    }
    registeredItems_.push_back(item);
}
