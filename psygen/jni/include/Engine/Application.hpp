#pragma once

#include "Engine/Singleton.hpp"

namespace psy {

class Display;
class Logger;

class Application : public Singleton<Application>
{
public:
    virtual ~Application() {}

    virtual void init() = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;

    inline bool is_running() const { return m_is_running; }


protected:
    bool m_is_running;

    Display* m_display;
    Logger*  m_logger;
};

#define sg_application      Application::GetSingleton()
#define sg_application_ptr  Application::GetSingletonPtr()


/*
class AndroidEventProcessor : public FrameCode
{
public:
    AndroidEventProcessor(struct android_app* android_application);
    virtual ~AndroidEventProcessor();

    virtual void init();
    virtual void execute();
    virtual void shutdown();


private:
    struct android_app* m_android_app;

    static int32_t handle_input(struct android_app* app, AInputEvent* event);
};
*/

} // end namespace psy
