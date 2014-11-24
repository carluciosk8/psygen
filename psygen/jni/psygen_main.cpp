#include <jni.h>

#include "Engine/AndroidApplication.hpp"
#include "Engine/AndroidDisplay.hpp"
#include "Engine/Application.hpp"
#include "Square.hpp"


void android_main(struct android_app* android_application)
{
    psy::Platform* m_platform = new psy::AndroidPlatform(android_application);
    psy::Display*  m_display  = new psy::AndroidDisplay(android_application);
    psy::Geometry* m_geometry = new Square();

    m_platform->init();
    m_display->init();

    // main loop
    while (m_platform->is_running())
    {
        m_geometry->draw();
    }

    m_platform->shutdown();

}
