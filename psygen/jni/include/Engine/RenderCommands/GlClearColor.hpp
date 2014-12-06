#pragma once

#include "Engine/RenderCommand.hpp"

#include <glm/glm.hpp>

namespace psy {


class GlClearColor : public RenderCommand
{
public:
    GlClearColor();
    virtual ~GlClearColor();

    // from RenderCommand
    virtual void execute();


protected:
    glm::fvec4 m_clear_color;
};


} // end namespace psy
