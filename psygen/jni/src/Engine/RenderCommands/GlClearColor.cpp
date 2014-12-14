#include "Engine/RenderCommands/GlClearColor.hpp"

#include <GLES2/gl2.h>


namespace psy {


GlClearColor::GlClearColor()
:
    m_clear_color(0,0,0,1)
{
    PSY_LOG_DBG("Creating new RenderCommand GlClearColor");
}


GlClearColor::~GlClearColor()
{
    PSY_LOG_DBG("Deleting RenderCommand GlClearColor");
}


void GlClearColor::execute()
{
    //log_debug_sgt << "GlClearColor::execute()" << std::endl;

    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
}


}
