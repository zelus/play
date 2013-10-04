#include "IllegalOperationException.h"
#include <sstream>

namespace play_core {

using namespace std;

/*!
  \brief Construct an IllegalOperationException from the given parameters.

  The generated message has the form : "Illegal operation exception file *file* line *line* : *message*"

  \param message the custom message of the exception.
  \param file the file name where the exception occured.
  \param line the line number where the exception occured.
 */
IllegalOperationException::IllegalOperationException(const string message, const char* file, int line) : CoreException(message,file,line)
{
    stringstream ss;
    ss << "Illegal operation exception file " << file << " line " << line << " : " << message;
    message_ = ss.str();
}

/*!
  \brief Delete the IllegalOperationException.
 */
IllegalOperationException::~IllegalOperationException() throw()
{

}

} // namespace
