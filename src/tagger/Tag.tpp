#include <stdexcept>
#include <sstream>
// debug
#include <iostream>

/*!
  \brief Constructs a Tag from the given parameters.
  \param tagName the name of the Tag.
 */
template<typename T>
Tag<T>::Tag(const std::string tagName)
{
    tagName_ = tagName;
}

/*!
  \brief Constructs a Tag from the given Tag.
  \param tag the Tag to construct from.
  \warning The registered Item list is not copied into the
  constructed Tag. This would break global consistency between
  Item and Tag crossed-references.
 */
template<typename T>
Tag<T>::Tag(const Tag &tag)
{
    tagName_ = tag.tagName_;
}

/*!
  \brief Deletes the Tag and all its references in registeredItems.
 */
template<typename T>
Tag<T>::~Tag()
{
    for(size_t i = 0; i < registeredItems_.size(); i++) {
        try {
            registeredItems_[i]->removeTag(this);
        }catch(std::exception& e) {

        }
    }
}

/*!
  \return the name of the Tag.
 */
template<typename T>
const std::string& Tag<T>::getName() const
{
    return tagName_;
}

/*!
  \brief Add an Item to the list of registered Items.
  \param item the Item to register.
  \exception std::logic_error if the Item is already registered to the Tag.
  \warning This method doesn't ensure consistency between Item and Tag objects :
  the Tag list of the Item is not updated. See Item::addTag for consistent Tag
  addition.
 */
template<typename T>
void Tag<T>::registerItem(T item)
{
    for(size_t i = 0; i < registeredItems_.size(); i++) {
        if(registeredItems_[i]->getName() == item->getName()) {
            std::stringstream ss;
            ss << "Cannot register the Item " << item->getName() << " to the Tag " << tagName_ << " : the Item is already registered to the Tag";
            throw std::logic_error(ss.str());
        }
    }
    registeredItems_.push_back(item);
}

/*!
  \brief Remove an Item to the list of registered Items.
  \param item the Item to remove.
  \exception std::logic_error if the Item is not registered to the Tag.
  \warning This method doesn't ensure consistency between Item and Tag objects :
  the Tag list of the Item is not updated. See Item::removeTag for consistent Tag
  removal.
 */
template<typename T>
void Tag<T>::unregisterItem(T item)
{
    typename RegisteredItems::iterator it;
    bool updated = false;
    for(it = registeredItems_.begin(); it != registeredItems_.end(); ++it) {
        if((*it)->getName() == item->getName()) {
            registeredItems_.erase(it);
            updated = true;
            break;
        }
    }
    if(!updated) {
        std::stringstream ss;
        ss << "Cannot unregister the Item " << item->getName() << " from the Tag " << tagName_ << " : the Item is not registered to the Tag";
        throw std::logic_error(ss.str());
    }
}

/*!
  \return the list of registered Items.
 */
template<typename T>
typename Tag<T>::RegisteredItems Tag<T>::getAllRegisteredItems() const
{
    return registeredItems_;
}
