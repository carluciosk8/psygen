#include <jni.h>

#include "Engine/AndroidApplication.hpp"


void android_main(struct android_app* android_application)
{
    // Make sure glue isn't stripped.
    app_dummy();

    psy::Application* app = new psy::AndroidApplication(android_application);

    app->run();
}
