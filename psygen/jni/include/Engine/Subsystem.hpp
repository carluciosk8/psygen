#pragma once

namespace psy {

class Subsystem
{
public:
    virtual ~Subsystem() {}

    virtual void init() = 0;
    virtual void shutdown() = 0;
};

} // end namespace psy
