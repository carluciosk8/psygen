
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

#include "PSYGEN/PSYengine/Transform.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////



Transform::Transform()
/*        :
        m_mRotate(mat3::IDENTITY),
        m_vTranslate(vec3::ZERO),
        m_fScale(1.0f)*/
{
    /* empty */
}



Transform::Transform(float s, const mat3& r, const vec3& t)
        :
        m_mRotate(r),
        m_vTranslate(t),
        m_fScale(s)
{
    /* empty */
}



void Transform::product(const Transform& a, const Transform& b)
{
    m_mRotate.mul(a.m_mRotate, b.m_mRotate);
    m_vTranslate.mul(a.m_mRotate, b.m_vTranslate);
    m_vTranslate *= a.m_fScale;
    m_vTranslate += a.m_vTranslate;
    m_fScale = a.m_fScale *  b.m_fScale;
}



void Transform::makeGLmodel(mat4& M)
{
    M[0][0] = m_fScale*m_mRotate.m[0][0];
    M[0][1] = m_fScale*m_mRotate.m[1][0];
    M[0][2] = m_fScale*m_mRotate.m[2][0];
    M[0][3] = 0;

    M[1][0] = m_fScale*m_mRotate.m[0][1];
    M[1][1] = m_fScale*m_mRotate.m[1][1];
    M[1][2] = m_fScale*m_mRotate.m[2][1];
    M[1][3] = 0;

    M[2][0] = m_fScale*m_mRotate.m[0][2];
    M[2][1] = m_fScale*m_mRotate.m[1][2];
    M[2][2] = m_fScale*m_mRotate.m[2][2];
    M[2][3] = 0;

    M[3][0] = m_vTranslate.x;
    M[3][1] = m_vTranslate.y;
    M[3][2] = m_vTranslate.z;
    M[3][3] = 1;
}



void Transform::makeGLview(mat4& M)
{
    M.m[0][0] = m_mRotate.m[0][0];
    M.m[1][0] = m_mRotate.m[1][0];
    M.m[2][0] = m_mRotate.m[2][0];
    M.m[0][3] = 0;

    M.m[0][1] = m_mRotate.m[0][1];
    M.m[1][1] = m_mRotate.m[1][1];
    M.m[2][1] = m_mRotate.m[2][1];
    M.m[1][3] = 0;

    M.m[0][2] = m_mRotate.m[0][2];
    M.m[1][2] = m_mRotate.m[1][2];
    M.m[2][2] = m_mRotate.m[2][2];
    M.m[2][3] = 0;

    M.m[3][0] = -m_mRotate[0][0]*m_vTranslate.x -m_mRotate[1][0]*m_vTranslate.y -m_mRotate[2][0]*m_vTranslate.z;
    M.m[3][1] = -m_mRotate[0][1]*m_vTranslate.x -m_mRotate[1][1]*m_vTranslate.y -m_mRotate[2][1]*m_vTranslate.z;
    M.m[3][2] = -m_mRotate[0][2]*m_vTranslate.x -m_mRotate[1][2]*m_vTranslate.y -m_mRotate[2][2]*m_vTranslate.z;
    M.m[3][3] = 1;
}



void Transform::rotateX(float pitch)
{
    float c = cos(pitch);
    float s = sin(pitch);
    m_mRotate[0][0] = 1  ;  m_mRotate[0][1] = 0  ;  m_mRotate[0][2] =  0;
    m_mRotate[1][0] = 0  ;  m_mRotate[1][1] = c  ;  m_mRotate[1][2] = -s;
    m_mRotate[2][0] = 0  ;  m_mRotate[2][1] = s  ;  m_mRotate[2][2] =  c;
}



void Transform::rotateY(float head)
{
    float c = cos(head);
    float s = sin(head);
    m_mRotate[0][0] =  c ; m_mRotate[0][1] = 0 ; m_mRotate[0][2] = s;
    m_mRotate[1][0] =  0 ; m_mRotate[1][1] = 1 ; m_mRotate[1][2] = 0;
    m_mRotate[2][0] = -s ; m_mRotate[2][1] = 0 ; m_mRotate[2][2] = c;
}



void Transform::rotateZ(float yaw)
{
    float c = cos(yaw);
    float s = sin(yaw);
    m_mRotate[0][0] = c ; m_mRotate[0][1] = -s ; m_mRotate[0][2] = 0;
    m_mRotate[1][0] = s ; m_mRotate[1][1] =  c ; m_mRotate[1][2] = 0;
    m_mRotate[2][0] = 0 ; m_mRotate[2][1] =  0 ; m_mRotate[2][2] = 1;
}



void Transform::rotateYXZ(float head, float pitch, float yaw)
{
    float cz = cos(yaw);
    float cy = cos(head);
    float cx = cos(pitch);
    float sz = sin(yaw);
    float sy = sin(head);
    float sx = sin(pitch);

    m_mRotate[0][0] = cy*cz + sx*sy*sz;  m_mRotate[0][1] = cz*sx*sy - cy*sz;  m_mRotate[0][2] = cx*sy;
    m_mRotate[1][0] = cx*sz;             m_mRotate[1][1] = cx*cz;             m_mRotate[1][2] = -sx;
    m_mRotate[2][0] = cy*sx*sz - cz*sy;  m_mRotate[2][1] = cy*cz*sx + sy*sz;  m_mRotate[2][2] = cx*cy;
}




void Transform::rotateZXY(float head, float pitch, float yaw)
{
    float cz = cos(yaw);
    float cy = cos(head);
    float cx = cos(pitch);
    float sz = sin(yaw);
    float sy = sin(head);
    float sx = sin(pitch);

    m_mRotate[0][0] = cy*cz - sx*sy*sz;  m_mRotate[0][1] = -cx*sz;            m_mRotate[0][2] = cz*sy + cy*sx*sz;
    m_mRotate[1][0] = cz*sx*sy + cy*sz;  m_mRotate[1][1] = cx*cz;             m_mRotate[1][2] = -cy*cz*sx + sy*sz;
    m_mRotate[2][0] = -cx*sy;            m_mRotate[2][1] = sx;                m_mRotate[2][2] = cx*cy;
}


const Transform Transform::IDENTITY(1.0f, mat3(1,0,0, 0,1,0, 0,0,1), vec3(0,0,0));

}//////////////////////////////////////////////////////////////////////////////////////////////////
