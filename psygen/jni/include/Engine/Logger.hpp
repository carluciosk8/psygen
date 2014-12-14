#pragma once

#if ANDROID
    #include "AndroidLogger.hpp"
#elif LINUX
    #include "LinuxLogger.hpp"
#elif WINDOWS
    #include "WindowsLogger.hpp"
#else
    #define PSY_LOG_DBG(...)
    #define PSY_LOG_INF(...)
    #define PSY_LOG_WRN(...)
    #define PSY_LOG_ERR(...)
#endif
