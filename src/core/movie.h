#ifndef MOVIE_H
#define MOVIE_H

#include "item.h"

class Movie : public Item
{
public:
    Movie(const string& movieName = "", Item* parent = nullptr);
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
