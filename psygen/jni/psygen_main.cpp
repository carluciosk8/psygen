#include <string>
#include <vector>

#include <glm/gtc/noise.hpp>

#include "Engine/AndroidApplication.hpp"
#include "Engine/AndroidLogger.hpp"
#include "psygen/Clock.hpp"
#include "Engine/AndroidDisplay.hpp"

#include "Engine/RenderCommands/GlShader.hpp"
#include "Engine/RenderCommands/GlTexture2D.hpp"
#include "Engine/RenderCommands/GlVertexArray.hpp"



class ExampleTask : public psy::Task
{
    psy::GlShader*             shd;
    psy::GlTexture2D*          tex;
    psy::GlVertexBufferObject* vbo;

    unsigned char m_texture[512][512];
    unsigned char m_main_prg[256];
    float m_time;
    float m_viewport[2];

public:
    ExampleTask()
    {
        PSY_LOG_DBG("        Creating new task ExampleTask");

        m_time = 0;

        shd = new psy::GlShader
        (
                "attribute vec4 a_vPosition;                  \n"
                "attribute vec2 a_vTexCoord;                  \n"
                "varying vec2 v_vTexCoord;                    \n"
                "uniform float u_time;                        \n"
                "uniform vec2  u_vp;                          \n"
                "void main()                                  \n"
                "{                                            \n"
                "    float sa = sin(u_time);                  \n"
                "    float ca = cos(u_time);                  \n"
                "    mat4 prj = mat4( 2.0/u_vp.x, 0.0,        0.0, -1.0,     \n"
                "                     0.0,        2.0/u_vp.y, 0.0, -1.0,     \n"
                "                     0.0,        0.0,        1.0,  1.0,     \n"
                "                     0.0,        0.0,        0.0,  1.0 );   \n"
                "    mat4 rot = mat4(  ca, -sa, 0.0, u_vp.x/4.0,     \n"
                "                      sa,  ca, 0.0, u_vp.y/4.0,     \n"
                "                     0.0, 0.0, 1.0, 0.0,     \n"
                "                     0.0, 0.0, 0.0, 1.0 );   \n"
                "    gl_Position = a_vPosition*rot*prj;       \n"
                "    v_vTexCoord = a_vTexCoord;               \n"
                "}                                            \n"
            ,
                "precision mediump float;                               \n"
                "varying vec2 v_vTexCoord;                              \n"
                "uniform sampler2D s_texture;                           \n"
                "void main()                                            \n"
                "{                                                      \n"
                "    gl_FragColor = texture2D(s_texture, v_vTexCoord);  \n"
                "}                                                      \n"
        );

        for (int y = 0 ; y < 512 ; ++y)
            for(int x = 0 ; x < 512 ; ++x)
                m_texture[y][x] = static_cast<unsigned char>(128.0f * (glm::perlin(glm::vec2(x / 32.0f, y / 32.0f)) + 1.0f));
        tex = new psy::GlTexture2D(512, GL_LUMINANCE, GL_UNSIGNED_BYTE, &m_texture);

        vbo = new psy::GlVertexBufferObject(GL_TRIANGLES,
                {
                    -500.5f,  500.5f,    0.0f, 1.0f, // 0
                    -500.5f, -500.5f,    0.0f, 0.0f, // 1
                     500.5f,  500.5f,    1.0f, 1.0f, // 2
                     500.5f, -500.5f,    1.0f, 0.0f  // 3
                }
            ,
                { 2 , 2 }
            ,
                {
                    0, 1, 2,
                    2, 1, 3
                }
        );

        psy::application_sgt.add_task(this);
    }

    virtual ~ExampleTask()
    {
        PSY_LOG_DBG("        Deleting task ExampleTask");
    }


    virtual void start()
    {
        PSY_LOG_DBG("        Starting task ExampleTask");

        shd->inflate();
        tex->inflate();
        vbo->inflate();

        m_viewport[0] = psy::display_sgt.get_width();
        m_viewport[1] = psy::display_sgt.get_height();

        // create and run setup program
        unsigned char start_prg[256];
        unsigned char* pc = start_prg;
        GLASM_PUSH(pc, GLASM, GLASM::DIS);
            GLASM_PUSH(pc, GLenum, GL_CULL_FACE);

        GLASM_PUSH(pc, GLASM, GLASM::DIS);
            GLASM_PUSH(pc, GLenum, GL_DEPTH_TEST);

        GLASM_PUSH(pc, GLASM, GLASM::CCL);
            GLASM_PUSH(pc, GLfloat, 0.0f);
            GLASM_PUSH(pc, GLfloat, 0.0f);
            GLASM_PUSH(pc, GLfloat, 0.0f);
            GLASM_PUSH(pc, GLfloat, 1.0f);

        GLASM_PUSH(pc, GLASM, GLASM::VWP);
            GLASM_PUSH(pc, GLint, 0);
            GLASM_PUSH(pc, GLint, 0);
            GLASM_PUSH(pc, GLint, psy::display_sgt.get_width());
            GLASM_PUSH(pc, GLint, psy::display_sgt.get_height());

        GLASM_PUSH(pc, GLASM, GLASM::END);

        psy::display_sgt.render(start_prg);


        // create main program
        pc = m_main_prg;
        GLASM_PUSH(pc, GLASM, GLASM::CLR);
            GLASM_PUSH(pc, GLbitfield, GL_COLOR_BUFFER_BIT);

        GLASM_PUSH(pc, GLASM, GLASM::SHD);
            GLASM_PUSH(pc, GLuint, shd->get_handler());

        GLASM_PUSH(pc, GLASM, GLASM::UF1);
            GLASM_PUSH(pc, GLint, shd->get_uniform_location("u_time"));
            GLASM_PUSH(pc, GLfloat*, &m_time);

        GLASM_PUSH(pc, GLASM, GLASM::UF2);
            GLASM_PUSH(pc, GLint, shd->get_uniform_location("u_vp"));
            GLASM_PUSH(pc, GLfloat*, m_viewport);

        GLASM_PUSH(pc, GLASM, GLASM::TEX);
            GLASM_PUSH(pc, GLuint, tex->get_handler());

        GLASM_PUSH(pc, GLASM, GLASM::VBO);
            GLASM_PUSH(pc, GLenum, GL_TRIANGLES);
            GLASM_PUSH(pc, GLuint, vbo->get_handler1());
            GLASM_PUSH(pc, GLuint, vbo->get_handler2());
            GLASM_PUSH(pc, GLint, vbo->get_num_indices());
            GLASM_PUSH(pc, GLubyte, vbo->get_stride());
            GLASM_PUSH(pc, GLubyte, 2);
                GLASM_PUSH(pc, GLubyte, 2);
                GLASM_PUSH(pc, GLubyte, 2);

        GLASM_PUSH(pc, GLASM, GLASM::END);

        psy::display_sgt.set_program(m_main_prg);
    }


    virtual void update()
    {
        m_time = psy::clock();
    }


    virtual void stop()
    {
        PSY_LOG_DBG("        ExampleTask::stop()");
    }
};



void android_main(struct android_app* android_application)
{
    PSY_LOG_DBG("Starting android_main");

    app_dummy();
    psy::AndroidApplication example_application(android_application);
    ExampleTask example_task;

    example_application.run();

    PSY_LOG_DBG("Finishing android_main");
}
