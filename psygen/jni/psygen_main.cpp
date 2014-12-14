#include <string>
#include <vector>

#include <glm/gtc/noise.hpp>

#include "Engine/AndroidApplication.hpp"
#include "Engine/AndroidLogger.hpp"
#include "Engine/Clock.hpp"
#include "Engine/AndroidDisplay.hpp"

#include "Engine/RenderCommands/GlClear.hpp"
#include "Engine/RenderCommands/GlClearColor.hpp"
#include "Engine/RenderCommands/GlDisable.hpp"
#include "Engine/RenderCommands/GlShader.hpp"
#include "Engine/RenderCommands/GlTexture2D.hpp"
#include "Engine/RenderCommands/GlVertexArray.hpp"
#include "Engine/RenderCommands/GlViewport.hpp"
#include "Engine/RenderCommands/GlUniform.hpp"



class ExampleTask : public psy::Task
{
    std::string                  m_vshader;
    std::string                  m_fshader;
    std::vector<float>           m_verts;
    std::vector<int>             m_format;
    std::vector<unsigned short>  m_indices;
    psy::RenderProgram           m_render_program;
    unsigned char                m_texture[512][512];

    unsigned char m_main_prg[256];
    float m_time;

public:
    ExampleTask()
    {
        PSY_LOG_DBG("        Creating new task ExampleTask");

        m_vshader =
            "attribute vec4 a_vPosition;                  \n"
            "attribute vec2 a_vTexCoord;                  \n"
            "varying vec2 v_vTexCoord;                    \n"
            "uniform float u_time;                        \n"
            "void main()                                  \n"
            "{                                            \n"
            "    float sa = sin(u_time);                  \n"
            "    float ca = cos(u_time);                  \n"
            "    mat4 rot = mat4(  ca, -sa, 0.0, 0.0,     \n"
            "                      sa,  ca, 0.0, 0.0,     \n"
            "                     0.0, 0.0, 1.0, 0.0,     \n"
            "                     0.0, 0.0, 0.0, 1.0 );   \n"
            "    gl_Position = a_vPosition*rot;           \n"
            "    v_vTexCoord = a_vTexCoord;               \n"
            "}                                            \n";

        m_fshader =
            "precision mediump float;                               \n"
            "varying vec2 v_vTexCoord;                              \n"
            "uniform sampler2D s_texture;                           \n"
            "void main()                                            \n"
            "{                                                      \n"
            "    gl_FragColor = texture2D(s_texture, v_vTexCoord);  \n"
            "}                                                      \n";

        m_verts =
        {
            -100.5f,  100.5f,    0.0f, 1.0f, // 0
            -100.5f, -100.5f,    0.0f, 0.0f, // 1
             100.5f,  100.5f,    1.0f, 1.0f, // 2
             100.5f, -100.5f,    1.0f, 0.0f  // 3
        };

        m_indices = { 0, 1, 2, 2, 1, 3 };

        m_format = { 2 , 2 };

        m_render_program = {};

        m_time = 0;

        for (int y = 0 ; y < 512 ; ++y)
            for(int x = 0 ; x < 512 ; ++x)
                m_texture[y][x] = static_cast<unsigned char>(128.0f * (glm::perlin(glm::vec2(x / 32.0f, y / 32.0f)) + 1.0f));

        psy::application_sgt.add_task(this);
    }

    virtual ~ExampleTask()
    {
        PSY_LOG_DBG("        Deleting task ExampleTask");
    }


    virtual void start()
    {
        PSY_LOG_DBG("        Starting task ExampleTask");

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

        psy::GlShader*             shd = new psy::GlShader(m_vshader.c_str(), m_fshader.c_str());
        psy::GlTexture2D*          tex = new psy::GlTexture2D(512, GL_LUMINANCE, GL_UNSIGNED_BYTE, &m_texture);
        psy::GlVertexBufferObject* vbo = new psy::GlVertexBufferObject(GL_TRIANGLES, m_verts, m_format, m_indices);

        m_verts.clear();
        m_indices.clear();


        // create main program
        pc = m_main_prg;
        GLASM_PUSH(pc, GLASM, GLASM::CLR);
            GLASM_PUSH(pc, GLbitfield, GL_COLOR_BUFFER_BIT);

        GLASM_PUSH(pc, GLASM, GLASM::SHD);
            GLASM_PUSH(pc, GLuint, shd->get_handler());

        GLASM_PUSH(pc, GLASM, GLASM::UF1);
            GLASM_PUSH(pc, GLint, 0);
            GLASM_PUSH(pc, GLfloat*, &m_time);

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

        PSY_LOG_DBG("        Finish ExampleTask::start()");
    }


    virtual void update()
    {
        m_time = psy::clock();
        //m_position.set_value(glm::vec2(200,200));
    }


    virtual void stop()
    {
        PSY_LOG_DBG("        Start ExampleTask::stop()");

        psy::display_sgt.set_active_program(nullptr);
        m_render_program.erase();

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
