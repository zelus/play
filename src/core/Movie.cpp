#include "Movie.h"
#include "ItemVisitor.h"
// debug
#include <iostream>

using namespace std;

/*!
  \brief Construct a Movie with the given name in the given context (ItemTree).

  Summary and notation are set to their default values (respectively an empty string
  and 0).

  \param name the name of the Movie.
  \param itemTree the tree the Movie belongs to.
 */
Movie::Movie(const std::string name, ItemTree& itemTree) : Item(name,itemTree)
{
    summary_ = "";
    notation_ = 0;
}

/*!
  \brief Construct a Movie with the given name, summary and notation in
  the context (ItemTree).

  \param name the name of the Movie.
  \param summary the summary of the Movie.
  \param notation the notation of the Movie.
  \param itemTree the tree the Movie belongs to.
 */
Movie::Movie(const std::string& name, const std::string& summary, const short notation, ItemTree& itemTree) : Item(name,itemTree)
{
    notation_ = notation;
    summary_ = summary;
}

/*!
  \brief Deletes the Movie.

  The Movie is also removed of its parent child list.
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
  \brief Set a new summary to the Movie.

  \param summary the new summary.
 */
void Movie::setSummary(const string& summary)
{
    summary_ = summary;
}

/*!
  \brief Set a new notation to the Movie.

  \param notation the new notation.
 */
void Movie::setNotation(const short notation)
{
    notation_ = notation;
}

/*!
  \brief Call dedicated Movie handler in given visitor.

  \param visitor the ItemVisitor to use through the Movie.
 */
void Movie::accept(ItemVisitor& visitor)
{
    visitor.visitMovie(this);
}
