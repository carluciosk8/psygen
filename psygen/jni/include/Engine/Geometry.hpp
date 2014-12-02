#pragma once

#include "Engine/Object.hpp"

namespace psy {


class Geometry : public Object
{
public:
    virtual ~Geometry() {}

    virtual void draw() = 0;
    virtual void estimate_bound() = 0;


protected:
    inline Geometry(const std::string& name) : Object(name) {}
};


} // end namespace psy
