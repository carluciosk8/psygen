#pragma once


namespace psy {

class Effect
{
public:
    virtual ~Effect() {}

    virtual void enable()  = 0;
    virtual void disable() = 0;
};


} // end namespace psy
