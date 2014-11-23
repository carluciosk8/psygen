#pragma once

namespace psy {


class Display
{
public:
    virtual ~Display() {}

    virtual void init() = 0;
};


}
