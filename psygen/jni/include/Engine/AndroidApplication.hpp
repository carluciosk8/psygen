#pragma once

#include "Engine/Application.hpp"

#include <android_native_app_glue.h>


namespace psy {


class AndroidApplication : public Application
{
public:
    AndroidApplication(struct android_app* app);
    virtual ~AndroidApplication();

    // from Application
    virtual void init();
    virtual void shutdown();
    virtual void run();
};


} // end namespace psy


#define android_application_sgt reinterpret_cast<psy::AndroidApplication&>(Application::get_singleton())
