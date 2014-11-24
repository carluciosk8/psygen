#pragma once

#include "Engine/Clock.hpp"

#include <time.h>

namespace psy {


class AndroidClock : public Clock
{
public:
    AndroidClock();
    virtual ~AndroidClock();


protected:
    static timespec m_start_time;

    static double android_get_time();
};


}
