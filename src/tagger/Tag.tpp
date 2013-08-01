#include <sstream>
// debug
#include <iostream>

#include "TaggerException.h"

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
  \brief Deletes the Tag.
  \note No reference checking is done during the deletion,
  if the tagged item maintain a Tag list this destructor has to be
  wrapped into an other function wich ensure Tag list consistency.
 */
template<typename T>
Tag<T>::~Tag()
{

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
  \exception TaggerException if the Item is already registered to the Tag.
  \warning This method doesn't ensure consistency between Item and Tag objects :
  the Tag list of the Item is not updated. See Item::addTag for consistent Tag
  addition.
 */
template<typename T>
void Tag<T>::registerItem(T item, int priority)
{
    if(item == nullptr) {
        throw TaggerException("The Item to register is null",__FILE__,__LINE__);
    }
    std::vector<T>& priority_items = registeredItems_[priority];
    for(size_t i = 0; i < priority_items.size(); i++) {
        if(priority_items[i]->getId() == item->getId()) {
            std::stringstream ss;
            ss << "Cannot register the Item " << item->getId() << " to the Tag " << tagName_ << " : the Item is already registered to the Tag";
            throw TaggerException(ss.str(),__FILE__, __LINE__);
        }
    }
    priority_items.push_back(item);
}

/*!
  \brief Remove an Item to the list of registered Items.
  \param item the Item to remove.
  \exception TaggerException if the Item is not registered to the Tag.
  \warning This method doesn't ensure consistency between Item and Tag objects :
  the Tag list of the Item is not updated. See Item::removeTag for consistent Tag
  removal.
 */
template<typename T>
void Tag<T>::unregisterItem(T item, int priority)
{
    if(item == nullptr) {
        throw TaggerException("The Item to unregister is null",__FILE__,__LINE__);
    }
    bool updated = false;
    if(priority == -1) {
        updated = removeAllItemInstances(item);
    }
    else {
        updated = removeItemInstanceWithPriority(item,priority);
    }
    if(!updated) {
        std::stringstream ss;
        ss << "Cannot unregister the Item " << item->getId() << " from the Tag " << tagName_ << " : the Item is not registered to the Tag";
        throw TaggerException(ss.str(), __FILE__, __LINE__);
    }
}

template<typename T>
typename std::vector<T> Tag<T>::getRegisteredItemsWithPriority(int priority) const
{
    return registeredItems_[priority];
}

/*!
  \return the list of registered Items.
 */
template<typename T>
typename Tag<T>::RegisteredItems Tag<T>::getRegisteredItems() const
{
    return registeredItems_;
}

/*!
  \return the number of registered Item for the Tag.
  \note The number returned is different to the size() method on getRegisteredItems() result
  because of the data structure.
*/
template<typename T>
size_t Tag<T>::getRegisteredItemsNumber() const
{
    size_t number_of_items = 0;
    typename RegisteredItems::const_iterator it;
    for(it = registeredItems_.begin(); it != registeredItems_.end(); ++it) {
        number_of_items += it->second.size();
    }
    return number_of_items;
}

/*!
  \brief Removes all the instances of a given Item from the registered Item map.
  \param item the Item to remove.
  \return true if at least one instance has been removed, false otherwise.
*/
template<typename T>
bool Tag<T>::removeAllItemInstances(T item)
{
    bool updated = false;
    typename RegisteredItems::iterator it;
    for(it = registeredItems_.begin(); it != registeredItems_.end(); ++it) {
        updated |= removeItemInstanceWithPriority(item, it->first);
    }
    return updated;
}

/*!
  \brief Removes the Item instance with the given priority.
  \param item the Item to remove.
  \param priority the priority of the Item to remove.
  \return true if the instance has been removed, false otherwise.
*/
template<typename T>
bool Tag<T>::removeItemInstanceWithPriority(T item, unsigned int priority)
{
    std::vector<T>& priority_items = registeredItems_[priority];
    typename std::vector<T>::iterator it;
    for(it = priority_items.begin(); it != priority_items.end(); ++it) {
        if((*it)->getId() == item->getId()) {
            priority_items.erase(it);
            return true;
        }
    }
    return false;
}
