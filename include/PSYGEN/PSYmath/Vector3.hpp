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
#ifndef __VECTOR3_H__
#define __VECTOR3_H__


#include <iostream>

#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYmath/Functions.hpp"
#include "PSYGEN/PSYmath/Matrix3.hpp"


namespace psy
{


template <class REAL>
class /*PSYAPI*/ Vector3
{
   public:
      // Components
	  union
	  {
		  struct { REAL x  ;  REAL y  ;  REAL z; };
		  struct { REAL r  ;  REAL g  ;  REAL b; };
	  };

      // Static Members
      PSYAPI static const Vector3  ZERO;
      PSYAPI static const Vector3  UX;
      PSYAPI static const Vector3  UY;
      PSYAPI static const Vector3  UZ;



	  // Constructors
	  Vector3();
      Vector3(REAL, REAL, REAL);
      Vector3(REAL[3]);

      // Member operators
      Vector3 operator+(const Vector3&) const;
      Vector3 operator-(const Vector3&) const;
      Vector3 operator*(const Vector3&) const;
      Vector3 operator/(const Vector3&) const;
	  Vector3 operator*(REAL) const;

	  Vector3 operator-() const;

	  Vector3& operator+=(const Vector3&);
      Vector3& operator-=(const Vector3&);
      Vector3& operator*=(const Vector3&);
      Vector3& operator/=(const Vector3&);
      Vector3& operator*=(REAL);

      bool operator==(const Vector3&) const;
      bool operator!=(const Vector3&) const;

	  REAL& operator[](int) const;
      operator REAL*();


      // Convenient functions for speed
      void add(const Vector3&, const Vector3&);
      void sub(const Vector3&, const Vector3&);
	  void mul(REAL, const Vector3&);
	  void mul(const Vector3&, REAL);
	  void mul(const Matrix3<REAL>&, const Vector3&);
	  void mul(const Vector3&, const Matrix3<REAL>&);
      void normalize();
      void lerp(const Vector3&, const Vector3&, float);

	  void cross(const Vector3&, const Vector3&);
}; //class Vector3


    // Typedefs
    typedef Vector3<float> vec3;
    typedef Vector3<double> dvec3;
    typedef Vector3<unsigned int> ivec3;
    //typedef Vector3<unsigned char> color32;


    // Non-member operators
    template <class REAL>  Vector3<REAL> operator* (REAL, const Vector3<REAL>&);
    template <class REAL>  std::ostream& operator<< (std::ostream&, const Vector3<REAL>&);
    template <class REAL>  Vector3<REAL> operator* (const Matrix3<REAL>&, const Vector3<REAL>&);
    template <class REAL>  Vector3<REAL> operator* (const Vector3<REAL>&, const Matrix3<REAL>&);


    // Non-member functions
    template <class REAL>  REAL length(const Vector3<REAL>&);
    template <class REAL>  REAL length_sqr(const Vector3<REAL>&);
    template <class REAL>  REAL distance(const Vector3<REAL>&, const Vector3<REAL>&);
    template <class REAL>  REAL distance_sqr(const Vector3<REAL>&, const Vector3<REAL>&);
    template <class REAL>  REAL dot(const Vector3<REAL>&, const Vector3<REAL>&);
    template <class REAL>  Vector3<REAL> normalize(const Vector3<REAL>&);
    template <class REAL>  Vector3<REAL> lerp(const Vector3<REAL>&, const Vector3<REAL>&, REAL);

    template <class REAL>  Vector3<REAL> cross(const Vector3<REAL>&, const Vector3<REAL>&);


} //end namespace Psygen

// Include inline implementations
#include "PSYGEN/PSYmath/Vector3.inl"

#endif // __VECTOR3_H__
