#pragma once

#include <string>

namespace psy {


class Logger
{
public:
    enum Priority { LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG };

    virtual ~Logger() {}

    virtual void log(Priority priority, const std::string& message) = 0;
    inline  void log(Priority priority, const char* message) { log(priority, std::string(message)); }
};


}
