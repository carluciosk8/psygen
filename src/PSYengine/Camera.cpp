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
    *  \brief
    *  \ingroup $GROUP$
    *
    *//***********************************************************************/
#include <stdexcept>
#include <GL/glu.h>

#include "PSYGEN/PSYengine/Camera.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Camera, Node)
{
    m_sys_memory_use = sizeof(*this);
    //bound.rad = 1.01f;
}



void Camera::amplify(Mutex* mutex)
{
    //if (m_eState == SHRINKED)
    //{
        //std::cout << "amplify Camera: name = \"" << get_name() << "\"" << std::endl;

        //empty
        if (mutex) mutex->lock();
        m_eState = AMPLIFIED;
        if (mutex) mutex->unlock();
    //}
}



void Camera::shrink(Mutex* mutex)
{
    //if (m_eState == AMPLIFIED)
    //{
        //std::cout << "shrink Camera: name = \"" << get_name() << "\"" << std::endl;

        //empty

        if (mutex) mutex->lock();
        m_eState = SHRINKED;
        if (mutex) mutex->unlock();
    //}
}



float Camera::estimate_mem_usage()
{
    return 0.0f;
}



float Camera::estimate_time_usage()
{
    return 0.0f;
}



void Camera::insert_child(Node* node)
{
    throw std::runtime_error("trying to insert child on camera node");
}



void Camera::remove_child(Node*)
{
    throw std::runtime_error("trying to remove child on camera node");
}


bool Camera::update_bound()
{
    world_bound.pos = world.getTranslate();
    return false;
}


void Camera::accept(Visitor*)
{
    /// nao sei o q fazer aqui ainda!!!
}



void Camera::set_perspective(float fFoV, float fAspect, float fNear, float fFar)
{
    m_fFieldOfView = fFoV;
    m_fAspect = fAspect;
    m_fNear = fNear;
    m_fFar = fFar;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_fFieldOfView, m_fAspect, m_fNear, m_fFar*1.5f);
    glGetFloatv(GL_PROJECTION_MATRIX, gl_proj);
    glMatrixMode(GL_MODELVIEW);
    proj = gl_proj;

    //world_bound.rad = m_fNear + 0.0001;
}



void Camera::update_frustum()
{
    //float   proj[16];
    //float   view[16];
    float   clip[16];
    float   t;

    /* Get the current PROJECTION matrix from OpenGL */
    //glGetFloatv(GL_PROJECTION_MATRIX, proj);

    /* Get the current MODELVIEW matrix from OpenGL */
    //glGetFloatv(GL_MODELVIEW_MATRIX, view);
    world.makeGLview(gl_view);
    view = gl_view;

    /* Combine the two matrices (multiply projection by modelview) */
    clip[ 0] = view[ 0] * proj[ 0] + view[ 1] * proj[ 4] + view[ 2] * proj[ 8] + view[ 3] * proj[12];
    clip[ 1] = view[ 0] * proj[ 1] + view[ 1] * proj[ 5] + view[ 2] * proj[ 9] + view[ 3] * proj[13];
    clip[ 2] = view[ 0] * proj[ 2] + view[ 1] * proj[ 6] + view[ 2] * proj[10] + view[ 3] * proj[14];
    clip[ 3] = view[ 0] * proj[ 3] + view[ 1] * proj[ 7] + view[ 2] * proj[11] + view[ 3] * proj[15];

    clip[ 4] = view[ 4] * proj[ 0] + view[ 5] * proj[ 4] + view[ 6] * proj[ 8] + view[ 7] * proj[12];
    clip[ 5] = view[ 4] * proj[ 1] + view[ 5] * proj[ 5] + view[ 6] * proj[ 9] + view[ 7] * proj[13];
    clip[ 6] = view[ 4] * proj[ 2] + view[ 5] * proj[ 6] + view[ 6] * proj[10] + view[ 7] * proj[14];
    clip[ 7] = view[ 4] * proj[ 3] + view[ 5] * proj[ 7] + view[ 6] * proj[11] + view[ 7] * proj[15];

    clip[ 8] = view[ 8] * proj[ 0] + view[ 9] * proj[ 4] + view[10] * proj[ 8] + view[11] * proj[12];
    clip[ 9] = view[ 8] * proj[ 1] + view[ 9] * proj[ 5] + view[10] * proj[ 9] + view[11] * proj[13];
    clip[10] = view[ 8] * proj[ 2] + view[ 9] * proj[ 6] + view[10] * proj[10] + view[11] * proj[14];
    clip[11] = view[ 8] * proj[ 3] + view[ 9] * proj[ 7] + view[10] * proj[11] + view[11] * proj[15];

    clip[12] = view[12] * proj[ 0] + view[13] * proj[ 4] + view[14] * proj[ 8] + view[15] * proj[12];
    clip[13] = view[12] * proj[ 1] + view[13] * proj[ 5] + view[14] * proj[ 9] + view[15] * proj[13];
    clip[14] = view[12] * proj[ 2] + view[13] * proj[ 6] + view[14] * proj[10] + view[15] * proj[14];
    clip[15] = view[12] * proj[ 3] + view[13] * proj[ 7] + view[14] * proj[11] + view[15] * proj[15];

    /* Extract the numbers for the RIGHT plane */
    frustum[0][0] = clip[ 3] - clip[ 0];
    frustum[0][1] = clip[ 7] - clip[ 4];
    frustum[0][2] = clip[11] - clip[ 8];
    frustum[0][3] = clip[15] - clip[12];

    /* Normalize the result */
    t = sqrt(frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2]);
    frustum[0][0] /= t;
    frustum[0][1] /= t;
    frustum[0][2] /= t;
    frustum[0][3] /= t;

    /* Extract the numbers for the LEFT plane */
    frustum[1][0] = clip[ 3] + clip[ 0];
    frustum[1][1] = clip[ 7] + clip[ 4];
    frustum[1][2] = clip[11] + clip[ 8];
    frustum[1][3] = clip[15] + clip[12];

    /* Normalize the result */
    t = sqrt(frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2]);
    frustum[1][0] /= t;
    frustum[1][1] /= t;
    frustum[1][2] /= t;
    frustum[1][3] /= t;

    /* Extract the BOTTOM plane */
    frustum[2][0] = clip[ 3] + clip[ 1];
    frustum[2][1] = clip[ 7] + clip[ 5];
    frustum[2][2] = clip[11] + clip[ 9];
    frustum[2][3] = clip[15] + clip[13];

    /* Normalize the result */
    t = sqrt(frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2]);
    frustum[2][0] /= t;
    frustum[2][1] /= t;
    frustum[2][2] /= t;
    frustum[2][3] /= t;

    /* Extract the TOP plane */
    frustum[3][0] = clip[ 3] - clip[ 1];
    frustum[3][1] = clip[ 7] - clip[ 5];
    frustum[3][2] = clip[11] - clip[ 9];
    frustum[3][3] = clip[15] - clip[13];

    /* Normalize the result */
    t = sqrt(frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2]);
    frustum[3][0] /= t;
    frustum[3][1] /= t;
    frustum[3][2] /= t;
    frustum[3][3] /= t;

    /* Extract the FAR plane */
    frustum[4][0] = clip[ 3] - clip[ 2];
    frustum[4][1] = clip[ 7] - clip[ 6];
    frustum[4][2] = clip[11] - clip[10];
    frustum[4][3] = clip[15] - clip[14];

    /* Normalize the result */
    t = sqrt(frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2]);
    frustum[4][0] /= t;
    frustum[4][1] /= t;
    frustum[4][2] /= t;
    frustum[4][3] /= t;

    /* Extract the NEAR plane */
    frustum[5][0] = clip[ 3] + clip[ 2];
    frustum[5][1] = clip[ 7] + clip[ 6];
    frustum[5][2] = clip[11] + clip[10];
    frustum[5][3] = clip[15] + clip[14];

    /* Normalize the result */
    t = sqrt(frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2]);
    frustum[5][0] /= t;
    frustum[5][1] /= t;
    frustum[5][2] /= t;
    frustum[5][3] /= t;
}



// bool Camera::test_frustum_visibility(Node* node)
// {
//     for (int p = 0; p < 6; p++)
//         if ( frustum[p][0] * (node->world.getTranslate().x + node->bound.pos.x ) +
//              frustum[p][1] * (node->world.getTranslate().y + node->bound.pos.y ) +
//              frustum[p][2] * (node->world.getTranslate().z + node->bound.pos.z ) +
//              frustum[p][3] <= -node->bound.rad )
//         return false;
//     return true;
// }



bool Camera::bound_is_visible(const Bound& bound)
{
    for (int p = 0; p < 6; p++)
        if ( frustum[p][0] * bound.pos.x +
             frustum[p][1] * bound.pos.y +
             frustum[p][2] * bound.pos.z +
             frustum[p][3] <= -bound.rad )
        return false;
    return true;
}


bool Camera::bound_is_nearby(const Bound& bound)
{
    proximity.pos = world.getTranslate();
    proximity.rad = m_fFar*1.5f;
    return proximity.test_collision(bound);
}


}//////////////////////////////////////////////////////////////////////////////
