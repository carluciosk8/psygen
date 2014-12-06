#include "Engine/RenderCommands/GlClear.hpp"


namespace psy {


GlClear::GlClear(GLbitfield bitfield)
:
    m_bitfield(bitfield)
{}


GlClear::~GlClear()
{}


void GlClear::execute()
{
    glClear(m_bitfield);
}


}
