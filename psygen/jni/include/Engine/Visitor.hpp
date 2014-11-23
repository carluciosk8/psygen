#pragma once

namespace psy {

class Visitable;

class Visitor
{
public:
    virtual ~Visitor() {}

    virtual void visit(Visitable*) = 0;
};


} // end namespace psy
