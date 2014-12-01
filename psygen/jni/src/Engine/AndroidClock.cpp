#include "Engine/AndroidClock.hpp"

namespace psy {


timespec AndroidClock::m_start_time;


AndroidClock::AndroidClock()
{
    int err = clock_gettime(CLOCK_MONOTONIC, &m_start_time);
    time_fptr = android_get_time;
}


AndroidClock::~AndroidClock()
{}


double AndroidClock::android_get_time()
{
    timespec now;
    int err = clock_gettime(CLOCK_MONOTONIC, &now);

    return (now.tv_nsec-m_start_time.tv_nsec)*0.000000001 + (now.tv_sec-m_start_time.tv_sec);
}


}
