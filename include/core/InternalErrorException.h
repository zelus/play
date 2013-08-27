#ifndef INTERNALERROREXCEPTION_H
#define INTERNALERROREXCEPTION_H

#include "CoreException.h"
#include <string>

/*!
  \brief Specific consistency related exception.

  InternalErrorException is thrown when a major consistency
  issue is detected during the excution (for exemple an Item
  which has a parent that cannot handle sub Item).

  Contains a default generic error message appended by
  a custom message, file name and line number.

  \note InternalErrorException is not handled in the test cases
  (see package test) because must of the time they results from
  a coding error and are not thrown when the code is valid.
 */
class InternalErrorException : public CoreException
{
public:
    InternalErrorException(const std::string& message, const char* file, int line);
    virtual ~InternalErrorException() throw();
};

#endif // INTERNALERROREXCEPTION_H
