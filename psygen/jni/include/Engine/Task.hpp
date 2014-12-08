#pragma once

namespace psy {

class Task
{
public:
    virtual ~Task() {}

    virtual void start() = 0;
    virtual void update() = 0;
    virtual void stop() = 0;
};

} // end namespace psy
