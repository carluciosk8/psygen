#include "Engine/AndroidApplication.hpp"

#include "Engine/AndroidDisplay.hpp"
#include "Engine/AndroidEventManager.hpp"
#include "Engine/AndroidLogger.hpp"

#include "Engine/RenderCommands/GlClear.hpp"
#include "Engine/RenderCommands/GlShader.hpp"
#include "Engine/RenderCommands/GlVertexArray.hpp"


namespace psy {



AndroidApplication::AndroidApplication(struct android_app* app)
{
    new AndroidLoggerDebug("psygen");
    new AndroidLoggerInfo("psygen");
    new AndroidLoggerWarning("psygen");
    new AndroidLoggerError("psygen");

    m_tasks.push_back( new AndroidEventManager(app) );
    m_tasks.push_back( new AndroidDisplay(app) );
}



AndroidApplication::~AndroidApplication()
{
    for (Task* task : m_tasks) delete task;

    delete &log_debug_sgt;
    delete &log_info_sgt;
    delete &log_warning_sgt;
    delete &log_error_sgt;
}



void AndroidApplication::init()
{
    Application::init();
    log_debug_sgt << "AndroidApplication::init()" << std::endl;
}



void AndroidApplication::shutdown()
{
    Application::shutdown();
    log_debug_sgt << "AndroidApplication::shutdown()" << std::endl;
}


} // end namespace psy
