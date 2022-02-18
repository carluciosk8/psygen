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
    *  \brief  Bound volume encapsulation
    *  \ingroup PSYengine
    *
    *//*******************************************************************************************/
#ifndef __PSYGEN_BOUND_H__
#define __PSYGEN_BOUND_H__

#include <GL/gl.h>

#include "PSYGEN/PSYengine/Transform.hpp"

namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{


class Bound
{
public:
    vec3  pos;
    float rad;

    Bound(){};
    Bound(const vec3& p, float r) : pos(p), rad(r) {}

    inline void merge(const Bound& s0)
    {
        merge(*this,s0);
    }

    bool test_collision(const Bound& that)
    {
        vec3 relPos = this->pos - that.pos;
        float dist = relPos.x * relPos.x + relPos.y * relPos.y + relPos.z * relPos.z;
        float minDist = this->rad + that.rad;
        return (dist <= minDist * minDist);
    }

    void merge(const Bound& s0, const Bound& s1)
    {
        vec3  centerDiff = s1.pos - s0.pos;
        float radiusDiff = s1.rad - s0.rad;
        float radiusDiffSqr = radiusDiff*radiusDiff;
        float Lsqr = length_sqr(centerDiff);

        if (radiusDiffSqr >= Lsqr)
        {
            if (radiusDiff >= 0.0f)
            {
                *this = s1;
                return;
            }
            else
            {
                *this = s0;
                return;
            }
        }
        else
        {
            float L = sqrt(Lsqr);
            float t = (L + s1.rad - s0.rad)/(2.0f*L);
            this->pos = s0.pos + t*centerDiff;
            this->rad = (L + s1.rad + s0.rad)/2.0f;
            return;
        }
    }


    void draw()
    {
        glBegin(GL_LINE_LOOP);
        glColor3f(1,0,0);
        for (float s=0, a=0, da=6.28/12; s<12; s++, a+=da)
            glVertex3f(pos.x + rad*cos(a), pos.y + rad*sin(a), pos.z);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glColor3f(0,1,0);
        for (float s=0, a=0, da=6.28/12; s<12; s++, a+=da)
            glVertex3f(pos.x, pos.y + rad*sin(a), pos.z + rad*cos(a));
        glEnd();
        glBegin(GL_LINE_LOOP);
        glColor3f(0,0,1);
        for (float s=0, a=0, da=6.28/12; s<12; s++, a+=da)
            glVertex3f(pos.x + rad*sin(a), pos.y, pos.z + rad*cos(a));
        glEnd();
        glColor3f(1,1,1);
    }

    void transform_by(Transform& world)
    {
        vec3 new_center;
        new_center.x = pos.x*world.getRotate()[0][0] + pos.y*world.getRotate()[0][1] + pos.z*world.getRotate()[0][2] + world.getTranslate().x;
        new_center.y = pos.x*world.getRotate()[1][0] + pos.y*world.getRotate()[1][1] + pos.z*world.getRotate()[1][2] + world.getTranslate().y;
        new_center.z = pos.x*world.getRotate()[2][0] + pos.y*world.getRotate()[2][1] + pos.z*world.getRotate()[2][2] + world.getTranslate().z;
        pos = new_center;
    }

//private:
//    static
};


}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_BOUND_H__
