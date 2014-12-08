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
    log_debug_sgt << "GlClear::execute()" << std::endl;
    glClear(m_bitfield);
}


}
