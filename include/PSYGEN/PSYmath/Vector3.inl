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
namespace psy {


//-- constructors ---------------------------------------------------------//
template <class REAL>
inline Vector3<REAL>::Vector3()
{}

template <class REAL>
inline Vector3<REAL>::Vector3(REAL _x, REAL _y, REAL _z)
:
   x(_x),
   y(_y),
   z(_z)
{}

template <class REAL>
inline Vector3<REAL>::Vector3(REAL v[3])
:
   x(v[0]),
   y(v[1]),
   z(v[2])
{}



//-- operators ------------------------------------------------------------//
template <class REAL>
inline Vector3<REAL> Vector3<REAL>::operator+(const Vector3<REAL>& v) const
{
    return Vector3(x + v.x  ,  y + v.y  ,  z + v.z);
}

template <class REAL>
inline Vector3<REAL> Vector3<REAL>::operator-(const Vector3<REAL>& v) const
{
    return Vector3(x - v.x  ,  y - v.y  ,  z - v.z);
}

template <class REAL>
inline Vector3<REAL> Vector3<REAL>::operator*(const Vector3<REAL>& v) const
{
    return Vector3(x*v.x , y*v.y , z*v.z);
}

template <class REAL>
inline Vector3<REAL> Vector3<REAL>::operator/(const Vector3<REAL>& v) const
{
    return Vector3(x/v.x , y/v.y , z/v.z);
}

template <class REAL>
inline Vector3<REAL> Vector3<REAL>::operator* (REAL a) const
{
   return Vector3(x*a , y*a , z*a);
}



template <class REAL>
inline Vector3<REAL>& Vector3<REAL>::operator+= (const Vector3<REAL>& v)
{
    x+=v.x  ;  y+=v.y  ;  z+=v.z;
    return *this;
}

template <class REAL>
inline Vector3<REAL>& Vector3<REAL>::operator-= (const Vector3<REAL>& v)
{
    x-=v.x  ;  y-=v.y  ;  z-=v.z;
    return *this;
}

template <class REAL>
inline Vector3<REAL>& Vector3<REAL>::operator*= (const Vector3<REAL>& v)
{
    x*=v.x  ;  y*=v.y  ;  z*=v.z;
    return *this;
}

template <class REAL>
inline Vector3<REAL>& Vector3<REAL>::operator/= (const Vector3<REAL>& v)
{
    x/=v.x  ;  y/=v.y  ;  z/=v.z;
    return *this;
}

template <class REAL>
inline Vector3<REAL>& Vector3<REAL>::operator*= (REAL a)
{
    x*=a  ;  y*=a  ;  z*=a;
    return *this;
}



template <class REAL>
inline Vector3<REAL> Vector3<REAL>::operator- () const
{
   return Vector3<REAL>(-x , -y , -z);
}



template <class REAL>
inline bool Vector3<REAL>::operator== (const Vector3& v) const
{
   return ( COMPARE(x, v.x, EPSILON) && COMPARE(y, v.y, EPSILON)  && COMPARE(z, v.z, EPSILON) );
}


template <class REAL>
inline bool Vector3<REAL>::operator!= (const Vector3& v) const
{
   return ( !COMPARE(x, v.x, EPSILON) || !COMPARE(y, v.y, EPSILON) || !COMPARE(z, v.z, EPSILON) );
}




// access vector V as V[0] = V.x, V[1] = V.y, V[2] = V.z
//
// WARNING.  These member functions rely on
// (1) Vector3 not having virtual functions
// (2) the data packed in a 3*sizeof(REAL) memory block
template <class REAL>
inline REAL& Vector3<REAL>::operator[] (int i) const
{
   return ((REAL*)this)[i];
}

template <class REAL>
inline Vector3<REAL>::operator REAL* ()
{
   return (REAL*)this;
}



//-- Member functions ---------------------------------------------------------
template <class REAL>
inline void Vector3<REAL>::add(const Vector3& v, const Vector3& u)
{
   x = v.x + u.x;
   y = v.y + u.y;
   z = v.z + u.z;
}

template <class REAL>
inline void Vector3<REAL>::sub(const Vector3& v, const Vector3& u)
{
   x = v.x - u.x;
   y = v.y - u.y;
   z = v.z - u.z;
}

template <class REAL>
inline void Vector3<REAL>::mul(REAL a, const Vector3& v)
{
   x = a*v.x;
   y = a*v.y;
   z = a*v.z;
}

template <class REAL>
inline void Vector3<REAL>::mul(const Vector3& v, REAL a)
{
   x = v.x*a;
   y = v.y*a;
   z = v.z*a;
}

template <class REAL>
inline void Vector3<REAL>::mul(const Matrix3<REAL>& M, const Vector3& v)
{
    x = M.m[0][0]*v.x + M.m[0][1]*v.y + M.m[0][2]*v.z;
    y = M.m[1][0]*v.x + M.m[1][1]*v.y + M.m[1][2]*v.z;
    z = M.m[2][0]*v.x + M.m[2][1]*v.y + M.m[2][2]*v.z;
}

template <class REAL>
inline void Vector3<REAL>::mul(const Vector3& v, const Matrix3<REAL>& M)
{
   x = v.x*M.m[0][0] + v.y*M.m[1][0] + v.z*M.m[2][0];
   y = v.x*M.m[0][1] + v.y*M.m[1][1] + v.z*M.m[2][1];
   z = v.x*M.m[0][2] + v.y*M.m[1][2] + v.z*M.m[2][2];
}

template <class REAL>
inline void Vector3<REAL>::normalize()
{
	(*this) *= 1.0f/sqrt(x*x + y*y + z*z);
}

template <class REAL>
inline void Vector3<REAL>::lerp(const Vector3& a, const Vector3& b, float t)
{
   x = lerp(a.x, b.x, t);
   y = lerp(a.y, b.y, t);
   z = lerp(a.z, b.z, t);
}



template <class REAL>
inline void Vector3<REAL>::cross(const Vector3<REAL>& u, const Vector3<REAL>& v)
{
   x = u.y*v.z - u.z*v.y;
   y = u.z*v.x - u.x*v.z;
   z = u.x*v.y - u.y*v.x;
}



//-- Non-member operators ---------------------------------------------------------
template <class REAL>
inline Vector3<REAL> operator* (REAL a, const Vector3<REAL>& v)
{
   return Vector3<REAL>(a*v.x, a*v.y, a*v.z);
}

template <class REAL>
inline std::ostream& operator<< (std::ostream& s, const Vector3<REAL>& v)
{
   return s << '(' << v.x << ", " << v.y << ", "  << v.z << ')';
}

template <class REAL>
inline Vector3<REAL> operator* (const Matrix3<REAL>& M, const Vector3<REAL>& v)
{
   return Vector3<REAL>(M.m[0][0]*v.x + M.m[0][1]*v.y + M.m[0][2]*v.z,
	                    M.m[1][0]*v.x + M.m[1][1]*v.y + M.m[1][2]*v.z,
	                    M.m[2][0]*v.x + M.m[2][1]*v.y + M.m[2][2]*v.z);
}

template <class REAL>
inline Vector3<REAL> operator* (const Vector3<REAL>& v, const Matrix3<REAL>& M)
{
   return Vector3<REAL>(v.x*M.m[0][0] + v.y*M.m[1][0] + v.z*M.m[2][0],
	                    v.x*M.m[0][1] + v.y*M.m[1][1] + v.z*M.m[2][1],
	                    v.x*M.m[0][2] + v.y*M.m[1][2] + v.z*M.m[2][2]);
}



//-- Non-member functions ---------------------------------------------------------
template <class REAL>
inline REAL length(const Vector3<REAL>& v)
{
   return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

template <class REAL>
inline REAL length_sqr(const Vector3<REAL>& v)
{
   return (v.x*v.x + v.y*v.y + v.z*v.z);
}

template <class REAL>
inline REAL distance(const Vector3<REAL>& v1, const Vector3<REAL>& v2)
{
   return Sqrt(Sqr(v1.x - v2.x) + Sqr(v1.y - v2.y) + Sqr(v1.z - v2.z));
}

template <class REAL>
inline REAL distance_sqr(const Vector3<REAL>& v1, const Vector3<REAL>& v2)
{
   return sqr(v1.x - v2.x) + sqr(v1.y - v2.y) + sqr(v1.z - v2.z);
   //return sqr(v1 - v2);
}

template <class REAL>
inline REAL dot(const Vector3<REAL>& v1, const Vector3<REAL>& v2)
{
   return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

template <class REAL>
inline Vector3<REAL> normalize(const Vector3<REAL>& v)
{
	return (1.0f/sqrt(v.x*v.x + v.y*v.y + v.z*v.z))*v;
}

template <class REAL>
inline Vector3<REAL> lerp(const Vector3<REAL>& a, const Vector3<REAL>& b, REAL t)
{
    return a + (b-a)*t;
}

template <class REAL>
inline Vector3<REAL> cross(const Vector3<REAL>& u, const Vector3<REAL>& v)
{
    return Vector3<REAL>(u.y*v.z - u.z*v.y  ,  u.z*v.x - u.x*v.z  ,  u.x*v.y - u.y*v.x);
}


}