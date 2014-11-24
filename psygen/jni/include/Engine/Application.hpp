#pragma once

#include "Engine/FrameCode.hpp"

#include <android_native_app_glue.h>

namespace psy {

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

    static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);
};


} // end namespace psy
