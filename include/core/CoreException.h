#ifndef COREEXCEPTION_H
#define COREEXCEPTION_H

#include <string>
#include <exception>

class CoreException : public std::exception
{
public:
    CoreException(const std::string message, const char* file, int line);
    virtual ~CoreException() throw();
    virtual const char* what() const throw();

private:
    std::string message_;
};

#endif // COREEXCEPTION_H
