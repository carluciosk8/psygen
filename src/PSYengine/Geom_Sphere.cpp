/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2008 by Carlucio Santos Cordeiro
    email:      carlucio@gmail.com

    This file is part of PSYGEN

    PSYGEN is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with PSYGEN. If not, see <http://www.gnu.org/licenses/>

-------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief ________
    *  \ingroup PSYengine
    *
    *//***********************************************************************/
#include <GL/glew.h>

#include "PSYGEN/PSYengine/Geom_Sphere.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Geom_Sphere, Geometry)
{
    m_sys_memory_use = sizeof(*this);

    bind_parameter2(Parameter::VEC3,  "center", &center, vec3::ZERO);
    bind_parameter2(Parameter::FLOAT, "radius", &radius, 0.0f);
    bind_parameter2(Parameter::INT,   "slices", &slices, 0);
    bind_parameter2(Parameter::INT,   "stacks", &stacks, 0);
}



void Geom_Sphere::amplify(Mutex*)
{
    if (m_eState == SHRINKED)
    {
//         std::cout << "amplify Geom_Sphere: name = \"" << get_name() << "\"" << std::endl;
//         std::cout << "   center = " << center << std::endl;
//         std::cout << "   radius = " << radius << std::endl;
//         std::cout << "   slices = " << slices << std::endl;
//         std::cout << "   stacks = " << stacks << std::endl;

        m_uiGL_Display_List = glGenLists(1);
        m_opGLU_Quadric_Obj = gluNewQuadric();

        gluQuadricNormals(m_opGLU_Quadric_Obj, GLU_SMOOTH);
        gluQuadricTexture(m_opGLU_Quadric_Obj, true);
        glNewList(m_uiGL_Display_List, GL_COMPILE);
        glTranslatef(center.x, center.y, center.z );
        gluSphere(m_opGLU_Quadric_Obj, radius, slices, stacks);
        glEndList();

        m_eState = AMPLIFIED;
    }
}



void Geom_Sphere::shrink(Mutex*)
{
    if (m_eState == AMPLIFIED)
    {
        //std::cout << "shrink Geom_Sphere: name = \"" << get_name() << "\"" << std::endl;
        m_eState = SHRINKED;

        glDeleteLists(m_uiGL_Display_List,1);
        gluDeleteQuadric(m_opGLU_Quadric_Obj);

    }
}



float Geom_Sphere::estimate_mem_usage()
{
    return 0.0f;//slices*stacks;
}



float Geom_Sphere::estimate_time_usage()
{
    return 0.0;
}



void Geom_Sphere::draw()
{
    glCallList(m_uiGL_Display_List);
}


void Geom_Sphere::calc_bound_volume()
{
    local_bound.pos = center;
    local_bound.rad = radius;
}

}//////////////////////////////////////////////////////////////////////////////
