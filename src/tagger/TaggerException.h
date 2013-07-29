#ifndef TAGGEREXCEPTION_H
#define TAGGEREXCEPTION_H

#include <string>
#include <exception>

class TaggerException : public std::exception
{
public:
    TaggerException(const std::string message, const char* file, int line);
    virtual ~TaggerException() throw();
    virtual const char* what() const throw();

private:
    std::string message_;
};

#endif // TAGGEREXCEPTION_H
