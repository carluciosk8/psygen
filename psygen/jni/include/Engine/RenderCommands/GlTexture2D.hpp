#pragma once

#include "Engine/RenderCommand.hpp"

#include <vector>
#include <GLES2/gl2.h>

namespace psy {


class GlTexture2D : public RenderCommand
{
public:
    GlTexture2D(int size, int format, int type, void* data);
    virtual ~GlTexture2D();

    // from RenderCommand
    virtual void execute();

    inline GLuint get_handler() { return  m_handle; }

protected:
    GLuint m_handle;
};


} // end namespace psy
