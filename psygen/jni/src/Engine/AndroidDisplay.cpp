#include "Engine/AndroidDisplay.hpp"

#include <GLES2/gl2ext.h>

#include "psygen/Logger.hpp"
#include "psygen/Application.hpp"
#include "psygen/RenderCommand.hpp"


namespace psy {

AndroidDisplay::AndroidDisplay(struct android_app* app)
:
    m_android_app(app),
    m_display(EGL_NO_DISPLAY),
    m_context(EGL_NO_CONTEXT),
    m_surface(EGL_NO_SURFACE)
{
    PSY_LOG_DBG("    Creating new task AndroidDisplay");

    m_initialized = false;
    m_width = 0;
    m_height = 0;
    //m_active_program = nullptr;
    m_glasm_prg = nullptr;
    render = android_render;
}



AndroidDisplay::~AndroidDisplay()
{
    PSY_LOG_DBG("    deleting task AndroidDisplay");
}



// initialize OpenGL ES and EGL
void AndroidDisplay::start()
{
    PSY_LOG_DBG("    Starting task AndroidDisplay");

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
        PSY_LOG_WRN("    Unable to eglMakeCurrent");
        return;
    }

    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height);

    m_initialized = true;
}



void AndroidDisplay::update()
{
    if ( application_sgt.is_running() )
    {
        //m_active_program->execute();

        android_render(m_glasm_prg);

        eglSwapBuffers(m_display, m_surface);
    }
}



void AndroidDisplay::android_render(unsigned char* prg)
{
    if (prg)
    {
        const unsigned char* pc = prg;
        GLASM cmd = *((GLASM*) pc);


        union
        {
            struct {GLint loc; GLfloat* pval;} uniform1fp ;
            GLbitfield     bitfield;
            GLint4          int4;
            GLcolor         color;
            GLenum         state;
            unsigned char* addr;
            GLuint         shader;
            GLuint         texture;
            struct
            {
                GLenum    primitive;
                GLuint    handler[2];
                GLint     num_indices;
                GLubyte   stride;
                GLubyte   num_attr;
                GLubyte   attr[32];
            } geometry;
        } value;


        for (pc += sizeof(GLASM) ; cmd != GLASM::END ; cmd = *((GLASM*) pc), pc += sizeof(GLASM) )
        {
            switch (cmd)
            {
            case GLASM::CLR:
                GLASM_NEXT(pc, GLbitfield, value.bitfield);
                //PSY_LOG_DBG("        glClear(0x%X)", value.bitfield);
                glClear(value.bitfield);
                break;


            case GLASM::CCL:
                GLASM_NEXT(pc, GLcolor, value.color);
                //PSY_LOG_DBG("        glClearColor(%f, %f, %f, %f)", value.color.r, value.color.g, value.color.b, value.color.a);
                glClearColor(value.color.r, value.color.g, value.color.b, value.color.a);
                break;

            case GLASM::DIS:
                GLASM_NEXT(pc, GLenum, value.state);
                //PSY_LOG_DBG("        glDisable(0x%X)", value.state);
                glDisable(value.state);
                break;

            case GLASM::SHD:
                GLASM_NEXT(pc, GLuint, value.shader);
                //PSY_LOG_DBG("        glUseProgram(%d)", value.shader);
                glUseProgram(value.shader);
                break;

            case GLASM::TEX:
                GLASM_NEXT(pc, GLuint, value.texture);
                //PSY_LOG_DBG("        glActiveTexture(%d)", value.texture);
                glActiveTexture(value.texture);
                break;

            case GLASM::UF1:
                GLASM_NEXT(pc, GLint, value.uniform1fp.loc);
                GLASM_NEXT(pc, GLfloat*, value.uniform1fp.pval);
                PSY_LOG_DBG("        glUniform1f(%d, %f)", value.uniform1fp.loc, *value.uniform1fp.pval);
                glUniform1f(value.uniform1fp.loc, *value.uniform1fp.pval);
                break;

            case GLASM::UF2:
                GLASM_NEXT(pc, GLint, value.uniform1fp.loc);
                GLASM_NEXT(pc, GLfloat*, value.uniform1fp.pval);
                PSY_LOG_DBG("        glUniform2f(%d, %f, %f)", value.uniform1fp.loc, value.uniform1fp.pval[0], value.uniform1fp.pval[1]);
                glUniform2fv(value.uniform1fp.loc, 1, value.uniform1fp.pval);
                break;

            case GLASM::VBO:
                GLASM_NEXT(pc, GLenum, value.geometry.primitive);
                GLASM_NEXT(pc, GLuint, value.geometry.handler[0]);
                GLASM_NEXT(pc, GLuint, value.geometry.handler[1]);
                GLASM_NEXT(pc, GLint, value.geometry.num_indices);
                GLASM_NEXT(pc, GLubyte, value.geometry.stride);
                GLASM_NEXT(pc, GLubyte, value.geometry.num_attr);

                //PSY_LOG_DBG("            glBindBuffer(GL_ARRAY_BUFFER, %d);", value.geometry.handler[0]);
                //PSY_LOG_DBG("            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, %d);", value.geometry.handler[1]);
                glBindBuffer(GL_ARRAY_BUFFER, value.geometry.handler[0]);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, value.geometry.handler[1]);

                for (int i=0 , p=0 ; i<value.geometry.num_attr ; p += value.geometry.attr[i]*sizeof(GLfloat) , ++i)
                {
                    //PSY_LOG_DBG("            glEnableVertexAttribArray(%d);", i);
                    //PSY_LOG_DBG("            glVertexAttribPointer(%d, %d, GL_FLOAT, GL_FALSE, %d, (const void*)%d);", i, value.geometry.attr[i], value.geometry.stride, p);
                    GLASM_NEXT(pc, GLubyte, value.geometry.attr[i]);
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, value.geometry.attr[i], GL_FLOAT, GL_FALSE, value.geometry.stride, (const void*)p);
                }

                //PSY_LOG_DBG("            glDrawElements(%d, %d, GL_UNSIGNED_SHORT, 0);", value.geometry.primitive_type, value.geometry.num_indices);
                glDrawElements(value.geometry.primitive, value.geometry.num_indices, GL_UNSIGNED_SHORT, 0);

                for (GLubyte i=0 ; i<value.geometry.num_attr ; ++i)
                {
                    //PSY_LOG_DBG("            glDisableVertexAttribArray(%d);", i);
                    glDisableVertexAttribArray(i);
                }
                break;

            case GLASM::VWP:
                GLASM_NEXT(pc, GLint4, value.int4);
                //PSY_LOG_DBG("        glViewport(%d, %d, %d, %d)", value.int4.x, value.int4.y, value.int4.z, value.int4.w);
                glViewport(value.int4.x, value.int4.y, value.int4.z, value.int4.w);
                break;



            case GLASM::JMP:
                GLASM_NEXT(pc, unsigned char*, value.addr);
                //PSY_LOG_DBG("        JMP %p", value.addr);
                /*pc = value.addr;*/
                break;

            default:
                break;
            }
        }
    }
}



void AndroidDisplay::stop()
{
    PSY_LOG_DBG("    Stopping task AndroidDisplay");
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
