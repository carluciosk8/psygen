#pragma once

#include "Engine/Display.hpp"

#include <android_native_app_glue.h>
#include <EGL/egl.h>

namespace psy {


class AndroidDisplay : public Display
{
public:
    AndroidDisplay(struct android_app* app);
    virtual ~AndroidDisplay();

    // from Subsystem
    virtual void init();
    virtual void shutdown();

    // from Display
    virtual void begin_frame();
    virtual void end_frame();


private:
    struct android_app* m_android_app;

    EGLDisplay m_display;
    EGLContext m_context;
    EGLSurface m_surface;
    EGLint     m_width;
    EGLint     m_height;
};


} // end namespace psy
