#include "Engine/AndroidApplication.hpp"

#include <android_native_app_glue.h>

namespace psy {


AndroidApplication::AndroidApplication(struct android_app* android_application)
:
    m_android_app(android_application)
{
    app_dummy();
    m_android_app->userData = this;
}


AndroidApplication::~AndroidApplication()
{
    // nop
}


void AndroidApplication::run()
{
    // loop waiting for stuff to do.
    for (;;)
    {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* poll_source;
        while ( (ident = ALooper_pollAll(0, NULL, &events, reinterpret_cast<void**>(&poll_source))) >= 0)
        {
            // Process this event.
            if (poll_source) poll_source->process(m_android_app, poll_source);

            // Check if we are exiting.
            if (m_android_app->destroyRequested) return;
        }
    }
}


} // end namespace psy
