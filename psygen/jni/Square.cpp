#include "Square.hpp"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


Square::Square()
{}


Square::~Square()
{}


void Square::inflate()
{}


void Square::shrink()
{}


int Square::estimate_memory()
{
    return 0;
}


int Square::estimate_time()
{
    return 0;
}


void Square::update(float dt)
{}


void Square::draw()
{
    const float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat vertices[] = {-0.5,  0.5, 0, color[0], color[1], color[2], color[3],
                          -0.5, -0.5, 0, color[0], color[1], color[2], color[3],
                           0.5,  0.5, 0, color[0], color[1], color[2], color[3],
                           0.5,  0.5, 0, color[0], color[1], color[2], color[3],
                          -0.5, -0.5, 0, color[0], color[1], color[2], color[3],
                           0.5, -0.5, 0, color[0], color[1], color[2], color[3]};

    glViewport(0, 0, 1920, 1080);

    // Just fill the screen with a color.
    glClearColor(0.95f, 0.95f, 0.95f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    //glUseProgram(engine->programObject);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, vertices);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, &vertices[3]);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //eglSwapBuffers(engine->display, engine->surface);
}
