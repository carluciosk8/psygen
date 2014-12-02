#include "Engine/AndroidApplication.hpp"

#include "Engine/AndroidDisplay.hpp"
#include "Engine/AndroidLogger.hpp"


namespace psy {


struct android_app* AndroidApplication::m_app;


AndroidApplication::AndroidApplication(struct android_app* app)
:
    m_poll(nullptr),
    m_events(0)
{
    m_app = app;
    m_app->userData = this;
    m_app->onAppCmd = handle_cmd;

    m_display = new AndroidDisplay(app);
    m_logger  = new AndroidLogger("psygen");
}



AndroidApplication::~AndroidApplication()
{
    delete m_display;
    delete m_logger;
}



void AndroidApplication::init()
{
    sg_display.init();
    square.inflate();
}



void AndroidApplication::run()
{
    m_is_running = true;
    while (m_is_running)
    {
        process_events();

        sg_display.begin_frame();
        square.draw();
        sg_display.end_frame();
    }
}



void AndroidApplication::shutdown()
{
    sg_display.shutdown();
}



void AndroidApplication::handle_cmd(struct android_app* app, int32_t cmd)
{
    switch (cmd)
    {
    // The window is being shown, get it ready.
    case APP_CMD_INIT_WINDOW:
        if (app->window) sg_application.init();
        break;

    // The window is being hidden or closed, clean it up.
    case APP_CMD_TERM_WINDOW:
        sg_application.shutdown();
        break;
    }
}


} // end namespace psy
