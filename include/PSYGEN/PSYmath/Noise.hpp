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
#ifndef __NOISE_H__
#define __NOISE_H__


#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYmath/Vector2.hpp"
#include "PSYGEN/PSYmath/Vector3.hpp"



namespace psy
{

class PSYAPI Noise
{
    public:

        static float noise(vec2 vec);
        static float noise(float x, float y);
        static float noise(vec3 vec);
        static float noise(float x, float y, float z);

    private:

        static float at2(float rx, float ry, float* q);
        static float at3(float rx, float ry, float rz, float* q);
        static void setup(float u, int& b0, int& b1, float& r0, float& r1, float& t);

        static int p[];
        static float g[][3];
		static int BM;
		static int N;
};

#include "Noise.inl"

}

#endif
