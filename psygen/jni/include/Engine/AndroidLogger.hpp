#pragma once

#include <android/log.h>

namespace psy { const char* logtag(const char*, int); }

#define PSY_LOG_DBG(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, psy::logtag(__FILE__,__LINE__), __VA_ARGS__))
#define PSY_LOG_INF(...) ((void)__android_log_print(ANDROID_LOG_INFO,  psy::logtag(__FILE__,__LINE__), __VA_ARGS__))
#define PSY_LOG_WRN(...) ((void)__android_log_print(ANDROID_LOG_WARN,  psy::logtag(__FILE__,__LINE__), __VA_ARGS__))
#define PSY_LOG_ERR(...) ((void)__android_log_print(ANDROID_LOG_ERROR, psy::logtag(__FILE__,__LINE__), __VA_ARGS__))
