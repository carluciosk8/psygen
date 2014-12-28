#include "Engine/RenderCommands/GlTexture2D.hpp"


namespace psy {


GlTexture2D::GlTexture2D(int size, int format, int type, void* data)
:
    m_size(size),
    m_format(format),
    m_type(type),
    m_data(data),
    m_handle(0)
{
    PSY_LOG_DBG("Creating new RenderingResource GlTexture2D");
}


GlTexture2D::~GlTexture2D()
{
    PSY_LOG_DBG("Deleting RenderingResource GlTexture2D");
}


void GlTexture2D::inflate()
{
    PSY_LOG_DBG("Inflating RenderingResource GlTexture2D");

    // Use tightly packed data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Generate a texture object
    glGenTextures(1, &m_handle);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, m_handle);

    // Load the texture
    glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_size, m_size, 0, m_format, m_type, m_data);

    // Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


void GlTexture2D::shrink()
{
    PSY_LOG_DBG("Shrinking RenderingResource GlTexture2D");

    glDeleteTextures(1, &m_handle);
}


}
