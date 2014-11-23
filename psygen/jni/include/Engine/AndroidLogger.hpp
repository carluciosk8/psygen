#pragma once

#include "Engine/Logger.hpp"

#include <string>
#include <android/log.h>

namespace psy {


class AndroidLogger : public Logger
{
public:
    AndroidLogger(const std::string& tag);
    virtual ~AndroidLogger() {}

    virtual void log(Priority priority, const std::string& message);


private:
    std::string m_tag;

    android_LogPriority m_priority_table[4];
};


}
