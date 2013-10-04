#include "Item.h"
#include "CoreException.h"
#include "IllegalOperationException.h"
#include "ItemVisitor.h"
#include <sstream>

// debug
#include <iostream>

namespace play_core {

using namespace std;

/*!
  \brief Construct an Item with the given name.

  The ID is set to the given name value to allow simple tree construction
  (without ID generation feature).

  \param name the name of the Item.
 */
Item::Item(const std::string& name)
{
    name_ = name;
    id_ = name;
    parent_ = nullptr;
}

/*!
  \brief Delete the Item.

  \warning Consistency with the eventual parent child list is not ensured.
  \see Item::deleteChild for a parent-consistent deletion.
 */
Item::~Item()
{

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

  \exception IllegalOperationException if the current Item cannot handle
  children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global
  interfaces.
  \note This method should be overriden by inherited classes that can handle
  children.
 */
void Item::addChild(Item*)
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Remove the given Item from the child list.

  \param item the Item to remove.

  \exception IllegalOperationException if the current Item cannot handle
  children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global
  interfaces.
  \note This method should be overriden by inherited classes that can handle
  children.
 */
void Item::removeChild(Item*)
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Delete the given Item and remove it from the child list.

  \param item the Item to delete.

  \exception IllegalOperationException if the current Item cannot handle
  children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global
  interfaces.
  \note This method should be overriden by inherited classes that can handle
  children.
 */
void Item::deleteChild(Item*)
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

  \exception IllegalOperationException if the current Item cannot handle
  children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global
  interfaces.
  \note This method should be overriden by inherited classes that can handle
  children.
 */
Item* Item::getChild(const string&) const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Search if a child match the given ID.

  \param id the ID of the wanted Item.
  \return true if at least one child match the given ID, false otherwise.

  \exception IllegalOperationException if the current Item cannot handle
  children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global
  interfaces.
  \note This method should be overriden by inherited classes that can handle
  children.
 */
bool Item::containsChild(const string&) const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Calculate the position of the given child Item in the child list.

  \param item the Item to match in the child list.
  \return the index of the given Item, or -1 if there is no child matching it.

  \exception IllegalOperationException if the current Item cannot handle
  children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global
  interfaces.
  \note This method should be overriden by inherited classes that can handle
  children.
 */
int Item::getChildIndex(Item*) const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \return a vector containing the pointers to Item's children.

  \exception IllegalOperationException if the current Item cannot handle
  children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global
  interfaces.
  \note This method should be overriden by inherited classes that can handle
  children.
 */
const vector<Item*>& Item::getChildren() const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \return the number of children handled by the Item.

  \exception IllegalOperationException if the current Item cannot handle
  children.

  \warning This method fails default because basic Item cannot handle children.
  See design pattern \em composite for further informations about global
  interfaces.
  \note This method should be overriden by inherited classes that can handle
  children.
 */
unsigned int Item::childCount() const
{
    stringstream ss;
    ss << "The Item " << id_ << "[" << name_ << "] is not a container.";
    throw IllegalOperationException(ss.str(),__FILE__,__LINE__);
}

/*!
  \brief Set the parent of the Item to the given parent value.

  \param parent the new parent of the Item.

  \warning Consistency with the parents (new and previous) child list is not
  ensured.
  \see Item::addChild for a parent-consistent deletion.
*/
void Item::setParent(Item* parent)
{
    parent_ = parent;
}

/*!
  \brief Set the ID of the Item to the given value.

  \param id the new ID of the Item.

  \warning If the Item is registered to a context this method may break Item
  unicity.
  \note This method is used internally by ItemContext to provide Item unicity.
 */
void Item::setId(const std::string& id)
{
    id_ = id;
}

} // namespace
