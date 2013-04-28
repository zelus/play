#include "movie.h"

Movie::Movie(const string& movieName, Item* parent) : Item(movieName,MOVIE_TYPE,parent)
{
    notation_ = 0;
    summary_ = "";
}

Movie::Movie(const Movie &movie) : Item(movie.itemName_,MOVIE_TYPE,movie.parent_)
{
    notation_ = movie.notation_;
    summary_ = movie.summary_;
}

Movie::~Movie()
{

}

const string& Movie::getSummary() const
{
    return summary_;
}

short Movie::getNotation() const
{
    return notation_;
}

void Movie::setSummary(const string &summary)
{
    summary_ = summary;
}

void Movie::setNotation(const short notation)
{
    notation_ = notation;
}
