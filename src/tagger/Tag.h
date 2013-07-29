#ifndef TAG_H
#define TAG_H

#include <string>
#include <vector>

/*!
  \brief Represents a simple Tag (key-word)

  This class is managed by the TagManager class : it shouldn't
  be manipulated directly (it may break the global consistency of
  the application).
 */
template<typename T>
class Tag
{
public:
    typedef typename std::vector<T> RegisteredItems;
    Tag(const std::string tagName);
    Tag(const Tag& tag);
    ~Tag();

    const std::string& getName() const;

    void registerItem(T item);
    void unregisterItem(T item);

    RegisteredItems getAllRegisteredItems() const;
private:
    std::string tagName_;
    RegisteredItems registeredItems_;
};

#include "Tag.tpp"
#endif // TAG_H
