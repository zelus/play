#include "TaggerException.h"

#include <sstream>

using namespace std;

TaggerException::TaggerException(const string message, const char* file, int line)
{
    std::stringstream ss;
    ss << "Tagger exception file " << file << " line " << line << " : " << message;
    message_ = ss.str();
}

TaggerException::~TaggerException() throw()
{

}

const char* TaggerException::what() const throw()
{
    return message_.c_str();
}
