#pragma once

#include "Engine/Visitor.hpp"


namespace psy
{


class Renderer : public Visitor
{
public:
    virtual ~Renderer();
    Renderer();

    virtual void visit(Visitable*);
};


} // end namespace psy
