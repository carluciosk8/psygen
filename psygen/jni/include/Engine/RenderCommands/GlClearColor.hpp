#pragma once

#include "Engine/RenderCommand.hpp"

#include <glm/glm.hpp>

namespace psy {


class GlClearColor : public RenderCommand
{
public:
    GlClearColor();
    inline GlClearColor(const glm::fvec4& clear_color)      : m_clear_color(clear_color) {}
    inline GlClearColor(float r, float g, float b, float a) : m_clear_color(r,g,b,a)     {}
    virtual ~GlClearColor();

    // from RenderCommand
    virtual void execute();


protected:
    glm::fvec4 m_clear_color;
};


} // end namespace psy
