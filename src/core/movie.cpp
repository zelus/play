#include "movie.h"

/*!
  \brief Constructs a Movie from the given parameters.

  The given name and parent are delegated to the Item constructor, and
  the ItemType is statically defined as MOVIE_TYPE. The notation and the
  summary are setted to default values (respectively 0 and "").
  \param movieName the name of the Movie.
  \param parent the parent of the Movie
  \todo An other constructor should be defined that allow a Movie creation with
  a given notation and a given summary.
 */
Movie::Movie(const string& movieName, Item* parent) : Item(movieName,MOVIE_TYPE,parent)
{
    notation_ = 0;
    summary_ = "";
}

/*!
  \brief Constructs a Movie from the given Movie.

  Notation and summary of the given movie are also copied.
  \param movie the Movie to construct from.
 */
Movie::Movie(const Movie &movie) : Item(movie.itemName_,MOVIE_TYPE,movie.parent_)
{
    notation_ = movie.notation_;
    summary_ = movie.summary_;
}

/*!
  \brief Deletes the Movie.
  \note Parent management is handled in Item superclass.
 */
Movie::~Movie()
{

}

/*!
  \return the summary of the Movie.
 */
const string& Movie::getSummary() const
{
    return summary_;
}

/*!
  \return the notation of the Movie.
 */
short Movie::getNotation() const
{
    return notation_;
}

/*!
  \brief Sets a new summary to the Movie.
  \param summary the new summary.
 */
void Movie::setSummary(const string &summary)
{
    summary_ = summary;
}

/*!
  \brief Sets a new notation to the Movie.
  \param notation the new notation.
 */
void Movie::setNotation(const short notation)
{
    notation_ = notation;
}
