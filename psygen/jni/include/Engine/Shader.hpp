#pragma once

#include "Engine/Object.hpp"
#include "Engine/Effect.hpp"

namespace psy {

class GLES2Shader: public Object , public Effect
{
public:
    inline GLES2Shader(const std::string& name) : Object(name) {}
    virtual ~GLES2Shader();

    // from Object
    virtual void inflate();
    virtual void shrink();
    virtual int  estimate_memory();
    virtual int  estimate_time();

    // from Effect
    virtual void enable();
    virtual void disable();

    GLuint load_shader(const char *shaderSrc, GLenum type);

protected:
    GLuint  m_shader_object;
    std::string m_vertex_shader_source;
    std::string m_fragment_shader_source;
    GLuint m_vertex_shader_handle;
    GLuint m_fragment_shader_handle;
    std::vector<std::string> m_attributes_names;
};

} // end namespace psy
