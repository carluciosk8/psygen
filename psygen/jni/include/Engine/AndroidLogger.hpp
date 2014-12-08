#pragma once

#include "Engine/Logger.hpp"

#include <string>
#include <android/log.h>

namespace psy {


class AndroidLoggerDebug : public LoggerDebug
{
public:
    inline AndroidLoggerDebug(const std::string& tag) : m_tag(tag) {}

private:
    std::string m_tag;
    virtual void log();
};


class AndroidLoggerInfo : public LoggerInfo
{
public:
    inline AndroidLoggerInfo(const std::string& tag) : m_tag(tag) {}

private:
    std::string m_tag;
    virtual void log();
};


class AndroidLoggerWarning : public LoggerWarning
{
public:
    inline AndroidLoggerWarning(const std::string& tag) : m_tag(tag) {}

private:
    std::string m_tag;
    virtual void log();
};


class AndroidLoggerError : public LoggerError
{
public:
    inline AndroidLoggerError(const std::string& tag) : m_tag(tag) {}

private:
    std::string m_tag;
    virtual void log();
};


}
