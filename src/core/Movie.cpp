#include "Movie.h"
#include "ItemVisitor.h"
// debug
#include <iostream>

namespace play_core {

using namespace std;

/*!
  \brief Construct a Movie with the given name, summary and notation.

  \param name the name of the Movie.
  \param summary the summary of the Movie.
  \param notation the notation of the Movie.
 */
Movie::Movie(const std::string& name, const std::string& summary, const short notation) : Item(name)
{
    notation_ = notation;
    summary_ = summary;
}

/*!
  \brief Delete the Movie.
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

} // namespace
