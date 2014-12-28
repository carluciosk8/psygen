#pragma once

#include "psygen/Display.hpp"

//#include <list>
#include <android_native_app_glue.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

struct GLint4 { GLint x; GLint y; GLint z; GLint w; };
struct GLcolor { GLfloat r; GLfloat g; GLfloat b; GLfloat a; };

namespace psy {


class AndroidDisplay : public Display
{
public:
    AndroidDisplay(struct android_app* app);
    virtual ~AndroidDisplay();

    //static void create(struct android_app* app) { new AndroidDisplay(app); }
    //static void destroy() { if (get_singleton_ptr()) delete get_singleton_ptr(); }

    // from Display
    virtual void start();
    virtual void update();
    virtual void stop();

    static void android_render(unsigned char*);

private:

    struct android_app* m_android_app;


    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
};


} // end namespace psy


//#define android_display_sgt reinterpret_cast<psy::AndroidDisplay&>(AndroidDisplay::get_singleton())
