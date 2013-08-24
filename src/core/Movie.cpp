#include "Movie.h"
#include "ItemVisitor.h"
// debug
#include <iostream>

using namespace std;

/*!
  \brief Constructs a Movie from the given parameters.

  The given name and parent are delegated to the Item constructor, and
  the ItemType is statically defined as MOVIE_TYPE. The notation and the
  summary are setted to default values (respectively 0 and "").
  \param id a unique ID associated to the Movie.
  \param movieName the name of the Movie.
  \param parent the parent of the Movie
  \note There is no consistency checking done on the ID unicity. To create Folders with consistent
  unique ID see \see ItemManager::createMovie method.
 */
Movie::Movie(const string& id, const string& name, Item* parent) : Item(id,name,ItemType::MOVIE_TYPE,parent)
{
    notation_ = 0;
    summary_ = "";
}

/*!
  \brief Constructs a Movie from the given parameters.

  The given name and parent are delegated to the Item constructo, and
  the ItemType is statically defined as MOVIE_TYPE. Notation and summary
  are setted with the given values.
  \param id a unique ID associated to the Movie.
  \param movieName the name of the Movie.
  \param movieSummary the summary of the Movie.
  \param movieNotation the notation of the Movie.
  \param parent the parent of the Movie.
  \note There is no consistency checking done on the ID unicity. To create Folders with consistent
  unique ID see \see ItemManager::createMovie method.
 */
Movie::Movie(const string& id, const string& name, const string& summary, const short notation, Item *parent) : Item(id,name, ItemType::MOVIE_TYPE,parent)
{
    notation_ = notation;
    summary_ = summary;
}

/*!
  \brief Deletes the Movie.
  \note Parent management is handled in Item superclass.
 */
Movie::~Movie()
{
    cout << "delete movie" << endl;
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

void Movie::accept(ItemVisitor* visitor)
{
    visitor->visitMovie(this);
}
