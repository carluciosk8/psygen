#pragma once

#include "Engine/RenderCommand.hpp"

#include <GLES2/gl2.h>

namespace psy {


class GlShader : public RenderCommand
{
public:
    GlShader(const char* vsource, const char* fsource);
    virtual ~GlShader();

    // from RenderCommand
    virtual void execute();


protected:
    GLuint  m_shader;

    GLuint load_shader(const char* source, GLenum type);
};


} // end namespace psy
