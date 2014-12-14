#include "Engine/RenderCommands/GlClear.hpp"

#include "Engine/AndroidDisplay.hpp"


namespace psy {


GlClear::GlClear(GLbitfield bitfield)
:
    m_bitfield(bitfield)
{
    PSY_LOG_DBG("Creating new RenderCommand GlClear");
}


GlClear::~GlClear()
{
    PSY_LOG_DBG("Deleting RenderCommand GlClear");
}


void GlClear::execute()
{
    glClear(m_bitfield);
}


}
