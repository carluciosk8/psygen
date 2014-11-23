#pragma once

#include "Engine/TimeSource.hpp"

#include <time.h>

namespace psy {


class AndroidTimeSource : public TimeSource
{
public:
    AndroidTimeSource();
    virtual ~AndroidTimeSource();

    virtual double get_time() const;


private:
    timespec m_start_time;
};


}
