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
#ifndef __PSYGEN_FUNCTIONS_H__
#define __PSYGEN_FUNCTIONS_H__


#include <cmath> // TODO: remove standard cmath lib and implement a fast version appropriate for 3D

#include "PSYGEN/PSYGEN.hpp"


namespace psy {

//
//  Constants
//
static const float PI = 3.1415926535898f;
static const float EPSILON = 0.0001f;




inline bool fuzzy_eq(float a, float b, float tol=EPSILON)
{
    return ( ((a-b)<tol) && ((a-b)>-tol) );
}



template <class T>
inline T radians(const T& deg)
{
    return deg*(PI/180.0f);
}


template <typename tReal>
inline tReal sqr(const tReal& value)
{
    return value*value;
}


inline float spline(float t)
{
    return  ( t * t * (3.0f - 2.0f * t) );
}


template <class T>
inline T lerp( T& a,  T& b, float t)
{
    return a + (b-a)*t;
}

// PSYAPI  float degrees(float);
// PSYAPI  float sin(float, bool);
// PSYAPI  float cos(float, bool);
// PSYAPI  float tan(float, bool);
// PSYAPI  float asin(float, bool);
// PSYAPI  float acos(float, bool);
// PSYAPI  float atan(float, bool);

/*
//
//  Exponential functions
//
PSYAPI  float pow(float , float, bool);
PSYAPI  float exp(float, bool);
PSYAPI  float sqr(float);
PSYAPI  float log(float, bool);
PSYAPI  float exp2(float);
PSYAPI  float log2(float);
PSYAPI  float sqrt(float, bool);
PSYAPI  float inversesqrt(float);


//
//  Common functions
//
//PSYAPI  float abs(float x);
PSYAPI  float sign(float x);
//PSYAPI  float floor(float x, bool);
PSYAPI  float ceil(float x, bool);
PSYAPI  float fract(float x);
//PSYAPI  float min(float a, float b);
//PSYAPI  float max(float a, float b);
PSYAPI  float clamp(float x, float min, float max);
PSYAPI  float lerp(float a, float b, float t);
PSYAPI  float step(float edge, float x);
PSYAPI  float smoothstep(float edge0, float edge1, float x);
PSYAPI  float spline(float t);
PSYAPI  bool fuzzyequal(float, float, float);*/


#include "PSYGEN/PSYmath/Functions.inl"

} //end namespace Psygen


#endif // __PSYGEN_MATH_H__
