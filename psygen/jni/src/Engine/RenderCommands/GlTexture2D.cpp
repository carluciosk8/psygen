#include "Engine/RenderCommands/GlTexture2D.hpp"

//#include "Engine/AndroidDisplay.hpp"

namespace psy {


GlTexture2D::GlTexture2D(int size, int format, int type, void* data)
:
        m_handle(0)
{
    PSY_LOG_DBG("Creating new RenderCommand GlTexture2D");

    // Use tightly packed data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Generate a texture object
    glGenTextures(1, &m_handle);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, m_handle);

    // Load the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, size, size, 0, format, type, data);

    // Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


GlTexture2D::~GlTexture2D()
{
    PSY_LOG_DBG("Deleting RenderCommand GlTexture2D");

    glDeleteTextures(1, &m_handle);
}


void GlTexture2D::execute()
{
    glActiveTexture(m_handle);
}


}
