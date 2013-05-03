/*!
  \file movie.h
  \author Gwendal Daniel
  \date 2013-04-28
 */

#ifndef MOVIE_H
#define MOVIE_H

#include "common.h"
#include "item.h"

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
    Movie(const string& movieName = "", Item* parent = nullptr);
    Movie(const string& movieName, const string& movieSummary, const short movieNotation, Item* parent = nullptr);
    Movie(const Movie& movie);
    ~Movie();

    const string& getSummary() const;
    short getNotation() const;

    void setSummary(const string& summary);
    void setNotation(const short notation);

private:
    string summary_;
    short notation_;
};

#endif // MOVIE_H
