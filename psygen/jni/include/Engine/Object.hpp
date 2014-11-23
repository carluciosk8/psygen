#pragma once

namespace psy {


class Object
{
public:
    virtual ~Object() {}

    virtual void inflate() = 0;
    virtual void shrink() = 0;
    virtual int  estimate_memory() = 0;
    virtual int  estimate_time() = 0;
    virtual void update(float dt) = 0;
};


} // end namespace psy
