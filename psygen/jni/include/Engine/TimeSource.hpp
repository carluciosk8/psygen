#pragma once

namespace psy {


class TimeSource
{
public:
    virtual ~TimeSource() {}
    virtual double get_time() const = 0;
};


}
