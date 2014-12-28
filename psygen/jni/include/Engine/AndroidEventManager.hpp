#pragma once

#include "psygen/EventManager.hpp"

#include <android_native_app_glue.h>

namespace psy {

class AndroidEventManager : public EventManager
{
public:
    AndroidEventManager(struct android_app* app);
    virtual ~AndroidEventManager();

    // from Task
    virtual void start();
    virtual void update();
    virtual void stop();

private:
    struct android_app* m_app;
    struct android_poll_source* m_poll;
    int m_events;

    static void handle_cmd(struct android_app* app, int32_t cmd);
};

} // end namespace psy


#define android_event_manager_sgt reinterpret_cast<psy::EventManager&>(Application::get_singleton())
