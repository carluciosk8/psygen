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
#ifndef __PSYGEN_TRANSFORM_H__
#define __PSYGEN_TRANSFORM_H__

#include "PSYGEN/PSYmath/Vector3.hpp"
#include "PSYGEN/PSYmath/Matrix3.hpp"
#include "PSYGEN/PSYmath/Matrix4.hpp"

namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Transform
{
public:
    Transform();
    Transform(float scale, const mat3& rotate, const vec3& translate);

    void setPos(const vec3&);
    void setPos(float x, float y, float z);
    void setScale(float s);
    void rotateX(float pitch);
    void rotateY(float head);
    void rotateZ(float yaw);
    void rotateYXZ(float head, float pitch, float yaw);
    void rotateZXY(float head, float pitch, float yaw);

    mat3& getRotate();
    const vec3& getTranslate() const;
    float getScale() const;

    void makeGLmodel(mat4&);
    void makeGLview(mat4&);


    void product(const Transform& a, const Transform& b);


private:
    mat3  m_mRotate;
    vec3  m_vTranslate;
    float  m_fScale;


public:
    static const Transform IDENTITY;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#include "PSYGEN/PSYengine/Transform.inl"

#endif //__PSYGEN_TRANSFORM_H__
