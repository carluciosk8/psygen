#pragma once

#include <android_native_app_glue.h>

#include "Engine/Platform.hpp"

namespace psy {


class AndroidPlatform: public Platform
{
public:
    AndroidPlatform(struct android_app* android_application);
    virtual ~AndroidPlatform();

    virtual void init();
    virtual void shutdown();


private:
    struct android_app* m_android_app;

    static void    engine_handle_cmd(struct android_app* app, int32_t cmd);
};


} // end namespace psy
