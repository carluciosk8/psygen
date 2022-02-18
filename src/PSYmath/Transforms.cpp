/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
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
    *  \ingroup PSYmath
    *
    *//***********************************************************************/
#include "PSYGEN/PSYmath/Transforms.hpp"
#include "PSYGEN/PSYmath/Functions.hpp"


namespace psy {////////////////////////////////////////////////////////////////

void rotateX(mat3& m, float a)
{
    float cos_a = cos(a);
    float sin_a = sin(a);
    m.m[0][0] = 1.0f ; m.m[0][1] = 0.0f  ; m.m[0][2] =  0.0f;
    m.m[1][0] = 0.0f ; m.m[1][1] = cos_a ; m.m[1][2] = -sin_a;
    m.m[2][0] = 0.0f ; m.m[2][1] = sin_a ; m.m[2][2] =  cos_a;
}



void rotateY(mat3& m, float a)
{
    float cos_a = cos(a);
    float sin_a = sin(a);
    m.m[0][0] =  cos_a ; m.m[0][1] = 0.0f ; m.m[0][2] = sin_a;
    m.m[1][0] =  0.0f  ; m.m[1][1] = 1.0f ; m.m[1][2] = 0.0f;
    m.m[2][0] = -sin_a ; m.m[2][1] = 0.0f ; m.m[2][2] = cos_a;
}



void rotateZ(mat3& m, float a)
{
    float cos_a = cos(a);
    float sin_a = sin(a);
    m.m[0][0] = cos_a ; m.m[0][1] = -sin_a ; m.m[0][2] = 0.0f;
    m.m[1][0] = sin_a ; m.m[1][1] =  cos_a ; m.m[1][2] = 0.0f;
    m.m[2][0] = 0.0f  ; m.m[2][1] =  0.0f  ; m.m[2][2] = 1.0f;
}



void rotateYXZ(mat3& m, float y, float p, float r)
{
    float cz = cos(r);
    float cy = cos(y);
    float cx = cos(p);
    float sz = sin(r);
    float sy = sin(y);
    float sx = sin(p);

    m.m[0][0] = cy*cz + sx*sy*sz;  m.m[0][1] = cz*sx*sy - cy*sz;  m.m[0][2] = cx*sy;
    m.m[1][0] = cx*sz;             m.m[1][1] = cx*cz;             m.m[1][2] = -sx;
    m.m[2][0] = cy*sx*sz - cz*sy;  m.m[2][1] = cy*cz*sx + sy*sz;  m.m[2][2] = cx*cy;
}



void rotateAngleAxis(mat3& m, float a, const vec3& v)
{
   float sa = sin(a);
   float ca = cos(a);
   float mca = 1-ca;

   m.m[0][0] = (ca + v.x*v.x*mca);       m.m[0][1] = (v.x*v.y*mca - v.z*sa);   m.m[0][2] = (v.x*v.z*mca + v.y*sa);
   m.m[1][0] = (v.x*v.y*mca + v.z*sa);   m.m[1][1] = (ca + v.y*v.y*mca);       m.m[1][2] = (v.y*v.z*mca - v.x*sa);
   m.m[2][0] = (v.x*v.z*mca - v.y*sa);   m.m[2][1] = (v.y*v.z*mca + v.x*sa);   m.m[2][2] = (ca + v.z*v.z*mca);
}


}//////////////////////////////////////////////////////////////////////////////
