#include "InternalErrorException.h"
#include <sstream>

namespace play_core {

using namespace std;
/*!
  \brief Construct an InternalErrorException from the given parameters.

  The generated message has the form "Internal error exception file *file* line *line* : *message*"

  \param message the custom message of the exception.
  \param file the file name where the exception occured.
  \param line the line number where the exception occured.
 */
InternalErrorException::InternalErrorException(const std::string& message, const char* file, int line) : CoreException(message,file,line)
{
    stringstream ss;
    ss << "Internal error exception file " << file << " line " << line << " : " << message;
    message_ = ss.str();
}

/*!
  \brief Delete the InternalErrorException.
 */
InternalErrorException::~InternalErrorException() throw()
{

}

} // namespace
