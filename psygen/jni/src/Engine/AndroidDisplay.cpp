#include "Engine/AndroidDisplay.hpp"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Engine/Logger.hpp"
#include "Engine/RenderCommand.hpp"


namespace psy {


AndroidDisplay::AndroidDisplay(struct android_app* app)
:
    m_android_app(app),
    m_display(EGL_NO_DISPLAY),
    m_context(EGL_NO_CONTEXT),
    m_surface(EGL_NO_SURFACE),
    m_width(0),
    m_height(0)

{
    m_initialized = false;
}



AndroidDisplay::~AndroidDisplay()
{
    for (RenderCommand* cmd : m_render_program)
        delete cmd;

    m_render_program.clear();
}



// initialize OpenGL ES and EGL
void AndroidDisplay::init()
{
    sg_logger(Logger::DEBUG, "AndroidDisplay::init()");

    const EGLint attribs[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
        EGL_BLUE_SIZE,       8,
        EGL_GREEN_SIZE,      8,
        EGL_RED_SIZE,        8,
        EGL_NONE
    };

    EGLint context_attribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLint format;
    EGLint num_configs;
    EGLConfig config;

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(m_display, NULL, NULL);
    eglChooseConfig(m_display, attribs, &config, 1, &num_configs);
    eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(m_android_app->window, 0, 0, format);

    m_surface = eglCreateWindowSurface(m_display, config, m_android_app->window, NULL);
    m_context = eglCreateContext(m_display, config, NULL, context_attribs);

    if (not eglMakeCurrent(m_display, m_surface, m_surface, m_context))
    {
        sg_logger(Logger::WARNING, "Unable to eglMakeCurrent");
        return;
    }

    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height);

    m_initialized = true;
}



void AndroidDisplay::update()
{
    if (m_initialized)
    {
        for (RenderCommand* cmd : m_render_program)
            cmd->execute();

        eglSwapBuffers(m_display, m_surface);
    }
}



void AndroidDisplay::shutdown()
{
    m_initialized = false;

    if (m_display not_eq EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_context not_eq EGL_NO_CONTEXT) eglDestroyContext(m_display, m_context);
        if (m_surface not_eq EGL_NO_SURFACE) eglDestroySurface(m_display, m_surface);
        eglTerminate(m_display);
    }

    m_display = EGL_NO_DISPLAY;
    m_context = EGL_NO_CONTEXT;
    m_surface = EGL_NO_SURFACE;
}


} // end namespace psy
