#pragma once

#include "Engine/Geometry.hpp"

#include <vector>
#include <GLES2/gl2.h>

class Square : public psy::Geometry
{
public:
    Square();
    virtual ~Square();

    virtual void inflate();
    virtual void shrink();
    virtual int  estimate_memory();
    virtual int  estimate_time();
    virtual void update(float dt);

    virtual void draw();
    virtual void estimate_bound();

protected:
    GLuint  m_shader_object;
    std::vector<GLfloat>  m_vertices;
};
