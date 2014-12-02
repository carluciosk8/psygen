#include "Engine/Shader.hpp"

#include <EGL/egl.h>
#include <GLES2/gl2ext.h>

#include "Engine/Logger.hpp"
#include "Engine/Display.hpp"

namespace psy
{

GLES2Shader::~GLES2Shader()
{
    // TODO Auto-generated destructor stub
}


void GLES2Shader::inflate()
{
    if ( !psy::sg_display.is_initialized() )
        return;

    GLint linked;

    // Load the vertex/fragment shaders
    m_vertex_shader_handle = load_shader(m_vertex_shader_source.c_str(), GL_VERTEX_SHADER);
    m_fragment_shader_handle = load_shader(m_fragment_shader_source.c_str(), GL_FRAGMENT_SHADER);

    // Create the program object
    m_shader_object = glCreateProgram();
    if (m_shader_object == 0)
    {
        sg_logger(Logger::WARNING, "Could not create shader program");
        return;
    }

    // Attach shaders to program
    glAttachShader(m_shader_object, m_vertex_shader_handle);
    glAttachShader(m_shader_object, m_fragment_shader_handle);

    // Bind attributes
    for (int i = 0 ; i < m_attributes_names.size() ; ++i)
        glBindAttribLocation(m_shader_object, i, m_attributes_names[i].c_str());

    // Link the program
    glLinkProgram(m_shader_object);

    // Check the link status
    glGetProgramiv(m_shader_object, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLint info_len = 0;
        glGetProgramiv(m_shader_object, GL_INFO_LOG_LENGTH, &info_len);

        if (info_len > 1)
        {
            char* info_log = new char[info_len];
            glGetProgramInfoLog(m_shader_object, info_len, NULL, info_log);
            sg_logger(Logger::WARNING, "Error linking shader program:\n" + info_log);

            delete[] info_log;
        }

        glDeleteProgram(m_shader_object);
    }
}


GLuint GLES2Shader::load_shader(const char* source, GLenum type)
{
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);
    if (shader != 0)
    {
        // Load the shader source
        glShaderSource(shader, 1, &source, NULL);

        // Compile the shader
        glCompileShader(shader);
        // Check the compile status
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 1)
            {
                char* infoLog = new char[infoLen];
                glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
                //LOGW("Error compiling shader:\n%s\n", infoLog);
                delete[] infoLog;
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

} /* namespace psy */
