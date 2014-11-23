#pragma once

#include "Engine/Object.hpp"

namespace psy {


class Attribute
{
public:
    virtual ~Attribute() {}

    virtual void enable() = 0;
    virtual void disable() = 0;
};


} // end namespace psy
