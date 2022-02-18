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
#ifndef __VECTOR2_H__
#define __VECTOR2_H__


#include <iostream>

#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYmath/Functions.hpp"
#include "PSYGEN/PSYmath/Matrix2.hpp"


namespace psy
{

template <class REAL>
class /*PSYGEN_API*/ Vector2
{
   public:
      // Components
      REAL  x;
      REAL  y;

      // Static Members
      static const Vector2  ZERO;
      static const Vector2  UX;
      static const Vector2  UY;



	  // Constructors
	  Vector2();
      Vector2(REAL, REAL);
      Vector2(REAL[2]);

      // Member operators
      Vector2 operator+(const Vector2&) const;
      Vector2 operator-(const Vector2&) const;
      Vector2 operator*(const Vector2&) const;
      Vector2 operator/(const Vector2&) const;
	  Vector2 operator*(REAL) const;

	  Vector2 operator-() const;

	  Vector2& operator+=(const Vector2&);
      Vector2& operator-=(const Vector2&);
      Vector2& operator*=(const Vector2&);
      Vector2& operator/=(const Vector2&);
      Vector2& operator*=(REAL);

      bool operator==(const Vector2&) const;
      bool operator!=(const Vector2&) const;

	  REAL& operator[](int) const;
      operator REAL*();

      void row(const Matrix2<REAL>&, int);
      void column(const Matrix2<REAL>&, int);

      // Convenient functions for speed
      void add(const Vector2&, const Vector2&);
      void sub(const Vector2&, const Vector2&);
	  void mul(REAL, const Vector2&);
	  void mul(const Vector2&, REAL);
	  void mul(const Matrix2<REAL>&, const Vector2&);
	  void mul(const Vector2&, const Matrix2<REAL>&);
      void normalize();
      void lerp(const Vector2&, const Vector2&, float);
}; //class Vector2


// Typedefs
typedef Vector2<float> vec2;
typedef Vector2<double> dvec2;


// Non-member operators
template <class REAL>  Vector2<REAL> operator* (REAL, const Vector2<REAL>&);
template <class REAL>  std::ostream& operator<< (std::ostream&, const Vector2<REAL>&);
template <class REAL>  Vector2<REAL> operator* (const Matrix2<REAL>&, const Vector2<REAL>&);
template <class REAL>  Vector2<REAL> operator* (const Vector2<REAL>&, const Matrix2<REAL>&);


// Non-member functions
template <class REAL>  REAL length(const Vector2<REAL>&);
template <class REAL>  REAL sqrLength(const Vector2<REAL>&);
template <class REAL>  REAL distance(const Vector2<REAL>&, const Vector2<REAL>&);
template <class REAL>  REAL dot(const Vector2<REAL>&, const Vector2<REAL>&);
template <class REAL>  Vector2<REAL> normalize(const Vector2<REAL>&);
template <class REAL>  Vector2<REAL> lerp(const Vector2<REAL>&, const Vector2<REAL>&, REAL);


// Include inline implementations
#include "PSYGEN/PSYmath/Vector2.inl"

} //end namespace Psygen


#endif // __VECTOR2_H__
