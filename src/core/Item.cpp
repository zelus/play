#include "Item.h"
#include "CoreException.h"
#include "IllegalOperationException.h"
#include "ItemVisitor.h"
#include <sstream>
// debug
#include <iostream>


#include "ItemTree.h"
using namespace std;

/*!
  \brief Construct an Item with the given name in the given context (ItemTree)

  \param name the name of the Item.
  \param itemTree the tree the Item belongs to.

  \note The given ItemTree affects an ID and a default parent to the Item.
 */
Item::Item(const std::string& name, ItemTree& itemTree) : itemTree_(itemTree)
{
    name_ = name;
    itemTree_ = itemTree;
    itemTree.registerItem(this);
}

/*!
  \brief Deletes the Item.

  If the Item has a parent it is removed from its children list.
 */
Item::~Item()
{
    if(parent_ != nullptr) {
        try {
            parent_->removeSubItem(this);
        }catch(CoreException&) {
            /*
              Nothing need to be done here : the parent doesn't handle
              the Item. This append when parent calls itself this method
              and has removed the Item from its children before.

              If the exception is the result of an invalid call
              (IllegalOperationException) the exception is ignored.
             */
        }
    }
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
 */
const string& Item::getId() const
{
    return id_;
}

/*!
  \return the name of the Item.
 */
const string& Item::getName() const
{
    return name_;
}

/*!
  \brief Set a new name to the Item.

  \param name the new name of the Item.
 */
void Item::setName(const string& name)
{
    name_ = name;
}

/*!
  \brief Add the given Item to the child list.

  \param item the Item to add.

  \exception IllegalOperationException if the Item cannot handle children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::addSubItem(Item*)
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Remove the given Item from the child list.

  \param item the Item to remove.

  \exception IllegalOperationException if the Item cannot handle children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::removeSubItem(Item*)
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Delete the given Item and remove it from the child list.

  \param item the Item to delete.

  \exception IllegalOperationException if the Item cannot handle children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
void Item::deleteSubItem(Item*)
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Search if a child match the given ID and return it.

  \param id the ID of the wanted Item.
  \return a pointer to the Item if at least one child match the given ID,
  nullptr otherwise.

  \exception IllegalOperationException if the Item cannot handle children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
Item* Item::getSubItem(const string&) const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Search if a child match the given ID.

  \param id the ID of the wanted Item.
  \return true if at least one child match the given ID, false otherwise.

  \exception IllegalOperationException if the Item cannot handle children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
bool Item::containsSubItem(const string&) const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Calculate the position of the given item in the child list.

  \param item the Item to match in the child list.
  \return the index of the given Item, or -1 if there is no child matching it.

  \exception IllegalOperationException if the Item cannot handle children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
int Item::getSubItemIndex(Item*) const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \return a vector containing the pointers to Item's children.

  \exception IllegalOperationException if the Item cannot handle children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
const vector<Item*>& Item::getAllSubItems() const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \return the number of children handled by the Item.

  \exception IllegalOperationException if the Item cannot handle children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global interfaces.
  \note This method should be overriden by inherited classes that can handle children.
 */
unsigned int Item::getSubItemNumber() const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Set the parent member of the Item to the given parent value.

  \param parent the new parent of the Item.

  \warning Don't call this method directly, it is used by the context to ensure
  tree consistency. To change the parent of an Item use addSubItem and removeSubItem
  methods instead.
*/
void Item::setParent(Item* parent)
{
    parent_ = parent;
}

/*!
  \brief Set the ID member of the Item to the given value.

  \param id the new ID of the Item.

  \warning Don't call this method directly, it is used by the context to give
  a unique ID to the Item.
 */
void Item::setId(const std::string& id)
{
    id_ = id;
}
