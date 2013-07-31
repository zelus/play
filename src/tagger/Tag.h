#ifndef TAG_H
#define TAG_H

#include <string>
#include <map>
#include <vector>

/*!
  \brief Represents a simple Tag (key-word)

  This class is managed by the TagManager class : it shouldn't
  be manipulated directly (it may break the Tag based search engine).

  \note Tag class is a template class and need a special item interface to
  work properly : the tagged item must provide a public getId() method returning
  a const string&. The return of this method should be a unique identifier of the
  tagged object.

  \warning Tag class only works with pointers (Item* instead of Item).
 */
template<typename T>
class Tag
{
public:
    typedef typename std::map<int, std::vector<T> > RegisteredItems;
    Tag(const std::string tagName);
    Tag(const Tag& tag) = delete;
    Tag<T>& operator=(const Tag<T>&) = delete;
    ~Tag();

    const std::string& getName() const;

    void registerItem(T item, int priority = 0);
    void unregisterItem(T item, int priority = 0);

    std::vector<T> getRegisteredItemsWithPriority(int priority) const;
    RegisteredItems getRegisteredItems() const;

private:
    std::string tagName_;
    RegisteredItems registeredItems_;
};

#include "Tag.tpp"
#endif // TAG_H
