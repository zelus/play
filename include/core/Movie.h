#ifndef MOVIE_H
#define MOVIE_H

#include "Item.h"
#include <string>

/*!
  \brief Represents a concrete Item with movies informations

  The Movie class is a part of the \em composite pattern used to store
  the Item tree. It is derivated from the Item class and represents a movie
  with specific movie informations : summary and notation.
  \note Movie class doesn't override children management method because a Movie
  is a basic Item and can not have children.
 */
class Movie : public Item
{
public:
    Movie(const std::string& id, const std::string& name, Item* parent = nullptr);
    Movie(const std::string& id, const std::string& name, const std::string& summary, const short notation, Item* parent = nullptr);
    Movie(const Movie& movie) = delete;
    ~Movie();

    const std::string& getSummary() const;
    short getNotation() const;

    void setSummary(const std::string& summary);
    void setNotation(const short notation);

    void accept(ItemVisitor* visitor);

private:
    std::string summary_;
    short notation_;
};

#endif // MOVIE_H
