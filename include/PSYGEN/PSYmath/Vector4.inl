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
//-- constructors ---------------------------------------------------------//
template <class REAL>
inline Vector4<REAL>::Vector4()
{}

template <class REAL>
inline Vector4<REAL>::Vector4(REAL _x, REAL _y, REAL _z, REAL _w)
:
   x(_x),
   y(_y),
   z(_z),
   w(_w)
{}

template <class REAL>
inline Vector4<REAL>::Vector4(REAL v[4])
:
   x(v[0]),
   y(v[1]),
   z(v[2]),
   w(v[3])
{}


//-- operators ------------------------------------------------------------//
template <class REAL>
inline Vector4<REAL> Vector4<REAL>::operator+(const Vector4<REAL>& v) const
{
   return Vector4<REAL>(x+v.x , y+v.y , z+v.z , w+v.w);
}

template <class REAL>
inline Vector4<REAL> Vector4<REAL>::operator-(const Vector4<REAL>& v) const
{
   return Vector4<REAL>(x-v.x , y-v.y , z-v.z , w-v.w);
}

template <class REAL>
inline Vector4<REAL> Vector4<REAL>::operator*(const Vector4<REAL>& v) const
{
   return Vector4<REAL>(x*v.x , y*v.y , z*v.z , w*v.w);
}

template <class REAL>
inline Vector4<REAL> Vector4<REAL>::operator/(const Vector4<REAL>& v) const
{
   return Vector4<REAL>(x/v.x , y/v.y , z/v.z , w/v.w);
}

template <class REAL>
inline Vector4<REAL> Vector4<REAL>::operator* (REAL a) const
{
   return Vector4<REAL>(x*a , y*a , z*a , w*a);
}



template <class REAL>
inline Vector4<REAL>& Vector4<REAL>::operator+= (const Vector4<REAL>& v)
{
   x+=v.x;
   y+=v.y;
   z+=v.z;
   w+=v.w;
   return *this;
}

template <class REAL>
inline Vector4<REAL>& Vector4<REAL>::operator-= (const Vector4<REAL>& v)
{
   x-=v.x;
   y-=v.y;
   z-=v.z;
   w-=v.w;
   return *this;
}

template <class REAL>
inline Vector4<REAL>& Vector4<REAL>::operator*= (const Vector4<REAL>& v)
{
   x*=v.x;
   y*=v.y;
   z*=v.z;
   w*=v.w;
   return *this;
}

template <class REAL>
inline Vector4<REAL>& Vector4<REAL>::operator/= (const Vector4<REAL>& v)
{
   x/=v.x;
   y/=v.y;
   z/=v.z;
   w/=v.w;
   return *this;
}

template <class REAL>
inline Vector4<REAL>& Vector4<REAL>::operator*= (REAL a)
{
    x*=a;
    y*=a;
    z*=a;
    w*=a;
    return *this;
}


template <class REAL>
inline Vector4<REAL> Vector4<REAL>::operator- () const
{
   return Vector4<REAL>(-x , -y , -z , -w);
}



template <class REAL>
inline bool Vector4<REAL>::operator== (const Vector4& v) const
{
   return ( fuzzyequal(x, v.x) && fuzzyequal(y, v.y) && fuzzyequal(z, v.z) && fuzzyequal(w, v.w) );
}


template <class REAL>
inline bool Vector4<REAL>::operator!= (const Vector4& v) const
{
   return ( !fuzzyequal(x, v.x) || !fuzzyequal(y, v.y) || !fuzzyequal(z, v.z) || !fuzzyequal(w, v.w) );
}



// access vector V as V[0] = V.x, V[1] = V.y, V[2] = V.z, V[3] = V.w
//
// WARNING.  These member functions rely on
// (1) Vector4 not having virtual functions
// (2) the data packed in a 4*sizeof(REAL) memory block
template <class REAL>
inline REAL& Vector4<REAL>::operator[] (int i) const
{
   return ((REAL*)this)[i];
}

template <class REAL>
inline Vector4<REAL>::operator REAL* ()
{
   return (REAL*)this;
}



//-- Member functions ---------------------------------------------------------
template <class REAL>
inline void Vector4<REAL>::add(const Vector4<REAL>& v, const Vector4<REAL>& u)
{
   x = v.x + u.x;
   y = v.y + u.y;
   z = v.z + u.z;
   w = v.w + u.w;
}

template <class REAL>
inline void Vector4<REAL>::sub(const Vector4<REAL>& v, const Vector4<REAL>& u)
{
   x = v.x - u.x;
   y = v.y - u.y;
   z = v.z - u.z;
   w = v.w - u.w;
}

template <class REAL>
inline void Vector4<REAL>::mul(REAL a, const Vector4& v)
{
   x = a*v.x;
   y = a*v.y;
   z = a*v.z;
   w = a*v.w;
}

template <class REAL>
inline void Vector4<REAL>::mul(const Vector4& v, REAL a)
{
   x = v.x*a;
   y = v.y*a;
   z = v.z*a;
   w = v.w*a;
}

template <class REAL>
inline void Vector4<REAL>::mul(const Matrix4<REAL>& M, const Vector4& v)
{
    x = M.m[0][0]*v.x + M.m[0][1]*v.y + M.m[0][2]*v.z + M.m[0][3]*v.w;
    y = M.m[1][0]*v.x + M.m[1][1]*v.y + M.m[1][2]*v.z + M.m[1][3]*v.w;
    z = M.m[2][0]*v.x + M.m[2][1]*v.y + M.m[2][2]*v.z + M.m[2][3]*v.w;
    w = M.m[3][0]*v.x + M.m[3][1]*v.y + M.m[3][2]*v.z + M.m[3][3]*v.w;
}

template <class REAL>
inline void Vector4<REAL>::mul(const Vector4& v, const Matrix4<REAL>& M)
{
   x = v.x*M.m[0][0] + v.y*M.m[1][0] + v.z*M.m[2][0] + v.w*M.m[3][0];
   y = v.x*M.m[0][1] + v.y*M.m[1][1] + v.z*M.m[2][1] + v.w*M.m[3][1];
   z = v.x*M.m[0][2] + v.y*M.m[1][2] + v.z*M.m[2][2] + v.w*M.m[3][2];
   w = v.x*M.m[0][3] + v.y*M.m[1][3] + v.z*M.m[2][3] + v.w*M.m[3][3];
}

template <class REAL>
inline void Vector4<REAL>::normalize()
{
	(*this) *= 1.0f/sqrt(x*x + y*y + z*z + w*w);
}

template <class REAL>
inline void Vector4<REAL>::lerp(const Vector4& a, const Vector4& b, float t)
{
   x = lerp(a.x, b.x, t);
   y = lerp(a.y, b.y, t);
   z = lerp(a.z, b.z, t);
   w = lerp(a.w, b.w, t);
}



//-- Non-member operators ---------------------------------------------------------
template <class REAL>
inline Vector4<REAL> operator*(REAL a, const Vector4<REAL>& v)
{
   return Vector4<REAL>(a*v.x  ,  a*v.y  ,  a*v.z  ,  a*v.w);
}

template <class REAL>
inline std::ostream& operator<<(std::ostream& s, const Vector4<REAL>& v)
{
   return s << '(' << v.x << ", " << v.y << ", "  << v.z << ", "  << v.w << ')';
}

template <class REAL>
inline Vector4<REAL> operator*(const Matrix4<REAL>& M, const Vector4<REAL>& v)
{
   return Vector4<REAL>(M.m[0][0]*v.x + M.m[0][1]*v.y + M.m[0][2]*v.z + M.m[0][3]*v.w,
	                    M.m[1][0]*v.x + M.m[1][1]*v.y + M.m[1][2]*v.z + M.m[1][3]*v.w,
	                    M.m[2][0]*v.x + M.m[2][1]*v.y + M.m[2][2]*v.z + M.m[2][3]*v.w,
	                    M.m[3][0]*v.x + M.m[3][1]*v.y + M.m[3][2]*v.z + M.m[3][3]*v.w);
}

template <class REAL>
inline Vector4<REAL> operator*(const Vector4<REAL>& v, const Matrix4<REAL>& M)
{
   return Vector4<REAL>(v.x*M.m[0][0] + v.y*M.m[1][0] + v.z*M.m[2][0] + v.w*M.m[3][0],
	                    v.x*M.m[0][1] + v.y*M.m[1][1] + v.z*M.m[2][1] + v.w*M.m[3][1],
	                    v.x*M.m[0][2] + v.y*M.m[1][2] + v.z*M.m[2][2] + v.w*M.m[3][2],
	                    v.x*M.m[0][3] + v.y*M.m[1][3] + v.z*M.m[2][3] + v.w*M.m[3][3]);
}



//-- Non-member functions ---------------------------------------------------------
template <class REAL>
inline REAL length(const Vector4<REAL>& v)
{
   return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

template <class REAL>
inline REAL sqrLength(const Vector4<REAL>& v)
{
   return (v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

template <class REAL>
inline REAL distance(const Vector4<REAL>& v1, const Vector4<REAL>& v2)
{
   return sqrt(sqr(v1.x - v2.x) + sqr(v1.y - v2.y) + sqr(v1.z - v2.z) + sqr(v1.w - v2.w));
}

template <class REAL>
inline REAL dot(const Vector4<REAL>& v, const Vector4<REAL>& u)
{
   return (v.x*u.x + v.y*u.y + v.z*u.z + v.w*u.w);
}

template <class REAL>
inline Vector4<REAL> normalize(const Vector4<REAL>& v)
{
	return (1.0f/Sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w))*v;
}

template <class REAL>
inline Vector4<REAL> lerp(const Vector4<REAL>& a, const Vector4<REAL>& b, REAL t)
{
    return a + (b-a)*t;
}
