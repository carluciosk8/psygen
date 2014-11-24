#include "Engine/AndroidApplication.hpp"

#include <android_native_app_glue.h>

namespace psy {



AndroidPlatform::AndroidPlatform(struct android_app* android_application)
:
    m_android_app(android_application)
{
    app_dummy();
    m_android_app->userData = this;
    android_application->onAppCmd = engine_handle_cmd;
}


AndroidPlatform::~AndroidPlatform()
{}


void AndroidPlatform::init()
{}


void AndroidPlatform::shutdown()
{}


void AndroidPlatform::engine_handle_cmd(struct android_app* app, int32_t cmd)
{
    switch (cmd)
    {
    case APP_CMD_INIT_WINDOW:
        // The window is being shown, get it ready.
        //m_is_running = true;
        break;

    case APP_CMD_TERM_WINDOW:
        // The window is being hidden or closed, clean it up.
        //m_is_running = false;
        break;
    }
}
} // end namespace psy
