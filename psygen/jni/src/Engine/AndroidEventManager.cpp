#include "Engine/AndroidEventManager.hpp"

#include <vector>
#include <string>

#include "Engine/Logger.hpp"
#include "Engine/Application.hpp"


namespace psy {



AndroidEventManager::AndroidEventManager(struct android_app* app)
:
    m_app(app),
    m_poll(nullptr),
    m_events(0)
{
    PSY_LOG_DBG("    Creating new task AndroidEventManager");

    m_app->onAppCmd = handle_cmd;
}



AndroidEventManager::~AndroidEventManager()
{
    PSY_LOG_DBG("    Deleting task AndroidEventManager");
}



void AndroidEventManager::start()
{
    PSY_LOG_DBG("    Starting task AndroidEventManager");
}


void AndroidEventManager::stop()
{
    PSY_LOG_DBG("    Stopping task AndroidEventManager");
}


void AndroidEventManager::update()
{
    if ((ALooper_pollAll(0, NULL, &m_events, reinterpret_cast<void**>(&m_poll))) >= 0)
        if (m_poll)
            m_poll->process(m_app, m_poll);

    if (m_app->destroyRequested)
        PSY_LOG_DBG("---------------------------------- m_app->destroyRequested ----------------------------------");

}



void AndroidEventManager::handle_cmd(struct android_app* app, int32_t cmd)
{
    static std::vector<std::string> android_commands =
    {
        "APP_CMD_INPUT_CHANGED",
        "APP_CMD_INIT_WINDOW",
        "APP_CMD_TERM_WINDOW",
        "APP_CMD_WINDOW_RESIZED",
        "APP_CMD_WINDOW_REDRAW_NEEDED",
        "APP_CMD_CONTENT_RECT_CHANGED",
        "APP_CMD_GAINED_FOCUS",
        "APP_CMD_LOST_FOCUS",
        "APP_CMD_CONFIG_CHANGED",
        "APP_CMD_LOW_MEMORY",
        "APP_CMD_START",
        "APP_CMD_RESUME",
        "APP_CMD_SAVE_STATE",
        "APP_CMD_PAUSE",
        "APP_CMD_STOP",
        "APP_CMD_DESTROY"
    };

    PSY_LOG_DBG("    cmd: %s", android_commands[cmd].c_str());
    switch (cmd)
    {
    // Window is ready to be used
    case APP_CMD_INIT_WINDOW:
        if (app->window)
            application_sgt.init();
        else
            PSY_LOG_ERR("    cmd: app->window is nullptr");
        break;

    // Window needs to be shutdown
    case APP_CMD_TERM_WINDOW:
        application_sgt.stop();
        break;
    }
}


} // end namespace psy
