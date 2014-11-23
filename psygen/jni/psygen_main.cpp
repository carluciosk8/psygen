#include <jni.h>

#include "Engine/AndroidApplication.hpp"


void android_main(struct android_app* android_application)
{
    psy::Application* app = new psy::AndroidApplication(android_application);
    app->run();
}
