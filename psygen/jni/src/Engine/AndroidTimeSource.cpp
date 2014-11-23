#include "Engine/AndroidTimeSource.hpp"


namespace psy {


AndroidTimeSource::AndroidTimeSource()
{
    int err = clock_gettime(CLOCK_MONOTONIC, &m_start_time);
}


AndroidTimeSource::~AndroidTimeSource()
{
}


double AndroidTimeSource::get_time() const
{
    timespec now;
    int err = clock_gettime(CLOCK_MONOTONIC, &now);

    return (now.tv_nsec-m_start_time.tv_nsec)*0.000000001 + (now.tv_sec-m_start_time.tv_sec);
}


}
