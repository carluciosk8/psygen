#include "Engine/Application.hpp"

namespace psy {


void Application::run()
{
    while (m_is_running)
    {
        m_clock.FrameStep();
    }
}


}
