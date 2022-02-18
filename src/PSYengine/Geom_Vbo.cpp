/**************************************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
    email:      carlucio@gmail.com

    This file is part of PSYGEN

    PSYGEN is free software: you can redistribute it and/or modify it under the terms of the GNU
    Lesser General Public License as published by the Free Software Foundation, either version 3
    of the License, or (at your option) any later version.

    PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
    even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with PSYGEN.
    If not, see <http://www.gnu.org/licenses/>

---------------------------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief  __________
    *  \ingroup  PSYengine
    *
    *//*******************************************************************************************/

#include <GL/glew.h>

#include "PSYGEN/PSYengine/Geom_Vbo.hpp"

namespace psy /////////////////////////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Geom_Vbo, Geometry)
{
    m_sys_memory_use = sizeof(*this);

    //empty
}



void Geom_Vbo::amplify(Mutex*)
{
    //if (m_eState == SHRINKED)
    //{
//         std::cout << "amplify Geom_Vbo: name = \"" << get_name() << "\"" << std::endl;

        //empty

        m_eState = AMPLIFIED;
    //}
}



void Geom_Vbo::shrink(Mutex*)
{
    //if (m_eState == AMPLIFIED)
    //{
//         std::cout << "shrink Geom_Vbo: name = \"" << get_name() << "\"" << std::endl;

        //empty

        m_eState = SHRINKED;
    //}
}



float Geom_Vbo::estimate_mem_usage()
{
    return 0.0f;
}



float Geom_Vbo::estimate_time_usage()
{
    return 0.0f;
}



void Geom_Vbo::calc_bound_volume()
{
    local_bound.pos = vec3::ZERO;
    local_bound.rad = 0;
}



void Geom_Vbo::draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBOVerts);
    glVertexPointer(3, GL_FLOAT, 0, NULL);    // Set The Vertex Pointer To The Vertex Buffer

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBONormals);
    glNormalPointer(GL_FLOAT, 0, NULL);    // Set The Normal Pointer To The Normal Buffer

//     glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBOColors);
//     glColorPointer(3, GL_FLOAT, 0, NULL);    // Set The Color Pointer To The Color Buffer

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBOTxCrds);
    glTexCoordPointer(3, GL_FLOAT, 0, NULL);    // Set The TexCoord Pointer To The TexCoord Buffer

    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_uiVBOIndxs);
    glDrawElements(m_ePrimType, m_uiNumIndxs, GL_UNSIGNED_INT, NULL);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
//    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}



void Geom_Vbo::create(float* fpVertices, float* fpNormals, /*float* fpColors,*/
                      float* fpTexCoords, unsigned int* uipIndexes,
                      unsigned int uiNumVerts, unsigned int uiNumIndxs, GLenum ePrimType)
{
    m_ePrimType = ePrimType;
    m_uiNumVerts = uiNumVerts;
    m_uiNumIndxs = uiNumIndxs;

    glGenBuffersARB(1, &m_uiVBOVerts);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBOVerts);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, uiNumVerts*sizeof(float), fpVertices, GL_STATIC_DRAW_ARB);

    glGenBuffersARB(1, &m_uiVBONormals);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBONormals);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, uiNumVerts*sizeof(float), fpNormals, GL_STATIC_DRAW_ARB);

//     glGenBuffersARB(1, &m_uiVBOColors);
//     glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBOColors);
//     glBufferDataARB(GL_ARRAY_BUFFER_ARB, uiNumVerts*sizeof(float), fpColors, GL_STATIC_DRAW_ARB);

    glGenBuffersARB(1, &m_uiVBOTxCrds);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_uiVBOTxCrds);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, uiNumVerts*sizeof(float), fpTexCoords, GL_STATIC_DRAW_ARB);

    glGenBuffersARB(1, &m_uiVBOIndxs);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_uiVBOIndxs);
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, uiNumIndxs*sizeof(unsigned int), uipIndexes, GL_STATIC_DRAW_ARB);
}



void Geom_Vbo::destroy()
{
    glDeleteBuffersARB(1, &m_uiVBOVerts);
    glDeleteBuffersARB(1, &m_uiVBONormals);
//    glDeleteBuffersARB(1, &m_uiVBOColors);
    glDeleteBuffersARB(1, &m_uiVBOTxCrds);
    glDeleteBuffersARB(1, &m_uiVBOIndxs);

    m_uiNumVerts = 0;
    m_uiNumIndxs = 0;
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
