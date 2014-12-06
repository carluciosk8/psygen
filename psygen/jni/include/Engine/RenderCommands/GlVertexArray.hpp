#pragma once

#include "Engine/RenderCommand.hpp"

#include <vector>
#include <GLES2/gl2.h>

namespace psy {


class GlVertexArray : public RenderCommand
{
public:
    GlVertexArray(GLenum primitive_type, const std::vector<float>& vertices, const std::vector<int>& format);
    virtual ~GlVertexArray();

    // from RenderCommand
    virtual void execute();


protected:
    GLenum m_primitive_type;
    const std::vector<float>& m_vertices;
    const std::vector<int>& m_format;
    int m_num_vertices;
    int m_stride;
};


} // end namespace psy
