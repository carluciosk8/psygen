#include "Engine/AndroidLogger.hpp"

namespace psy {



AndroidLogger::AndroidLogger(const std::string& tag)
:
    m_tag(tag)
{
    m_priority_table[Priority::ERROR]   = ANDROID_LOG_ERROR;
    m_priority_table[Priority::WARNING] = ANDROID_LOG_WARN;
    m_priority_table[Priority::INFO]    = ANDROID_LOG_INFO;
    m_priority_table[Priority::DEBUG]   = ANDROID_LOG_DEBUG;

    (DEBUG, "AndroidLogger constructed");
}



AndroidLogger::~AndroidLogger()
{
    (DEBUG, "AndroidLogger destructed");
}



void AndroidLogger::operator ()(Priority priority, const std::string& message)
{
    __android_log_print(m_priority_table[priority], m_tag.c_str(), "%s", message.c_str());
}

}
