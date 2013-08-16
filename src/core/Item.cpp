#include "Item.h"
#include "Folder.h"
#include "Tag.h"
#include "CoreException.h"
#include <stdexcept>
#include <sstream>
// debug
#include <iostream>

const int Item::name_priority = 1;

/*!
  \brief Constructs an Item from the given parameters.
  \note If a parent is given the constructed Item is added to its parent child list.
  \param itemName The name of the Item.
  \param itemType The type of the Item.
  \param parent The parent of the Item.
  \exception std::logic_error if the given parent cannot handle subItems.
 */
Item::Item(const string& itemName, ItemType itemType, Item* parent, TagManager<Item*>* tagManager)
{
    itemName_ = itemName;
    parent_ = parent;
    itemType_ = itemType;
    tagManager_ = tagManager;
    addTags(itemName,name_priority);
    if(parent_ != nullptr) {
        try {
            parent_->addSubItem(this);
        }catch(logic_error& e) {
            throw e;
        }
    }
}

/*!
  \brief Deletes the Item and its references into its Tags.

  The reference of the Item in each Tag it is registered to is
  deleted.

  \bug No composite pattern consistency checking.
 */
Item::~Item()
{
    deleteTags(itemName_,name_priority);
}

/*!
  \return the parent of the Item.
 */
Item* Item::getParent() const
{
    return parent_;
}

/*!
  \return the id of the Item.
  \note This method is required by the Tag template.
  \bug The method return the name of the Item, a unique ID must
  be returned containing the full path of the item.
 */
const string& Item::getId() const
{
    return itemName_;
}

/*!
  \return the name of the Item.
 */
const string& Item::getName() const
{
    return itemName_;
}

/*!
  \return the ItemType of the Item.
 */
ItemType Item::getType() const
{
    return itemType_;
}

/*!
  \brief Set a new parent to the Item.
  \param parent the new parent.
  \bug This method doesn't ensure consistency of the
  composite pattern : the Item is not removed from its eventual parent,
  if you want to remove an Item from its parent you have to use
  Item::removeSubItem parent method instead.
 */
void Item::setParent(Item *parent)
{
    parent_ = parent;
}

/*!
  \brief Set a new name to the Item.

  The Tag list is also updated with the new name.

  \param name the new name of the Item.
 */
void Item::setName(const std::string& name)
{
    updateTags(itemName_,name,name_priority);
    itemName_ = name;
}

/*!
  \brief Basic implementation of the addSubItem method.
  \param item the Item to add to the child list.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::addSubItem(Item *item)
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the removeSubItem method.
  \param item the Item to remove from the child list.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::removeSubItem(Item *item)
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the deleteSubItem method.
  \param item the Item to remove from the child list.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::deleteSubItem(Item *item)
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the getSubItem method.
  \param itemName the name of the wanted Item.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
Item* Item::getSubItem(const string &itemName) const
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the containsSubItem method.
  \param itemName the name of the wanted Item.
  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
bool Item::containsSubItem(const string &itemName) const
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Basic implementation of the getAllSubItems method.

  \exception std::logic_error if the Item can not have children.
  \warning This method fails default because basic Items are not allowed to have children.
  See design pattern \em composite for further imformations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
ItemList Item::getAllSubItems() const
{
    stringstream ss;
    ss << "The Item " << itemName_ << " is not a container.";
    throw CoreException(ss.str(),__FILE__,__LINE__);
}

/*!
  \return the list of Tag associated to the Item.
 */
Item::Tags Item::getAllTags() const
{
    return tagList_;
}

/*!
  \brief Add Tags from the given value (with the given priority) of the Tag list.

  The Tags are extracted from the given value by the TagManager associated to the
  Tag. It ensures consistency between Tags in the Item's list and Tags registered in
  the TagManager. (\see TagManager::createTagsFromItem).

  \param value the value to tag.
  \param priority the priority of the value (see static const values).

  \exception CoreException if the Item is not associated to a TagManager.
  \note If the given value is empty the Tag map is unchanged.
  \note This method should be overriden by inherited classes that would change Tag processing
  (for example delete some specific tokens from value before send it to the TagManager).
 */
void Item::addTags(const string& value, unsigned int priority)
{
    if(tagManager_ == nullptr) {
        stringstream ss;
        ss << "No TagManager associated to the Item " << itemName_ << ".";
        throw CoreException(ss.str(),__FILE__,__LINE__);
    }
    else {
        std::vector<Tag<Item*>*>& tags = tagList_[priority];
        if(value.empty()) {
            // No Tag to add to the Tag map.
            return ;
        }
        else {
            const std::vector<Tag<Item*>*>& new_tags = tagManager_->createTagsFromItem(value,this,priority);
            std::vector<Tag<Item*>*>::const_iterator it;
            for(it = new_tags.begin(); it != new_tags.end(); ++it) {
                tags.push_back(*it);
            }
        }
    }
}

/*!
  \brief Delete Tags from the given value (with the given priority) of the Tag list.

  The Tags are extracted from the priority level and send to the TagManager for a consistent
  deletion. It ensures consistency between Tags in the Item's list and Tags registered in
  the TagManager. (\see TagManager::deleteTagsFromItem).

  \param value the value to tag.
  \param priority the priority of the value (see static const values).

  \exception CoreException if the Item is not associated to a TagManager.
  \note If the given value is empty the Tag map is unchanged.
  \note This implementation deletes all the Tag registered to the given priority,
  including those which are not extracted from the value. If an other implementation
  is needed in sub Items this method should be overriden.
 */
void Item::deleteTags(const string& value, unsigned int priority)
{
    if(tagManager_ == nullptr) {
        stringstream ss;
        ss << "No TagManager associated to the Item " << itemName_ << ".";
        throw CoreException(ss.str(),__FILE__,__LINE__);
    }
    else {
        std::vector<Tag<Item*>*>& tags = tagList_[priority];
        if(value.empty()) {
            // No Tag to delete from the Tag map.
        }
        else {
            tagManager_->deleteTagsFromItem(tags,this,priority);
            if(!tags.empty()) {
                tags.clear();
            }
        }
    }
}

/*!
  \brief Update Tags from the given oldValue to the given newValue (with the given priority) of the Tag list.

  Consistency between Tags in the Item's list and Tags registered in
  the TagManager is ensured.

  \param oldValue the value to delete Tags from.
  \param newValue the value to create Tags from.
  \param priority the priority of the values (see static const values).

  \exception CoreException if the Item is not associated to a TagManager.
  \note If the given values are empty the Tag map is unchanged.
  \note This impementation is just a basic call to deleteTags(oldValue,priority)
  followed by a call to addTags(newValue,priority). If an other implementation is
  needed in sub Items this method should be overriden.
 */
void Item::updateTags(const string &oldValue, const string &newValue, unsigned int priority)
{
    try {
        deleteTags(oldValue,priority);
        addTags(newValue,priority);
    }catch(CoreException& e) {
        throw e;
    }
}
