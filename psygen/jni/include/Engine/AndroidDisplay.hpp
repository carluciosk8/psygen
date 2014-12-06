#pragma once

#include "Engine/Subsystem.hpp"

#include <list>
#include <android_native_app_glue.h>
#include <EGL/egl.h>

namespace psy {

class RenderCommand;

class AndroidDisplay : public Subsystem
{
public:
    AndroidDisplay(struct android_app* app);
    virtual ~AndroidDisplay();

    // from Subsystem
    virtual void init();
    virtual void update();
    virtual void shutdown();

    inline void add_command(RenderCommand* cmd) { m_render_program.push_back(cmd); }

    inline int get_width() { return m_width; }
    inline int get_height() { return m_height; }

protected:
    EGLDisplay m_display;
    EGLSurface m_surface;
    friend class GlSwapBuffers;

    std::list<RenderCommand*> m_render_program;


private:
    struct android_app* m_android_app;

    EGLContext m_context;
    EGLint     m_width;
    EGLint     m_height;
};

#define sg_android_display      reinterpret_cast<psy::AndroidDisplay&>(psy::Subsystem::get_singleton())
#define sg_android_display_ptr  reinterpret_cast<psy::AndroidDisplay*>(psy::Subsystem::get_singleton_ptr())

} // end namespace psy
