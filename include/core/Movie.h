#ifndef MOVIE_H
#define MOVIE_H

#include "Item.h"
#include <string>

namespace play_core {

/*!
  \brief Represents a concrete Item which can store specific movie informations.

  The Movie class is a part of the \em composite pattern used to store
  the Item tree. It is derivated from the Item class and represents a movie
  with specific movie informations : summary and notation.

  \note Movie class doesn't override children management method because a Movie
  is a basic Item and can not have children.
 */
class Movie : public Item
{
public:
    Movie(const std::string& name, const std::string& summary="", const short notation=0);
    /*!
      \warning Copy constructor is deleted to prevent ID
      duplication
    */
    Movie(const Movie& movie) = delete;
    /*!
      \warning Assignment operator is deleted to prevent ID
      duplication.
     */
    Movie& operator=(const Movie&) = delete;

    ~Movie();

    const std::string&      getSummary()                                const;
    short                   getNotation()                               const;

    void                    setSummary(const std::string& summary);
    void                    setNotation(const short notation);

    void accept(ItemVisitor& visitor);

private:
    std::string summary_;
    short notation_;
};

} // namespace

#endif // MOVIE_H
