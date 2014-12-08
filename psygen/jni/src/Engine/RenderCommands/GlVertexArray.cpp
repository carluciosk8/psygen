#include "Engine/RenderCommands/GlVertexArray.hpp"

#include <numeric>

namespace psy {


GlVertexArray::GlVertexArray(GLenum primitive_type, const std::vector<float>& vertices, const std::vector<int>& format)
:
    m_primitive_type(primitive_type),
    m_vertices(vertices),
    m_format(format),
    m_num_vertices(0),
    m_stride(0)
{
    for (int attribute_size : m_format)
        m_stride += attribute_size;

    m_num_vertices = m_vertices.size() / m_stride;

    m_stride *= sizeof(GLfloat);
}


GlVertexArray::~GlVertexArray()
{}


void GlVertexArray::execute()
{
    log_debug_sgt << "GlVertexArray::execute( ";
    for (float f : m_format) log_debug_sgt << f << " , ";
    log_debug_sgt << " )" << std::endl;

    for (int i = 0 , p = 0 ; i < m_format.size() ; p += m_format[i] , ++i)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, m_format[i], GL_FLOAT, GL_FALSE, m_stride, &m_vertices[p]);
    }

    glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);

    for (int i = 0 ; i < m_format.size() ; ++i)
        glDisableVertexAttribArray(i);
}


}
