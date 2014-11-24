#include "Engine/Application.hpp"

#include <android_native_app_glue.h>


namespace psy {


AndroidEventProcessor::AndroidEventProcessor(struct android_app* android_application)
:
    m_android_app(android_application)
{
    android_application->onInputEvent = engine_handle_input;
}



AndroidEventProcessor::~AndroidEventProcessor()
{}



void AndroidEventProcessor::init()
{}



void AndroidEventProcessor::execute()
{
    int events;
    struct android_poll_source* source;

    while ( ALooper_pollAll(0, NULL, &events, reinterpret_cast<void**>(&source)) >= 0)
    {
        // Process this event.
        if (source != NULL)
        {
            source->process(m_android_app, source);
        }

        // Check if we are exiting.
        if (m_android_app->destroyRequested != 0)
        {
            // exit application
        }
    }
}


void AndroidEventProcessor::shutdown()
{}



int32_t AndroidEventProcessor::engine_handle_input(struct android_app* app, AInputEvent* event)
{
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
    {
        int32_t ret = 0;

        int32_t action = AMotionEvent_getAction(event);
        if (action == AMOTION_EVENT_ACTION_DOWN)
        {
            ret = 1;
        }
        else if (action == AMOTION_EVENT_ACTION_UP)
        {
            ret = 1;
        }

        if (ret)
        {
        }
        return ret;
    }
    return 0;
}



}
