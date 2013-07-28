#include "TagManager.h"
#include "Tag.h"

/*!
  \brief Constructs a new TagManager.
 */
TagManager::TagManager()
{

}

/*!
  \brief Constructs a TagManager from the given TagManager.
  \param tagManager the TagManager to construct from.
 */
TagManager::TagManager(TagManager &tagManager)
{
    tagList_ = tagManager.tagList_;
}

/*!
  \brief Deletes the TagManager and each Tag managed by it.

  \warning In case of Tag sharing between TagManagers, this deletion invalidates
  the other TagManagers referencing the Tags.
 */
TagManager::~TagManager()
{
    TagList::iterator it;
    for(it = tagList_.begin(); it != tagList_.end(); ++it) {
        delete (*it);
    }
}

/*!
  \brief Return the tag corresponding to the given name.

  This method ensure Tag unicity relatively to the TagManager : if a Tag
  with the given name exists it is returned, otherwise a new Tag is created
  with it.
  \param tagName the name of the wanted Tag.
  \return the Tag with the given name.
 */
Tag* TagManager::getTag(const string &tagName)
{
    TagList::iterator it;
    for(it = tagList_.begin(); it != tagList_.end(); ++it) {
        if((*it)->getTagName() == tagName) {
            return *it;
        }
    }
    // The Tag doesn't exist and has to be created
    Tag* newTag = new Tag(tagName);
    tagList_.push_back(newTag);
    return newTag;
}

/*!
  \return the list of all Tags managed by the TagManager.
 */
TagList TagManager::getTagList() const
{
    return tagList_;
}
