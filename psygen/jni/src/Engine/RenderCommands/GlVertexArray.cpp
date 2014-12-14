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





GlVertexBufferObject::GlVertexBufferObject(GLenum primitive_type, const std::vector<float>& vertices, const std::vector<int>& format, const std::vector<unsigned short>& indices)
:
    m_primitive_type(primitive_type),
    m_format(format),
    //m_num_vertices(0),
    m_stride(0)
{
    PSY_LOG_DBG("Creating new RenderCommand GlVertexBufferObject");

    for (int attribute_size : m_format)
        m_stride += attribute_size;
    m_stride *= sizeof(GLfloat);

    //m_num_vertices = vertices.size() / m_stride;
    m_num_indices = indices.size();

    glGenBuffers(2, m_handler);

    glBindBuffer(GL_ARRAY_BUFFER, m_handler[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handler[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_num_indices * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);
}



GlVertexBufferObject::~GlVertexBufferObject()
{
    PSY_LOG_DBG("Deleting RenderCommand GlVertexBufferObject");
}



void GlVertexBufferObject::execute()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handler[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handler[1]);

    for (int p = 0 , i = 0 ; i < m_format.size() ; p += m_format[i]*sizeof(GLfloat), ++i)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, m_format[i], GL_FLOAT, GL_FALSE, m_stride, (const void*)p);
    }

    glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_SHORT, 0);

    for (int i = 0 ; i < m_format.size() ; ++i)
        glDisableVertexAttribArray(i);
}






}
