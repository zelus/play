#include <sstream>
#include "TaggerException.h"
// Debug
#include <iostream>

/*!
  \brief Constructs a new TagManager.
 */
template<typename T>
TagManager<T>::TagManager()
{

}

/*!
  \brief Deletes the TagManager and each Tag managed by it.
 */
template<typename T>
TagManager<T>::~TagManager()
{
    typename std::vector<Tag<T>*>::iterator it;
    for(it = tags_.begin(); it != tags_.end(); ++it) {
        delete (*it);
    }
}

template<typename T>
std::vector<Tag<T>*> TagManager<T>::tagFromString(const std::string& toTag)
{
    std::vector<Tag<T>*> tags;
    std::stringstream ss(toTag);
    std::string tmp;
    while(std::getline(ss,tmp,' ')) {
        std::cout << tmp << std::endl;
        tags.push_back(createSingletonTag(tmp));
    }
    return tags;
}

template<typename T>
std::vector<Tag<T>*> TagManager<T>::createTagsFromItem(const std::string& toTag, T item, unsigned int priority)
{
    const std::vector<Tag<T>*>& tags = tagFromString(toTag);
    typename std::vector<Tag<T>*>::const_iterator it;
    for(it = tags.begin(); it != tags.end(); ++it) {
        try {
            (*it)->registerItem(item,priority);
        }catch(TaggerException& e) {
            /* Don't handle TaggerException, it would cause more damage than
               solve anything : if the registration process is interrupted the
               Item would be part tagged. Moreover, the TaggerException corresponds
               to a double registration in a Tag, which may be resulting of a consistency
               error, but the result is still valid.
             */
        }
    }
    return tags;
}

template<typename T>
void TagManager<T>::deleteTagsFromItem(const std::string& toTag, T item, unsigned int priority)
{
    const std::vector<Tag<T>*>& tags = tagFromString(toTag);
    try {
        deleteTagsFromItem(tags,item,priority);
    }catch(TaggerException& e) {
        /* Don't handle TaggerException, it would cause more damage than
           solve anything : if the unregistration process is interrupted the
           Item would be part tagged. Moreover, the TaggerException corresponds
           to an invalid unregistration in a Tag, which may be resulting of a consistency
           error, but the result is still valid.
         */
    }
}

template<typename T>
void TagManager<T>::deleteTagsFromItem(const std::vector<Tag<T>*>& tags, T item, unsigned int priority)
{
    typename std::vector<Tag<T>*>::const_iterator it;
    for(it = tags.begin(); it != tags.end(); ++it) {
        try {
            (*it)->unregisterItem(item,priority);
            if((*it)->getRegisteredItemsNumber() == 0) {
                removeTag(*it);
                delete *it;
            }
        }catch(TaggerException& e) {
            /* Don't handle TaggerException, it would cause more damage than
               solve anything : if the unregistration process is interrupted the
               Item would be part tagged. Moreover, the TaggerException corresponds
               to an invalid unregistration in a Tag, which may be resulting of a consistency
               error, but the result is still valid.
             */
        }
    }
}

/*!
  \brief Return the tag corresponding to the given name.
  \param tagName the name of the wanted Tag.
  \return the Tag with the given name.
  \exception TaggerException if the TagManager doesn't contain the Tag.
 */
template<typename T>
Tag<T>* TagManager<T>::getTag(const std::string &tagName) const
{
    typename std::vector<Tag<T>*>::const_iterator it;
    for(it = tags_.begin(); it != tags_.end(); ++it) {
        if((*it)->getName() == tagName) {
            return *it;
        }
    }
    std::stringstream ss;
    ss << "The Tag " << tagName << " doesn't exists in the TagManager";
    throw TaggerException(ss.str(),__FILE__,__LINE__);
}

/*!
  \return the list of all Tags managed by the TagManager.
 */
template<typename T>
std::vector<Tag<T>*> TagManager<T>::getTags() const
{
    return tags_;
}

template<typename T>
size_t TagManager<T>::getTagsNumber() const
{
    return tags_.size();
}

template<typename T>
bool TagManager<T>::containsTag(const std::string& tagName) const
{
    typename std::vector<Tag<T>*>::const_iterator it;
    for(it = tags_.begin(); it != tags_.end(); ++it) {
        if((*it)->getName() == tagName) {
            return true;
        }
    }
    return false;
}

template<typename T>
Tag<T>* TagManager<T>::createSingletonTag(const std::string& tagName)
{
    Tag<T>* tag = nullptr;
    try {
        tag = getTag(tagName);
    }catch(TaggerException& e) {
        tag = new Tag<T>(tagName);
        tags_.push_back(tag);
        return tag;
    }
    return tag;
}

template<typename T>
void TagManager<T>::removeTag(Tag<T>* tag)
{
    typename std::vector<Tag<T>*>::iterator it;
    for(it = tags_.begin(); it != tags_.end(); ++it) {
        if((*it)->getName() == tag->getName()) {
            tags_.erase(it);
            break;
        }
    }
}
