#pragma once

#include "Engine/Application.hpp"

#include <android_native_app_glue.h>

#include "Square.hpp"

namespace psy {

class AndroidApplication : public Application
{
public:
    AndroidApplication(struct android_app* app);
    virtual ~AndroidApplication();

    // from Application
    virtual void init();
    virtual void run();
    virtual void shutdown();

    inline void process_events();

private:
    static struct android_app* m_app;
    static void handle_cmd(struct android_app* app, int32_t cmd);

    int  m_events;
    struct android_poll_source* m_poll;


    Square square;
};


inline void AndroidApplication::process_events()
{
    while ((ALooper_pollAll(0, NULL, &m_events, reinterpret_cast<void**>(&m_poll))) >= 0)
        if (m_poll) m_poll->process(m_app, m_poll);

    if (m_app->destroyRequested) m_is_running = false;
}


/*
class AndroidPlatform: public Platform
{
public:
    AndroidPlatform(struct android_app* android_application);
    virtual ~AndroidPlatform();

    virtual void init();
    virtual void shutdown();


private:
    struct android_app* m_android_app;

    static void    handle_cmd(struct android_app* app, int32_t cmd);
};
*/

} // end namespace psy
