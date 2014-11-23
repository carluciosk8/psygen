#pragma once

namespace psy {

class Visitor;

class Visitable
{
public:
    virtual ~Visitable() {}

    virtual void accept(Visitor*) = 0;
};


} // end namespace psy
