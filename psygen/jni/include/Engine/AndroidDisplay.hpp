#pragma once

#include "Engine/Display.hpp"

//#include <list>
#include <android_native_app_glue.h>
#include <EGL/egl.h>

namespace psy {


class AndroidDisplay : public Display
{
public:
    AndroidDisplay(struct android_app* app);
    virtual ~AndroidDisplay();

    // from Display
    virtual void start();
    virtual void update();
    virtual void stop();

private:
    struct android_app* m_android_app;

    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
};


} // end namespace psy
