#include "Engine/RenderCommands/GlDisable.hpp"


namespace psy {


GlDisable::GlDisable(const std::vector<GLenum>& states)
:
    m_states(states)
{
    PSY_LOG_DBG("Creating new RenderCommand GlDisable");
}


GlDisable::~GlDisable()
{
    PSY_LOG_DBG("Deleting RenderCommand GlDisable");

    m_states.clear();
}


void GlDisable::execute()
{
    //log_debug_sgt << "GlDisable::execute()" << std::endl;

    for (GLenum state : m_states)
        glDisable(state);
}


}
