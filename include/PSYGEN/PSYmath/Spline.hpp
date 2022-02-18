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
#ifndef __SPLINE_H__
#define __SPLINE_H__

#include "PSYGEN/PSYmath/Vector3.hpp"

namespace psy
{


class HermiteSpline
{
	public:
		vec3  p0;
		vec3  m0;
		vec3  p1;
		vec3  m1;


		HermiteSpline(const vec3& vp0, const vec3& vm0, const vec3& vp1, const vec3& vm1);
		vec3 operator()(float t);
		void pos(vec3& p, float t);
		void vel(vec3& v, float t);
		void acc(vec3& a, float t);
};

#include "PSYGEN/PSYmath/Spline.inl"

}

#endif //__SPLINE_H__
