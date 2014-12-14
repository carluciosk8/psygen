#include "Engine/AndroidLogger.hpp"

#include <sstream>

namespace psy {

static std::stringstream tag;

const char* logtag(const char* file, int line)
{
    tag.str( std::string() );
    tag.clear();
    tag << file << ":" << line;
    return tag.str().c_str();
}

}
