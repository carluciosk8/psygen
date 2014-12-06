#pragma once

#include "Engine/RenderCommand.hpp"

#include <GLES2/gl2.h>

namespace psy {


class GlClear : public RenderCommand
{
public:
    GlClear(GLbitfield bitfield);
    virtual ~GlClear();

    // from RenderCommand
    virtual void execute();


protected:
    GLbitfield m_bitfield;
};


} // end namespace psy
