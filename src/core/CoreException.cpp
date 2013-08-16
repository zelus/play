#include "CoreException.h"

#include <sstream>

using namespace std;

CoreException::CoreException(const string message, const char* file, int line)
{
    stringstream ss;
    ss << "Core exception file " << file << " line " << line << " : " << message;
    message_ = ss.str();
}

CoreException::~CoreException() throw()
{

}

const char* CoreException::what() const throw()
{
    return message_.c_str();
}
