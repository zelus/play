using namespace std;

/*!
  \brief Constructs a new TagManager.
 */
template<typename T>
TagManager<T>::TagManager()
{

}

/*!
  \brief Constructs a TagManager from the given TagManager.
  \param tagManager the TagManager to construct from.
 */
template<typename T>
TagManager<T>::TagManager(TagManager &tagManager)
{
    tags_ = tagManager.tags_;
}

/*!
  \brief Deletes the TagManager and each Tag managed by it.

  \warning In case of Tag sharing between TagManagers, this deletion invalidates
  the other TagManagers referencing the Tags.
 */
template<typename T>
TagManager<T>::~TagManager()
{
    typename vector<Tag<T>*>::iterator it;
    for(it = tags_.begin(); it != tags_.end(); ++it) {
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
template<typename T>
Tag<T>* TagManager<T>::getTag(const string &tagName)
{
    typename vector<Tag<T>*>::iterator it;
    for(it = tags_.begin(); it != tags_.end(); ++it) {
        if((*it)->getTagName() == tagName) {
            return *it;
        }
    }
    // The Tag doesn't exist and has to be created
    Tag<T>* newTag = new Tag<T>(tagName);
    tags_.push_back(newTag);
    return newTag;
}

/*!
  \return the list of all Tags managed by the TagManager.
 */
template<typename T>
vector<Tag<T>*> TagManager<T>::getTags() const
{
    return tags_;
}
