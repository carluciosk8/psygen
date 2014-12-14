#include <time.h>

namespace psy {

timespec __android_start_timespec;
int __android__start_err = clock_gettime(CLOCK_MONOTONIC, &__android_start_timespec);

double __android_clock()
{
    timespec now;
    int err = clock_gettime(CLOCK_MONOTONIC, &now);

    return (now.tv_nsec-__android_start_timespec.tv_nsec)*0.000000001 + (now.tv_sec-__android_start_timespec.tv_sec);
}

double (*clock)() = __android_clock;

}
