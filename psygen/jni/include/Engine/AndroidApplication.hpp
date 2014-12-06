#pragma once

#include "Engine/Application.hpp"

#include <vector>
#include <list>
#include <string>
#include <android_native_app_glue.h>


namespace psy {

class Subsystem;

class AndroidApplication : public Application
{
public:
    AndroidApplication(struct android_app* app);
    virtual ~AndroidApplication();

    // from Application
    virtual void init();
    virtual void run();
    virtual void shutdown();

    inline void update();

private:
    struct android_app* m_app;

    static void handle_cmd(struct android_app* app, int32_t cmd);

    std::list<Subsystem*> m_subsystems_list;
};


inline void AndroidApplication::update()
{
    int  m_events;
    struct android_poll_source* m_poll;

    if ((ALooper_pollAll(0, NULL, &m_events, reinterpret_cast<void**>(&m_poll))) >= 0)
        if (m_poll)
            m_poll->process(m_app, m_poll);

    if (m_app->destroyRequested) m_is_running = false;
}


} // end namespace psy
