#pragma once

#include "psygen/RenderCommand.hpp"

#include <vector>
#include <GLES2/gl2.h>

namespace psy {


class GlVertexArray : public RenderingResource
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


class GlVertexBufferObject : public RenderingResource
{
public:
    GlVertexBufferObject(GLenum primitive_type, const std::vector<GLfloat>& vertices, const std::vector<GLubyte>& format, const std::vector<GLushort>& indices);
    virtual ~GlVertexBufferObject();

    // from RenderingResource
    virtual void inflate();
    virtual void shrink();

    inline GLuint  get_handler1() { return  m_handler[0]; }
    inline GLuint  get_handler2() { return  m_handler[1]; }
    inline GLubyte get_num_indices() { return m_indices.size(); }
    inline GLubyte get_stride() { return m_stride; }

protected:
    GLuint   m_handler[2];
    GLenum   m_primitive_type;
    std::vector<GLubyte>  m_format;
    std::vector<GLfloat>  m_vertices;
    std::vector<GLushort> m_indices;
    int m_stride;
};


} // end namespace psy
