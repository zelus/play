#include <sstream>
// debug
#include <iostream>

#include "TaggerException.h"

/*!
  \brief Constructs a Tag from the given parameters.
  \param tagName the name of the Tag.
  \exception TaggerException if the given tagName is empty.
 */
template<typename T>
Tag<T>::Tag(const std::string tagName)
{
    if(tagName.empty()) {
        throw TaggerException("Cannot create a Tag with an empty name", __FILE__, __LINE__);
    }
    tagName_ = tagName;
}

/*!
  \brief Deletes the Tag.
  \warning No reference checking is done during the deletion,
  if the tagged Item maintains a Tag list this destructor has to be
  wrapped into an other function wich ensure Item's Tag list consistency.
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
  \exception TaggerException if the Item is already registered to the Tag or if the given Item is null.
  \warning This method doesn't ensure consistency between Item and Tag objects :
  if the Item maintains a Tag list this method has to be wrapped into an other
  function wich ensure Item's Tag list consistency.
 */
template<typename T>
void Tag<T>::registerItem(T item, unsigned int priority)
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
  \exception TaggerException if the Item is not registered to the Tag or if the given Item is null.
  \warning This method doesn't ensure consistency between Item and Tag objects :
  if the Item maintains a Tag list this method has to be wrapped into an other
  function wich ensure Item's Tag list consistency.
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

/*!
  \return a vector containing the registered Items with the given property.
*/
template<typename T>
typename std::vector<T> Tag<T>::getRegisteredItemsWithPriority(unsigned int priority)
{
    return registeredItems_[priority];
}

/*!
  \return a map containing all the registered Items.
 */
template<typename T>
typename Tag<T>::RegisteredItems Tag<T>::getRegisteredItems() const
{
    return registeredItems_;
}

/*!
  \return the number of registered Items for the Tag.
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
  \brief Search in the registered Item map for the given Item.
  \param item the Item to find.
  \return true if at least one instance of the Item has been founded, false otherwise.
  \exception TaggerException if the Item to check for is null.
*/
template<typename T>
bool Tag<T>::containsItem(T item) const
{
    if(item == nullptr) {
        throw TaggerException("The Item to check is null",__FILE__, __LINE__);
    }
    typename RegisteredItems::const_iterator it;
    for(it = registeredItems_.begin(); it != registeredItems_.end(); ++it) {
        for(size_t i = 0; i < it->second.size(); ++i) {
            if(it->second[i]->getId() == item->getId()) {
                return true;
            }
        }
    }
    return false;
}

/*!
  \brief Remove all the instances of a given Item from the registered Item map.
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
