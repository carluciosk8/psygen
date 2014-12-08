#include "Engine/RenderCommands/GlShader.hpp"

#include "Engine/Logger.hpp"

namespace psy {


GlShader::GlShader(const char* vsource, const char* fsource)
{
    m_shader = glCreateProgram();
    if (m_shader == 0)
    {
        log_warning_sgt << "Could not create shader program" << std::endl;
        return;
    }

    GLuint vshader_handle = load_shader(vsource, GL_VERTEX_SHADER);
    GLuint fshader_handle = load_shader(fsource, GL_FRAGMENT_SHADER);
    glAttachShader(m_shader, vshader_handle);
    glAttachShader(m_shader, fshader_handle);
    glLinkProgram(m_shader);

    GLint linked;
    glGetProgramiv(m_shader, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLint length = 0;
        glGetProgramiv(m_shader, GL_INFO_LOG_LENGTH, &length);

        if (length > 1)
        {
            char log[length];
            glGetProgramInfoLog(m_shader, length, NULL, log);
            log_warning_sgt << "Error linking shader program:" << std::endl;
            log_warning_sgt << std::string(log) << std::endl;
        }

        glDeleteProgram(m_shader);
    }
}


GlShader::~GlShader()
{}


void GlShader::execute()
{
    log_debug_sgt << "GlShader::execute( " << m_shader << " )" << std::endl;

    glUseProgram(m_shader);
}


GLuint GlShader::load_shader(const char* source, GLenum type)
{
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);
    if (shader != 0)
    {
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            if (length > 1)
            {
                char log[length];
                glGetShaderInfoLog(shader, length, NULL, log);
                log_warning_sgt << "Error compiling shader:" << std::endl;
                log_warning_sgt << std::string(log) << std::endl;
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}


}
