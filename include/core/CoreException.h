#ifndef COREEXCEPTION_H
#define COREEXCEPTION_H

#include <string>
#include <exception>

/*!
  \brief Base exception class of the package core.

  All the exceptions thrown by any of the core components
  are an instance or a subclass of CoreException.

  Contains a default generic error message appended by
  a custom message, file name and line number.
 */
class CoreException : public std::exception
{
public:
    CoreException(const std::string message, const char* file, int line);
    virtual ~CoreException() throw();
    virtual const char* what() const throw();

protected:
    /*!
      The message returned by the what() method.
    */
    std::string message_;
};

#endif // COREEXCEPTION_H
