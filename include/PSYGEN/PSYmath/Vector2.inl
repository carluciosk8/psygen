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
inline Vector2<REAL>::Vector2()
:
   x(0.0),
   y(0.0)
{}

template <class REAL>
inline Vector2<REAL>::Vector2(REAL vx, REAL vy)
:
   x(vx),
   y(vy)
{}

template <class REAL>
inline Vector2<REAL>::Vector2(REAL v[2])
:
   x(v[0]),
   y(v[1])
{}



//-- operators ------------------------------------------------------------//
template <class REAL>
inline Vector2<REAL> Vector2<REAL>::operator+ (const Vector2<REAL>& v) const
{
   return Vector2(x+v.x, y+v.y);
}

template <class REAL>
inline Vector2<REAL> Vector2<REAL>::operator- (const Vector2<REAL>& v) const
{
   return Vector2(x-v.x, y-v.y);
}

template <class REAL>
inline Vector2<REAL> Vector2<REAL>::operator* (const Vector2<REAL>& v) const
{
   return Vector2(x*v.x, y*v.y);
}

template <class REAL>
inline Vector2<REAL> Vector2<REAL>::operator/ (const Vector2<REAL>& v) const
{
   return Vector2(x/v.x, y/v.y);
}

template <class REAL>
inline Vector2<REAL> Vector2<REAL>::operator* (REAL a) const
{
   return Vector2(x*a, y*a);
}



template <class REAL>
inline Vector2<REAL>& Vector2<REAL>::operator+= (const Vector2<REAL>& v)
{
   x+=v.x;
   y+=v.y;
   return *this;
}

template <class REAL>
inline Vector2<REAL>& Vector2<REAL>::operator-= (const Vector2<REAL>& v)
{
   x-=v.x;
   y-=v.y;
   return *this;
}

template <class REAL>
inline Vector2<REAL>& Vector2<REAL>::operator*= (const Vector2<REAL>& v)
{
   x*=v.x;
   y*=v.y;
   return *this;
}

template <class REAL>
inline Vector2<REAL>& Vector2<REAL>::operator/= (const Vector2<REAL>& v)
{
   x/=v.x;
   y/=v.y;
   return *this;
}

template <class REAL>
inline Vector2<REAL>& Vector2<REAL>::operator*= (REAL a)
{
    x*=a;
    y*=a;
    return *this;
}



template <class REAL>
inline Vector2<REAL> Vector2<REAL>::operator- () const
{
   return Vector2<REAL>(-x,-y);
}



template <class REAL>
inline bool Vector2<REAL>::operator== (const Vector2& v) const
{
   return ( fuzzyequal(x, v.x) && fuzzyequal(y, v.y) ); 
}


template <class REAL>
inline bool Vector2<REAL>::operator!= (const Vector2& v) const
{
   return ( !fuzzyequal(x, v.x) || !fuzzyequal(y, v.y) ); 
}



// access vector V as V[0] = V.x, V[1] = V.y
//
// WARNING.  These member functions rely on
// (1) Vector2 not having virtual functions
// (2) the data packed in a 2*sizeof(REAL) memory block
template <class REAL>
inline REAL& Vector2<REAL>::operator[] (int i) const
{
   return ((REAL*)this)[i];
}

template <class REAL>
inline Vector2<REAL>::operator REAL* ()
{
   return (REAL*)this;
}



//-- Member functions ---------------------------------------------------------
template <class REAL>
inline void Vector2<REAL>::row(const Matrix2<REAL>& M, int i)
{
	x = M[i][0]  ;  y = M[i][1];
}



template <class REAL>
inline void Vector2<REAL>::column(const Matrix2<REAL>& M, int i)
{
	x = M[0][i];
	y = M[1][i];
}



template <class REAL>
inline void Vector2<REAL>::add(const Vector2& v, const Vector2& u)
{
   x = v.x + u.x;
   y = v.y + u.y;
}

template <class REAL>
inline void Vector2<REAL>::sub(const Vector2& v, const Vector2& u)
{
   x = v.x - u.x;
   y = v.y - u.y;
}

template <class REAL>
inline void Vector2<REAL>::mul(REAL a, const Vector2& v)
{
   x = a*v.x;
   y = a*v.y;
}

template <class REAL>
inline void Vector2<REAL>::mul(const Vector2& v, REAL a)
{
   x = v.x*a;
   y = v.y*a;
}

template <class REAL>
inline void Vector2<REAL>::mul(const Matrix2<REAL>& M, const Vector2& v)
{
   x = M.m[0][0]*v.x + M.m[0][1]*v.y;
   y = M.m[1][0]*v.x + M.m[1][1]*v.y;
}

template <class REAL>
inline void Vector2<REAL>::mul(const Vector2& v, const Matrix2<REAL>& M)
{
   x = v.x*M.m[0][0] + v.y*M.m[1][0];
   y = v.x*M.m[0][1] + v.y*M.m[1][1];
}

template <class REAL>
inline void Vector2<REAL>::normalize()
{
	(*this) *= 1.0f/fSqrt(x*x + y*y);
}

template <class REAL>
inline void Vector2<REAL>::lerp(const Vector2& a, const Vector2& b, float t)
{
   x = lerp(a.x, b.x, t);
   y = lerp(a.y, b.y, t);
}



//-- Non-member operators ---------------------------------------------------------
template <class REAL>
inline Vector2<REAL> operator* (REAL a, const Vector2<REAL>& v)
{
   return Vector2<REAL>(a*v.x, a*v.y);
}

template <class REAL>
inline std::ostream& operator<< (std::ostream& s, const Vector2<REAL>& v)
{
   return s << '(' << v.x << ", " << v.y << ')';
}

template <class REAL>
inline Vector2<REAL> operator* (const Matrix2<REAL>& M, const Vector2<REAL>& v)
{
   return Vector2<REAL>(M.m[0][0]*v.x + M.m[0][1]*v.y, 
	                    M.m[1][0]*v.x + M.m[1][1]*v.y);
}

template <class REAL>
inline Vector2<REAL> operator* (const Vector2<REAL>& v, const Matrix2<REAL>& M)
{
   return Vector2<REAL>(v.x*M.m[0][0] + v.y*M.m[1][0], 
	                    v.x*M.m[0][1] + v.y*M.m[1][1]);
}



//-- Non-member functions ---------------------------------------------------------
template <class REAL>
inline REAL length(const Vector2<REAL>& v)
{
   return sqrt(v.x*v.x + v.y*v.y);
}

template <class REAL>
inline REAL sqrLength(const Vector2<REAL>& v)
{
   return (v.x*v.x + v.y*v.y);
}

template <class REAL>
inline REAL distance(const Vector2<REAL>& v1, const Vector2<REAL>& v2)
{
   return sqrt(sqr(v1.x - v2.x) + sqr(v1.y - v2.y));
}

template <class REAL>
inline REAL dot(const Vector2<REAL>& v1, const Vector2<REAL>& v2)
{
   return (v1.x * v2.x + v1.y * v2.y);
}

template <class REAL>
inline Vector2<REAL> normalize(const Vector2<REAL>& v)
{
	return (1.0f/Sqrt(v.x*v.x + v.y*v.y))*v;
}

template <class REAL>
inline Vector2<REAL> lerp(const Vector2<REAL>& a, const Vector2<REAL>& b, REAL t)
{
    return a + (b-a)*t;
}
