#include "Engine/AndroidApplication.hpp"

#include "Engine/AndroidDisplay.hpp"
#include "Engine/AndroidLogger.hpp"

#include "Engine/RenderCommands/GlClear.hpp"
#include "Engine/RenderCommands/GlShader.hpp"
#include "Engine/RenderCommands/GlVertexArray.hpp"


namespace psy {



AndroidApplication::AndroidApplication(struct android_app* app)
:
    m_app(app)
{
    new AndroidLogger("psygen");
    new AndroidDisplay(app);

    m_app->userData = this;
    m_app->onAppCmd = handle_cmd;
}



AndroidApplication::~AndroidApplication()
{
    delete sg_android_display_ptr;
    delete sg_logger_ptr;
}



void AndroidApplication::init()
{
    sg_logger(Logger::DEBUG, "AndroidApplication::init()");

    sg_android_display_ptr->init();
}



void AndroidApplication::run()
{
    sg_logger(Logger::DEBUG, "AndroidApplication::run()");

    m_is_running = true;
    while (m_is_running)
    {
        update();

        sg_android_display_ptr->update();
    }
}



void AndroidApplication::shutdown()
{
    sg_logger(Logger::DEBUG, "AndroidApplication::shutdown()");

    sg_android_display.shutdown();
}



void AndroidApplication::handle_cmd(struct android_app* app, int32_t cmd)
{
    switch (cmd)
    {
    case APP_CMD_INIT_WINDOW:
        if (app->window) sg_application.init();
        break;

    case APP_CMD_TERM_WINDOW:
        sg_application.shutdown();
        break;
    }
}


} // end namespace psy
