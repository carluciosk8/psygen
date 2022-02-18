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
#ifndef __MATRIX2_H__
#define __MATRIX2_H__


#include <iostream>

#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYmath/Functions.hpp"


namespace psy
{

template <class REAL>
class /*PSYGEN_API*/ Matrix2
{
    public:
        // Components
        REAL m[2][2];

        // Static Members
        static const Matrix2 ZERO;
        static const Matrix2 IDENTITY;


		// Constructors
        Matrix2();
        Matrix2(REAL, REAL,
                REAL, REAL);
        Matrix2(REAL*);


        // Members operators
        Matrix2 operator+ (const Matrix2&) const;
        Matrix2 operator- (const Matrix2&) const;
        Matrix2 operator* (const Matrix2&) const;
        Matrix2 operator/ (const Matrix2&) const;
		Matrix2 operator* (REAL) const;

		Matrix2 operator- () const;

		Matrix2& operator+= (const Matrix2&);
        Matrix2& operator-= (const Matrix2&);
        Matrix2& operator*= (const Matrix2&);
        Matrix2& operator/= (const Matrix2&);
		Matrix2& operator*= (REAL);

        bool operator== (const Matrix2&) const;
        bool operator!= (const Matrix2&) const;

		REAL* operator[] (int);


        // Convenient functions for speed
        void add(const Matrix2&, const Matrix2&);
        void sub(const Matrix2&, const Matrix2&);
        void div(const Matrix2&, const Matrix2&);
        void mul(const Matrix2&, const Matrix2&);
        void mul(REAL, const Matrix2&);
        void mul(const Matrix2&, REAL);
        void compMul(const Matrix2&, const Matrix2&);
		void transpose();
		void inverse();
        void orthonormalize();
}; // Class Matrix2


// Typedefs
typedef Matrix2<float> mat2;
typedef Matrix2<double> dmat2;


// Non-member operators
template <class REAL>  Matrix2<REAL> operator* (REAL, const Matrix2<REAL>&);
template <class REAL>  std::ostream& operator<< (std::ostream&, const Matrix2<REAL>&);


// Non-member functions
template <class REAL>  REAL determinant(const Matrix2<REAL>&);
template <class REAL>  Matrix2<REAL> transpose(const Matrix2<REAL>&);
template <class REAL>  Matrix2<REAL> inverse(const Matrix2<REAL>&);
template <class REAL>  Matrix2<REAL> orthonormalize(const Matrix2<REAL>&);


// Include inline implementations
#include "PSYGEN/PSYmath/Matrix2.inl"

} //end namespace Psygen


#endif // define __MATRIX2_H__
