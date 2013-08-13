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
    // tag item from string ? sans support de la liste de tag dans l'item

    Tag<T>* getTag(const std::string& tagName) const;

    std::vector<Tag<T>*> getTags() const;
    size_t getTagsNumber() const;
    bool containsTag(const std::string& tagName) const;

protected:
    std::vector<Tag<T>*> tags_;

private:
    Tag<T>* createSingletonTag(const std::string& tagName);
};

#include "TagManager.tpp"
#endif // TAGMANAGER_H
