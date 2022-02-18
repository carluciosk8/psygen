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
    *  \ingroup PSYengine
    *
    *//***********************************************************************/
inline float Noise::noise(float x, float y)
{
    return noise( vec2(x, y) );
}



inline float Noise::noise(float x, float y, float z)
{
    return noise( vec3(x, y, z) );
}



inline float Noise::at2(float rx, float ry, float* q)
{
    return  ( rx * q[0] + ry * q[1] );
}


inline float Noise::at3(float rx, float ry, float rz, float* q)
{
    return  ( rx * q[0] + ry * q[1] + rz * q[2] );
}


inline void Noise::setup(float u, int& b0, int& b1, float& r0, float& r1, float& t)
{
    t = u + N;
    b0 = ((int)t) & BM;
    b1 = (b0+1) & BM;
    r0 = t - (int)t;
    r1 = r0 - 1.0f;
}
