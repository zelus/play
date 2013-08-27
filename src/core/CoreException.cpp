#include "CoreException.h"

#include <sstream>

using namespace std;

/*!
  \brief Construct a CoreException from the given parameters.

  The generated message has the form : "Core exception file *file* line *line* : *message*"

  \param message the custom message of the exception.
  \param file the file name where the exception occured.
  \param line the line number where the exception occured.
 */
CoreException::CoreException(const std::string message, const char* file, int line)
{
    stringstream ss;
    ss << "Core exception file " << file << " line " << line << " : " << message;
    message_ = ss.str();
}

/*!
  \brief Delete the CoreException.
 */
CoreException::~CoreException() throw()
{

}

/*!
  \brief Generic method inherited from std::exception.

  \return an exception safe char* representing the exception message.
 */
const char* CoreException::what() const throw()
{
    return message_.c_str();
}
