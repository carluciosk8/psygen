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
#ifndef __MATRIX4_H__
#define __MATRIX4_H__


#include <iostream>

#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYmath/Functions.hpp"


namespace psy {


template <class REAL>
class /*PSYGEN_API*/ Matrix4
{
    public:
        // Components
        REAL m[4][4];

        // Static Members
        static const Matrix4 ZERO;
        static const Matrix4 IDENTITY;


		// Constructors
        Matrix4();
        Matrix4(REAL, REAL, REAL, REAL,
                REAL, REAL, REAL, REAL,
                REAL, REAL, REAL, REAL,
                REAL, REAL, REAL, REAL);
        Matrix4(REAL*);


        // Members operators
        Matrix4 operator+ (const Matrix4&) const;
        Matrix4 operator- (const Matrix4&) const;
        Matrix4 operator* (const Matrix4&) const;
        Matrix4 operator/ (const Matrix4&) const;
		Matrix4 operator* (REAL) const;

		Matrix4 operator- () const;

		Matrix4& operator+= (const Matrix4&);
        Matrix4& operator-= (const Matrix4&);
        Matrix4& operator*= (const Matrix4&);
        Matrix4& operator/= (const Matrix4&);
		Matrix4& operator*= (REAL);

        bool operator== (const Matrix4&) const;
        bool operator!= (const Matrix4&) const;

		REAL* operator[] (int);
        operator REAL*();


        // Convenient functions for speed
        void add(const Matrix4&, const Matrix4&);
        void sub(const Matrix4&, const Matrix4&);
        void div(const Matrix4&, const Matrix4&);
        void mul(const Matrix4&, const Matrix4&);
        void mul(REAL, const Matrix4&);
        void mul(const Matrix4&, REAL);
        void compMul(const Matrix4&, const Matrix4&);
		void transpose();
		void inverse();
        void orthonormalize();
}; // Class Matrix4


// Typedefs
typedef Matrix4<float> mat4;
typedef Matrix4<double> dmat4;


// Non-member operators
template <class REAL>  Matrix4<REAL> operator* (REAL, const Matrix4<REAL>&);
template <class REAL>  std::ostream& operator<< (std::ostream&, const Matrix4<REAL>&);


// Non-member functions
template <class REAL>  REAL determinant(const Matrix4<REAL>&);
template <class REAL>  Matrix4<REAL> transpose(const Matrix4<REAL>&);
template <class REAL>  Matrix4<REAL> inverse(const Matrix4<REAL>&);
template <class REAL>  Matrix4<REAL> orthonormalize(const Matrix4<REAL>&);


// Include inline implementations
#include "PSYGEN/PSYmath/Matrix4.inl"

} //end namespace Psygen


#endif // define __MATRIX4_H__
