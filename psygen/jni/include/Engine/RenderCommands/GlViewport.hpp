#pragma once

#include "Engine/RenderCommand.hpp"

namespace psy {


class GlViewport : public RenderCommand
{
public:
    GlViewport(int width, int height);
    virtual ~GlViewport();

    // from RenderCommand
    virtual void execute();


protected:
    int m_width;
    int m_height;
};


} // end namespace psy
