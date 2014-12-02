#include "Square.hpp"

#include <EGL/egl.h>
#include <GLES2/gl2ext.h>

#include "Engine/Logger.hpp"
#include "Engine/Display.hpp"


namespace psy {


GLuint LoadShader(const char *shaderSrc, GLenum type)
{
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);
    if (shader != 0)
    {
        // Load the shader source
        glShaderSource(shader, 1, &shaderSrc, NULL);

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
}


Square::Square():
    Geometry("Square"),
    m_shader_object(0),
    m_vertices
    ({
        -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,

         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f
    })
{}


Square::~Square()
{}


void Square::inflate()
{
    if ( !psy::sg_display.is_initialized() )
        return;

    psy::sg_logger(psy::Logger::DEBUG, "Square::inflate()");

    char vShaderStr[] =
            "attribute vec4 a_vPosition;   \n"
            "attribute vec4 a_vColor;      \n"
            "varying vec4 v_vColor;        \n"
            "void main()                   \n"
            "{                             \n"
            "   gl_Position = a_vPosition; \n"
            "   v_vColor = a_vColor;       \n"
            "}                             \n";

    char fShaderStr[] =
            "precision mediump float;                   \n"
            "varying vec4 v_vColor;                     \n"
            "void main()                                \n"
            "{                                          \n"
            "  gl_FragColor = v_vColor;                 \n"
            "}                                          \n";

    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader   = psy::LoadShader(vShaderStr, GL_VERTEX_SHADER);
    fragmentShader = psy::LoadShader(fShaderStr, GL_FRAGMENT_SHADER);

    // Create the program object
    m_shader_object = glCreateProgram();
    if (m_shader_object == 0)
    {
        return;
    }

    // Attach shaders to program
    glAttachShader(m_shader_object, vertexShader);
    glAttachShader(m_shader_object, fragmentShader);

    // Bind a_vPosition to attribute 0 and a_vColor to 1
    glBindAttribLocation(m_shader_object, 0, "a_vPosition");
    glBindAttribLocation(m_shader_object, 1, "a_vColor");

    // Link the program
    glLinkProgram(m_shader_object);

    // Check the link status
    glGetProgramiv(m_shader_object, GL_LINK_STATUS, &linked);
    if(!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(m_shader_object, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen > 1)
        {
            char* infoLog = new char[infoLen];
            glGetProgramInfoLog(m_shader_object, infoLen, NULL, infoLog);
            //LOGW("Error linking program:\n%s\n", infoLog);

            delete[] infoLog;
        }

        glDeleteProgram(m_shader_object);
    }
}


void Square::draw()
{
    if ( !psy::sg_display.is_initialized() )
        return;


    glUseProgram(m_shader_object);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, &m_vertices[0]);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, &m_vertices[3]);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}


void Square::update(float dt)  {}
void Square::shrink()          {}
void Square::estimate_bound()  {}
int  Square::estimate_memory() { return 0; }
int  Square::estimate_time()   { return 0; }
