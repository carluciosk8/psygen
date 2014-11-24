#pragma once

#include "Engine/Clock.hpp"

namespace psy {


class Application
{
public:
    virtual ~Application() {}

    virtual void run();


protected:
    bool  m_is_running;
    ClockManager m_clock;
};


} // end namespace psy
