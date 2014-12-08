#include <string>
#include <vector>

#include "Engine/AndroidApplication.hpp"
#include "Engine/Logger.hpp"
#include "Engine/AndroidDisplay.hpp"

#include "Engine/RenderCommands/GlClear.hpp"
#include "Engine/RenderCommands/GlClearColor.hpp"
#include "Engine/RenderCommands/GlDisable.hpp"
#include "Engine/RenderCommands/GlShader.hpp"
#include "Engine/RenderCommands/GlVertexArray.hpp"
#include "Engine/RenderCommands/GlViewport.hpp"


class ExampleApplication : public psy::AndroidApplication
{
public:
    ExampleApplication(struct android_app* app)
    :
        AndroidApplication(app)
    {
        m_vshader =
            "attribute vec4 a_vPosition;                \n"
            "attribute vec4 a_vColor;                   \n"
            "varying vec4 v_vColor;                     \n"
            "void main()                                \n"
            "{                                          \n"
            "    gl_Position = a_vPosition;             \n"
            "    v_vColor = a_vColor;                   \n"
            "}                                          \n";

        m_fshader =
            "precision mediump float;                   \n"
            "varying vec4 v_vColor;                     \n"
            "void main()                                \n"
            "{                                          \n"
            "    gl_FragColor = v_vColor;               \n"
            "}                                          \n";

        m_verts =
        {
            -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
             0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,

             0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f
        };

        m_format = { 3 , 4 };
}


    virtual void init()
    {
        AndroidApplication::init();
        psy::log_debug_sgt << "ExampleApplication::init()" << std::endl;

        psy::GlDisable    cmd1( {GL_CULL_FACE, GL_DEPTH_TEST} );
        psy::GlClearColor cmd2;
        psy::GlViewport   cmd3(psy::display_sgt.get_width(), psy::display_sgt.get_height());

        cmd1.execute();
        cmd2.execute();
        cmd3.execute();

        m_render_program.add_command(new psy::GlClear(GL_COLOR_BUFFER_BIT));
        m_render_program.add_command(new psy::GlShader(m_vshader.c_str(), m_fshader.c_str()));
        m_render_program.add_command(new psy::GlVertexArray(GL_TRIANGLES, m_verts, m_format));
        psy::display_sgt.set_active_program(&m_render_program);
    }


    virtual void shutdown()
    {
        AndroidApplication::shutdown();
        psy::log_debug_sgt << "ExampleApplication::shutdown()" << std::endl;
    }


private:
    psy::RenderProgram m_render_program;
    std::string        m_vshader;
    std::string        m_fshader;
    std::vector<float> m_verts;
    std::vector<int>   m_format;
};



void android_main(struct android_app* android_application)
{
    app_dummy();
    ExampleApplication example_application(android_application);
    example_application.run();
}
