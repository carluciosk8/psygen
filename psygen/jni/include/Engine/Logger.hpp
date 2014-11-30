#pragma once

#include "Engine/Singleton.hpp"

#include <string>

namespace psy {


class Logger : public Singleton<Logger>
{
public:
    enum Priority
    {
        ERROR,
        WARNING,
        INFO,
        DEBUG
    };

    virtual ~Logger() {}

    virtual void operator ()(Priority priority, const std::string& message) = 0;
    virtual void         log(Priority priority, const std::string& message) = 0;

    inline  void operator ()(Priority priority, const char* message) { log(priority, std::string(message)); }
    inline  void         log(Priority priority, const char* message) { log(priority, std::string(message)); }
};

#define sg_logger Logger::GetSingleton()

}
