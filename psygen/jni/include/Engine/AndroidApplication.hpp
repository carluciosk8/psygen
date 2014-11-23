#pragma once

#include <android_native_app_glue.h>

#include "Engine/Application.hpp"

namespace psy {


class AndroidApplication: public Application
{
public:
    AndroidApplication(struct android_app* android_application);
    virtual ~AndroidApplication();

    virtual void run();


private:
    struct android_app* m_android_app;
};


} // end namespace psy
