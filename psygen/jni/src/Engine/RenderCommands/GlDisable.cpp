#include "Engine/RenderCommands/GlDisable.hpp"


namespace psy {


GlDisable::GlDisable(const std::vector<GLenum>& states)
:
    m_states(states)
{}


GlDisable::~GlDisable()
{
    m_states.clear();
}


void GlDisable::execute()
{
    for (GLenum state : m_states)
        glDisable(state);
}


}
