#include "Engine/AndroidApplication.hpp"

#include "Engine/AndroidDisplay.hpp"
#include "Engine/AndroidEventManager.hpp"


namespace psy {



AndroidApplication::AndroidApplication(struct android_app* app)
{
    PSY_LOG_DBG("    Creating new AndroidApplication");

    // Create android subsystems
    //new AndroidEventManager(app);
    //new AndroidDisplay(app);

    m_tasks.push_back( new AndroidEventManager(app) );
    m_tasks.push_back( new AndroidDisplay(app) );
}



AndroidApplication::~AndroidApplication()
{
    PSY_LOG_DBG("    Deleting AndroidApplication");

    // Delete android subsystems.
    for (Task* task : m_tasks)
        delete task;
}



void AndroidApplication::init()
{    Application::init();
    PSY_LOG_DBG("    Start AndroidApplication::init()");

    // nop

    PSY_LOG_DBG("    Finish AndroidApplication::init()");
}



void AndroidApplication::shutdown()
{    Application::shutdown();
    PSY_LOG_DBG("    Start AndroidApplication::shutdown()");

    // nop

    PSY_LOG_DBG("    Finish AndroidApplication::shutdown()");
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void AndroidApplication::run()
{
    PSY_LOG_DBG("    Start AndroidApplication::run()");

    // Wait display to be ready
    while (not m_is_running)
        event_manager_sgt.update();

    Application::run();

    shutdown();

    PSY_LOG_DBG("    Finish AndroidApplication::run()");
}


} // end namespace psy
