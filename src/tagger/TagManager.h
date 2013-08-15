#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <string>
#include <vector>

#include "Tag.h"

/*!
  \brief High level interface ensuring Tag unicity. (see
  \em Singleton pattern for further informations.

  Every client code has to use this interface to get existing
  Tags and / or create new Tags.
 */
template<typename T>
class TagManager
{
public:
    TagManager();
    TagManager(TagManager& tagManager) = delete;
    TagManager<T>& operator=(const TagManager<T>&) = delete;
    virtual ~TagManager();

    std::vector<Tag<T>*> tagFromString(const std::string& toTag);

    std::vector<Tag<T>*> createTagsFromItem(const std::string& toTag, T item ,unsigned int priority);
    void deleteTagsFromItem(const std::string& toTag, T item, unsigned int priority);
    void deleteTagsFromItem(const std::vector<Tag<T>*>& tags, T item, unsigned int priority);

    Tag<T>* getTag(const std::string& tagName) const;

    std::vector<Tag<T>*> getTags() const;
    size_t getTagsNumber() const;
    bool containsTag(const std::string& tagName) const;

protected:
    std::vector<Tag<T>*> tags_;

private:
    Tag<T>* createSingletonTag(const std::string& tagName);
    void removeTag(Tag<T>* tag);
};

#include "TagManager.tpp"
#endif // TAGMANAGER_H
