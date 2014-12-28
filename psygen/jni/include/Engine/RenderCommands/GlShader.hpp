#pragma once

#include "psygen/RenderCommand.hpp"

#include <string>
#include <GLES2/gl2.h>

namespace psy {


class GlShader : public RenderingResource
{
public:
    GlShader(const char* vsource, const char* fsource);
    virtual ~GlShader();

    // from RenderingResource
    virtual void inflate();
    virtual void shrink();

    inline GLuint get_handler() { return  m_shader; }
    inline GLint  get_uniform_location(const GLchar* name) { return glGetUniformLocation(m_shader, name); }

protected:
    std::string m_vertex_shader_source;
    std::string m_fragment_shader_source;
    GLuint  m_shader;

    GLuint load_shader(const char* source, GLenum type);
};


} // end namespace psy
