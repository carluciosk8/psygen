#include "Engine/RenderCommands/GlVertexArray.hpp"

#include <numeric>

#include "Engine/AndroidDisplay.hpp"

namespace psy {


GlVertexArray::GlVertexArray(GLenum primitive_type, const std::vector<float>& vertices, const std::vector<int>& format, const std::vector<unsigned short>& indices)
:
    m_primitive_type(primitive_type),
    m_vertices(vertices),
    m_format(format),
    m_indices(indices),
    m_num_vertices(0),
    m_stride(0)
{
    PSY_LOG_DBG("Creating new RenderCommand GlVertexArray");

    for (int attribute_size : m_format)
        m_stride += attribute_size;

    m_num_vertices = m_vertices.size() / m_stride;

    m_stride *= sizeof(GLfloat);
}


GlVertexArray::~GlVertexArray()
{
    PSY_LOG_DBG("Deleting RenderCommand GlVertexArray");
}


void GlVertexArray::execute()
{
    for (int i = 0 , p = 0 ; i < m_format.size() ; p += m_format[i] , ++i)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, m_format[i], GL_FLOAT, GL_FALSE, m_stride, &m_vertices[p]);
    }

    //glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, &m_indices[0]);

    for (int i = 0 ; i < m_format.size() ; ++i)
        glDisableVertexAttribArray(i);
}





GlVertexBufferObject::GlVertexBufferObject(GLenum primitive_type, const std::vector<GLfloat>& vertices, const std::vector<GLubyte>& format, const std::vector<GLushort>& indices)
:
    m_handler {0, 0},
    m_primitive_type(primitive_type),
    m_format(format),
    m_vertices(vertices),
    m_indices(indices),
    m_stride(0)
{
    PSY_LOG_DBG("Creating new RenderCommand GlVertexBufferObject");
}



GlVertexBufferObject::~GlVertexBufferObject()
{
    PSY_LOG_DBG("Deleting RenderCommand GlVertexBufferObject");
}



void GlVertexBufferObject::inflate()
{

    for (int attribute_size : m_format)
        m_stride += attribute_size;
    m_stride *= sizeof(GLfloat);

    glGenBuffers(2, m_handler);

    glBindBuffer(GL_ARRAY_BUFFER, m_handler[0]);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handler[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLushort), &m_indices[0], GL_STATIC_DRAW);
}


void GlVertexBufferObject::shrink()
{
}






}
