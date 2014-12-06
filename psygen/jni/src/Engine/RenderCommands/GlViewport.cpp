#include "Engine/RenderCommands/GlViewport.hpp"

#include <GLES2/gl2.h>


namespace psy {


GlViewport::GlViewport(int width, int height)
:
        m_width(width),
        m_height(height)
{}


GlViewport::~GlViewport()
{}


void GlViewport::execute()
{
    glViewport(0, 0, m_width, m_height);
}


}
