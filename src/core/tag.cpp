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
            ss << "Cannot register the Item " << item->getName() << " to the Tag " << tagName_ << " : the Item is already registered to the Tag";
            throw logic_error(ss.str());
        }
    }
    registeredItems_.push_back(item);
}

void Tag::unregisterItem(Item *item)
{
    ItemList::iterator it;
    for(it = registeredItems_.begin(); it != registeredItems_.end(); ++it) {
        if((*it)->getName() == item->getName()) {
            registeredItems_.erase(it);
            break;
        }
    }
    if(it == registeredItems_.end()) {
        stringstream ss;
        ss << "Cannot unregister the Item " << item->getName() << " from the Tag " << tagName_ << " : the Item is not registered to the Tag";
        throw logic_error(ss.str());
    }
}
