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
    for (GLenum state : m_states)
        glEnable(state);
}


}
