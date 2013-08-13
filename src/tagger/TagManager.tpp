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

/*!
  \brief Return the tag corresponding to the given name.
  \param tagName the name of the wanted Tag.
  \return the Tag with the given name.
  \exception TaggerException if the TagManager doesn't contain the Tag.
 */
template<typename T>
Tag<T>* TagManager<T>::getTag(const std::string &tagName) const
{
    typename std::vector<Tag<T>*>::iterator it;
    for(it = tags_.begin(); it != tags_.end(); ++it) {
        if((*it)->getTagName() == tagName) {
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
