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
inline HermiteSpline::HermiteSpline(const vec3& vp0, const vec3& vm0, const vec3& vp1, const vec3& vm1)
:
	p0(vp0),
	m0(vm0),
	p1(vp1),
	m1(vm1){
}



inline vec3 HermiteSpline::operator()(float t)
{
	return p0*(2*t*t*t - 3*t*t + 1) + m0*(t*t*t - 2*t*t + t) + 
		   p1*(-2*t*t*t + 3*t*t) + m1*(t*t*t - t*t);
}



inline void HermiteSpline::pos(vec3& p, float t)
{
	/* 
	position interpolation, t = [0,1):

	h00(t) = 2t� - 3t� + 1
	h10(t) = t� - 2t� + t
	h01(t) = -2t� + 3t�
	h11(t) = t� -  t�

	p(t) = h00(t)*p0 + h10(t)*m0 + h01(t)*p1 + h11(t)*m1
	*/

	p.add( p0*(2*t*t*t - 3*t*t + 1) + m0*(t*t*t - 2*t*t + t) ,
		   p1*(-2*t*t*t + 3*t*t) + m1*(t*t*t - t*t) );
}



inline void HermiteSpline::vel(vec3& v, float t)
{
	/* 
	velocity (first derivative) interpolation, t = [0,1):

	h00'(t) = 6t� - 6t
	h10'(t) = 3t� - 4t + 1
	h01'(t) = -6t� + 6t
	h11'(t) = 3t� -  2t

	v(t) = p'(t) = h00'(t)*p0 + h10'(t)*m0 + h01'(t)*p1 + h11'(t)*m1
	*/

	v.add( (6*t*t*t - 6*t)*p0 + (3*t*t - 4*t + 1)*m0 ,
		   (-6*t*t + 6*t)*p1 + (3*t*t -  2*t)*m1 );
}


inline void HermiteSpline::acc(vec3& a, float t)
{
	/* 
	acceleration (second derivative) interpolation, t = [0,1):

	h00''(t) = 12t - 6
	h10''(t) = 6t - 4
	h01''(t) = -12t + 6
	h11''(t) = 6t -  2

	a(t) = p''(t) = h00''(t)*p0 + h10''(t)*m0 + h01''(t)*p1 + h11''(t)*m1
	*/

	a.add( (12*t - 6)*p0 + (6*t - 4)*m0 ,
		  (-12*t + 6)*p1 + (6*t - 2)*m1 );
}
