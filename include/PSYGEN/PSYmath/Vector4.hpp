/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2008 by Carlucio Santos Cordeiro
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
    *  \brief Four dimensional vector types definition
    *  \ingroup maths
    *
    *//***********************************************************************/
#ifndef __PSYGEN_VECTOR4_H__
#define __PSYGEN_VECTOR4_H__


#include <iostream>

#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYmath/Functions.hpp"
#include "PSYGEN/PSYmath/Matrix4.hpp"


namespace psy
{

/**
  *  \author Carlucio Santos Cordeiro <carlucio@gmail.com>
  *  \ingroup maths
  *
  */
template <class REAL>
class /*PSYGEN_API*/ Vector4
{
    public:
        // Components
        union
        {
            struct { REAL x  ;  REAL y  ;  REAL z  ;  REAL w; };
            struct { REAL r  ;  REAL g  ;  REAL b  ;  REAL a; };
        };

        // Static Members
        static const Vector4  ZERO;
        static const Vector4  UX;
        static const Vector4  UY;
        static const Vector4  UZ;
        static const Vector4  UW;



        // Constructors
        Vector4();
        Vector4 ( REAL, REAL, REAL, REAL );
        Vector4 ( REAL[4] );

        // Member operators
        Vector4 operator+ ( const Vector4& ) const;
        Vector4 operator- ( const Vector4& ) const;
        Vector4 operator* ( const Vector4& ) const;
        Vector4 operator/ ( const Vector4& ) const;
        Vector4 operator* ( REAL ) const;

        Vector4 operator-() const;

        Vector4& operator+= ( const Vector4& );
        Vector4& operator-= ( const Vector4& );
        Vector4& operator*= ( const Vector4& );
        Vector4& operator/= ( const Vector4& );
        Vector4& operator*= ( REAL );

        bool operator== ( const Vector4& ) const;
        bool operator!= ( const Vector4& ) const;

        REAL& operator[] ( int ) const;
        operator REAL*();


        // Convenient functions for speed
        void add ( const Vector4&, const Vector4& );
        void sub ( const Vector4&, const Vector4& );
        void mul ( REAL, const Vector4& );
        void mul ( const Vector4&, REAL );
        void mul ( const Matrix4<REAL>&, const Vector4& );
        void mul ( const Vector4&, const Matrix4<REAL>& );
        void normalize();
        void lerp ( const Vector4&, const Vector4&, float );

        void cross ( const Vector4&, const Vector4& );
}; //class Vector4


// Typedefs
typedef Vector4<float> vec4;
typedef Vector4<double> dvec4;
typedef Vector4<int> ivec4;


// Non-member operators
template <class REAL>  Vector4<REAL> operator* ( REAL, const Vector4<REAL>& );
template <class REAL>  std::ostream& operator<< ( std::ostream&, const Vector4<REAL>& );
template <class REAL>  Vector4<REAL> operator* ( const Matrix4<REAL>&, const Vector4<REAL>& );
template <class REAL>  Vector4<REAL> operator* ( const Vector4<REAL>&, const Matrix4<REAL>& );


// Non-member functions
template <class REAL>  REAL length ( const Vector4<REAL>& );
template <class REAL>  REAL sqrLength ( const Vector4<REAL>& );
template <class REAL>  REAL distance ( const Vector4<REAL>&, const Vector4<REAL>& );
template <class REAL>  REAL dot ( const Vector4<REAL>&, const Vector4<REAL>& );
template <class REAL>  Vector4<REAL> normalize ( const Vector4<REAL>& );
template <class REAL>  Vector4<REAL> lerp ( const Vector4<REAL>&, const Vector4<REAL>&, REAL );


// Include inline implementations
#include "PSYGEN/PSYmath/Vector4.inl"

} //end namespace Psygen


#endif // __PSYGEN_VECTOR4_H__
