#include "Engine/RenderCommands/GlViewport.hpp"

#include <GLES2/gl2.h>


namespace psy {


GlViewport::GlViewport(int width, int height)
:
        m_width(width),
        m_height(height)
{
    PSY_LOG_DBG("Creating new RenderCommand GlViewport( %d , %d )", m_width, m_height);
}


GlViewport::~GlViewport()
{
    PSY_LOG_DBG("Deleting RenderCommand GlViewport");
}


void GlViewport::execute()
{
    //log_debug_sgt << "GlViewport::execute( " << m_width << " , " << m_height << " )" << std::endl;

    glViewport(0, 0, m_width, m_height);
}


}
