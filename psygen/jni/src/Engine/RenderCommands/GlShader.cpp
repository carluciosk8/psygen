#include "Engine/RenderCommands/GlShader.hpp"

#include <glm/glm.hpp>
#include <vector>

#include "Engine/Logger.hpp"
#include "Engine/Clock.hpp"

#include "Engine/RenderCommands/GlUniform.hpp"

namespace psy {


GlShader::GlShader(const char* vsource, const char* fsource)
{
    PSY_LOG_DBG("Creating new RenderCommand GlShader");

    m_shader = glCreateProgram();
    if (m_shader == 0)
    {
        PSY_LOG_WRN("Could not create shader program");
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
            glGetProgramInfoLog(m_shader, length, nullptr, log);
            PSY_LOG_WRN("Error linking shader program:\n%s", log);
        }

        glDeleteProgram(m_shader);
    }
}


GlShader::~GlShader()
{
    PSY_LOG_DBG("Deleting RenderCommand GlShader");
}


void GlShader::execute()
{
    glUseProgram(m_shader);
}


GLuint GlShader::load_shader(const char* source, GLenum type)
{
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);
    if (shader != 0)
    {
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            if (length > 1)
            {
                char log[length];
                glGetShaderInfoLog(shader, length, nullptr, log);
                PSY_LOG_WRN("Error compiling shader:\n%s", log);
                //LOGW(log);
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}


}
