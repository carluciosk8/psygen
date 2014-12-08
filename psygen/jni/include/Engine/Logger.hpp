#pragma once

#include <string>
#include <sstream>

#include "Engine/Singleton.hpp"


namespace psy {


class Logger
{
public:
    virtual ~Logger() {}

    template <class T> Logger& operator << ( const T& Value );
    inline             Logger& operator << ( std::ostream&(*f)(std::ostream&) );

protected:
    std::stringstream line;

private:
    virtual void log() = 0;
};


class LoggerDebug   : public Logger, public Singleton<LoggerDebug> {};
class LoggerInfo    : public Logger, public Singleton<LoggerInfo> {};
class LoggerWarning : public Logger, public Singleton<LoggerWarning> {};
class LoggerError   : public Logger, public Singleton<LoggerError> {};

#define log_debug_sgt     LoggerDebug::get_singleton()
#define log_info_sgt      LoggerInfo::get_singleton()
#define log_warning_sgt   LoggerWarning::get_singleton()
#define log_error_sgt     LoggerError::get_singleton()


}


#include "Logger.inl"
