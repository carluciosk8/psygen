#include "Engine/RenderCommands/GlEnable.hpp"


namespace psy {


GlEnable::GlEnable(const std::vector<GLenum>& states)
:
    m_states(states)
{}


GlEnable::~GlEnable()
{
    m_states.clear();
}


void GlEnable::execute()
{
    log_debug_sgt << "GlEnable::execute()" << std::endl;

    for (GLenum state : m_states)
        glEnable(state);
}


}
