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
#ifndef __PSYGEN_MAT3_H__
#define __PSYGEN_MAT3_H__


#include <iostream>

#include "PSYGEN/PSYGEN.hpp"
#include "PSYGEN/PSYmath/Functions.hpp"


namespace psy {


template <class REAL>
class /*PSYGEN_API*/ Matrix3
{
    public:
        // Components
        REAL m[3][3];

        // Static Members
        static const Matrix3 ZERO;
        static const Matrix3 IDENTITY;


		// Constructors
        Matrix3();
        Matrix3(REAL, REAL, REAL,
                REAL, REAL, REAL,
                REAL, REAL, REAL);
        Matrix3(REAL*);


        // Members operators
        Matrix3 operator+ (const Matrix3&) const;
        Matrix3 operator- (const Matrix3&) const;
        Matrix3 operator* (const Matrix3&) const;
        Matrix3 operator/ (const Matrix3&) const;
		Matrix3 operator* (REAL) const;

		Matrix3 operator- () const;

		Matrix3& operator+= (const Matrix3&);
        Matrix3& operator-= (const Matrix3&);
        Matrix3& operator*= (const Matrix3&);
        Matrix3& operator/= (const Matrix3&);
		Matrix3& operator*= (REAL);

        bool operator== (const Matrix3&) const;
        bool operator!= (const Matrix3&) const;

		REAL* operator[] (int);
		operator REAL*();


        // Convenient functions for speed
        void add(const Matrix3&, const Matrix3&);
        void sub(const Matrix3&, const Matrix3&);
        void div(const Matrix3&, const Matrix3&);
        void mul(const Matrix3&, const Matrix3&);
        void mul(REAL, const Matrix3&);
        void mul(const Matrix3&, REAL);
        void compMul(const Matrix3&, const Matrix3&);
		void transpose();
		void inverse();
        void orthonormalize();
}; // Class Matrix3

// Include inline implementations
#include "PSYGEN/PSYmath/Matrix3.inl"

    // Typedefs
    typedef Matrix3<float> mat3;
    typedef Matrix3<double> dmat3;


    // Non-member operators
    template <class REAL>  Matrix3<REAL> operator* (REAL, const Matrix3<REAL>&);
    template <class REAL>  std::ostream& operator<< (std::ostream&, const Matrix3<REAL>&);


    // Non-member functions
    template <class REAL>  REAL determinant(const Matrix3<REAL>&);
    template <class REAL>  Matrix3<REAL> transpose(const Matrix3<REAL>&);
    template <class REAL>  Matrix3<REAL> inverse(const Matrix3<REAL>&);
    template <class REAL>  Matrix3<REAL> orthonormalize(const Matrix3<REAL>&);

    //template <class REAL>
    //inline Matrix3<REAL>& radians(Matrix3<REAL>& m) { return radians< Matrix3<REAL> > (m); }



}// namespace Psygen


#endif //__PSYGEN_MAT3_H__
