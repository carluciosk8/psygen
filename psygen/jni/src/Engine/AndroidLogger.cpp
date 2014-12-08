#include "Engine/AndroidLogger.hpp"


namespace psy {



void AndroidLoggerDebug::log()
{
    __android_log_print(ANDROID_LOG_DEBUG, m_tag.c_str(), "%s", line.str().c_str() );
}



void AndroidLoggerInfo::log()
{
    __android_log_print(ANDROID_LOG_INFO, m_tag.c_str(), "%s", line.str().c_str() );
}



void AndroidLoggerWarning::log()
{
    __android_log_print(ANDROID_LOG_WARN, m_tag.c_str(), "%s", line.str().c_str() );
}



void AndroidLoggerError::log()
{
    __android_log_print(ANDROID_LOG_ERROR, m_tag.c_str(), "%s", line.str().c_str() );
}



}
