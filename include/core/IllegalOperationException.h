#ifndef ILLEGALOPERATIONEXCEPTION_H
#define ILLEGALOPERATIONEXCEPTION_H

#include "CoreException.h"
#include <string>

/*!
  \brief Specific \em composite related exception.

  IllegalOperationException is thrown when a globally
  defined method is called on an object that cannot handle
  it (for example addSubItem on a Movie Item).

  Contains a default generic error message appended by
  a custom message, file name and line number.
 */
class IllegalOperationException : public CoreException
{
public:
    IllegalOperationException(const std::string message, const char* file, int line);
    virtual ~IllegalOperationException() throw();
};

#endif // ILLEGALOPERATIONEXCEPTION_H
