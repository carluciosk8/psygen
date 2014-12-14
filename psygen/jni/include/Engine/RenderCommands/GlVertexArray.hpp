#pragma once

#include "Engine/RenderCommand.hpp"

#include <vector>
#include <GLES2/gl2.h>

namespace psy {


class GlVertexArray : public RenderCommand
{
public:
    GlVertexArray(GLenum primitive_type, const std::vector<float>& vertices, const std::vector<int>& format, const std::vector<unsigned short>& indices);
    virtual ~GlVertexArray();

    // from RenderCommand
    virtual void execute();


protected:
    GLenum m_primitive_type;
    const std::vector<float>& m_vertices;
    const std::vector<int>& m_format;
    const std::vector<unsigned short>& m_indices;
    int m_num_vertices;
    int m_stride;
};


class GlVertexBufferObject : public RenderCommand
{
public:
    GlVertexBufferObject(GLenum primitive_type, const std::vector<float>& vertices, const std::vector<int>& format, const std::vector<unsigned short>& indices);
    virtual ~GlVertexBufferObject();

    // from RenderCommand
    virtual void execute();

    inline GLuint  get_handler1() { return  m_handler[0]; }
    inline GLuint  get_handler2() { return  m_handler[1]; }
    inline GLubyte get_num_indices() { return m_num_indices; }
    inline GLubyte get_stride() { return m_stride; }

protected:
    GLenum   m_primitive_type;
    GLuint   m_handler[2];
    const std::vector<int>& m_format;
    int m_num_indices;
    int m_stride;
};


} // end namespace psy
