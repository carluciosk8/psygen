#pragma once

namespace psy {


class FrameCode
{
public:
    virtual ~FrameCode() {}

    virtual void init() = 0;
    virtual void execute() = 0;
    virtual void shutdown() = 0;
};


}
