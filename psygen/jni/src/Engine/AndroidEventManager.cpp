#include "Engine/AndroidEventManager.hpp"

#include "Engine/Application.hpp"


namespace psy {



AndroidEventManager::AndroidEventManager(struct android_app* app)
:
    m_app(app),
    m_poll(nullptr),
    m_events(0)
{
    m_app->onAppCmd = handle_cmd;
}



AndroidEventManager::~AndroidEventManager()
{
}



void AndroidEventManager::update()
{
    if ((ALooper_pollAll(0, NULL, &m_events, reinterpret_cast<void**>(&m_poll))) >= 0)
        if (m_poll)
            m_poll->process(m_app, m_poll);

    if (m_app->destroyRequested)
    {
        //m_is_running = false;
    }
}



void AndroidEventManager::handle_cmd(struct android_app* app, int32_t cmd)
{
    switch (cmd)
    {
    case APP_CMD_INIT_WINDOW:
        if (app->window) application_sgt.init();
        break;

    case APP_CMD_TERM_WINDOW:
        application_sgt.shutdown();
        break;
    }
}


} // end namespace psy
