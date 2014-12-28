#pragma once

#include "psygen/RenderCommand.hpp"

#include <vector>
#include <GLES2/gl2.h>

namespace psy {


class GlTexture2D : public RenderingResource
{
public:
    GlTexture2D(int size, int format, int type, void* data);
    virtual ~GlTexture2D();

    // from RenderingResource
    virtual void inflate();
    virtual void shrink();

    inline GLuint get_handler() { return  m_handle; }

protected:
    int    m_size;
    int    m_format;
    int    m_type;
    void*  m_data;

    GLuint m_handle;
};


} // end namespace psy
