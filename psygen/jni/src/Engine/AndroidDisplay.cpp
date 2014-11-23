#include "Engine/AndroidDisplay.hpp"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Engine/Logger.hpp"


namespace psy {


AndroidDisplay::AndroidDisplay(struct android_app* android_app)
:
    m_android_app(android_app),
    m_display(NULL),
    m_context(NULL),
    m_surface(NULL),
    m_width(0),
    m_height(0)
{}



AndroidDisplay::~AndroidDisplay()
{
    if (m_display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(m_display, m_context);
        }
        if (m_surface != EGL_NO_SURFACE)
        {
            eglDestroySurface(m_display, m_surface);
        }
        eglTerminate(m_display);
    }
    m_display = EGL_NO_DISPLAY;
    m_context = EGL_NO_CONTEXT;
    m_surface = EGL_NO_SURFACE;
}



// initialize OpenGL ES and EGL
void AndroidDisplay::init()
{
    // Here specify the attributes of the desired configuration.
    // Below, we select an EGLConfig with at least 8 bits per color component compatible with on-screen windows
    const EGLint attribs[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
        EGL_BLUE_SIZE,       8,
        EGL_GREEN_SIZE,      8,
        EGL_RED_SIZE,        8,
        EGL_NONE
    };

    EGLint contextAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLint format;
    EGLint numConfigs;
    EGLConfig config;

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(m_display, NULL, NULL);

    // Here, the application chooses the configuration it desires.
    // In this sample, we have a very simplified selection process, where we pick the first EGLConfig that matches our criteria
    eglChooseConfig(m_display, attribs, &config, 1, &numConfigs);

    // EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
    // As soon as we picked a EGLConfig, we can safely reconfigure the ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
    eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(m_android_app->window, 0, 0, format);

    m_surface = eglCreateWindowSurface(m_display, config, m_android_app->window, NULL);
    m_context = eglCreateContext(m_display, config, NULL, contextAttribs);

    if (eglMakeCurrent(m_display, m_surface, m_surface, m_context) == EGL_FALSE)
    {
        //LOGW("Unable to eglMakeCurrent");
        //return -1;
    }

    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height);


    glViewport(0, 0, m_width, m_height);
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}


} // end namespace psy
