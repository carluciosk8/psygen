#include "Engine/AndroidLogger.hpp"

namespace psy {



AndroidLogger::AndroidLogger(const std::string& tag)
:
    m_tag(tag)
{
    m_priority_table[Priority::LOG_ERROR]   = ANDROID_LOG_ERROR;
    m_priority_table[Priority::LOG_WARNING] = ANDROID_LOG_WARN;
    m_priority_table[Priority::LOG_INFO]    = ANDROID_LOG_INFO;
    m_priority_table[Priority::LOG_DEBUG]   = ANDROID_LOG_DEBUG;

    log(LOG_INFO, "AndroidLogger started");
}



void AndroidLogger::log(Priority priority, const std::string& message)
{
    __android_log_print(m_priority_table[priority], m_tag.c_str(), "%s", message.c_str());
}



}
