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
inline Matrix4<REAL>::Matrix4()
{}

template <class REAL>
inline Matrix4<REAL>::Matrix4(REAL m00, REAL m01, REAL m02, REAL m03,
                              REAL m10, REAL m11, REAL m12, REAL m13,
                              REAL m20, REAL m21, REAL m22, REAL m23,
                              REAL m30, REAL m31, REAL m32, REAL m33 )
{
   m[0][0]=m00 ; m[0][1]=m01 ; m[0][2]=m02 ; m[0][3]=m03;
   m[1][0]=m10 ; m[1][1]=m11 ; m[1][2]=m12 ; m[1][3]=m13;
   m[2][0]=m20 ; m[2][1]=m21 ; m[2][2]=m22 ; m[2][3]=m23;
   m[3][0]=m30 ; m[3][1]=m31 ; m[3][2]=m32 ; m[3][3]=m33;
}

template <class REAL>
inline Matrix4<REAL>::Matrix4(REAL* a)
{
   memcpy(m, a, 16*sizeof(REAL));
}



//-- operators ------------------------------------------------------------//
template <class REAL>
inline Matrix4<REAL> Matrix4<REAL>::operator+ (const Matrix4<REAL>& a) const
{
   return Matrix4<REAL>
   ( m[0][0]+a.m[0][0] , m[0][1]+a.m[0][1] , m[0][2]+a.m[0][2] , m[0][3]+a.m[0][3],
     m[1][0]+a.m[1][0] , m[1][1]+a.m[1][1] , m[1][2]+a.m[1][2] , m[1][3]+a.m[1][3],
     m[2][0]+a.m[2][0] , m[2][1]+a.m[2][1] , m[2][2]+a.m[2][2] , m[2][3]+a.m[2][3],
     m[3][0]+a.m[3][0] , m[3][1]+a.m[3][1] , m[3][2]+a.m[3][2] , m[3][3]+a.m[3][3] );
}

template <class REAL>
inline Matrix4<REAL> Matrix4<REAL>::operator- (const Matrix4<REAL>& a) const
{
   return Matrix4<REAL>
   ( m[0][0]-a.m[0][0] , m[0][1]-a.m[0][1] , m[0][2]-a.m[0][2] , m[0][3]-a.m[0][3],
     m[1][0]-a.m[1][0] , m[1][1]-a.m[1][1] , m[1][2]-a.m[1][2] , m[1][3]-a.m[1][3],
     m[2][0]-a.m[2][0] , m[2][1]-a.m[2][1] , m[2][2]-a.m[2][2] , m[2][3]-a.m[2][3],
     m[3][0]-a.m[3][0] , m[3][1]-a.m[3][1] , m[3][2]-a.m[3][2] , m[3][3]-a.m[3][3] );
}

template <class REAL>
inline Matrix4<REAL> Matrix4<REAL>::operator* (const Matrix4<REAL>& a) const
{
   return Matrix4<REAL>
   ( m[0][0]*a.m[0][0] + m[0][1]*a.m[1][0] + m[0][2]*a.m[2][0] + m[0][3]*a.m[3][0],
     m[0][0]*a.m[0][1] + m[0][1]*a.m[1][1] + m[0][2]*a.m[2][1] + m[0][3]*a.m[3][1],
     m[0][0]*a.m[0][2] + m[0][1]*a.m[1][2] + m[0][2]*a.m[2][2] + m[0][3]*a.m[3][2],
     m[0][0]*a.m[0][3] + m[0][1]*a.m[1][3] + m[0][2]*a.m[2][3] + m[0][3]*a.m[3][3],

     m[1][0]*a.m[0][0] + m[1][1]*a.m[1][0] + m[1][2]*a.m[2][0] + m[1][3]*a.m[3][0],
     m[1][0]*a.m[0][1] + m[1][1]*a.m[1][1] + m[1][2]*a.m[2][1] + m[1][3]*a.m[3][1],
     m[1][0]*a.m[0][2] + m[1][1]*a.m[1][2] + m[1][2]*a.m[2][2] + m[1][3]*a.m[3][2],
     m[1][0]*a.m[0][3] + m[1][1]*a.m[1][3] + m[1][2]*a.m[2][3] + m[1][3]*a.m[3][3],

     m[2][0]*a.m[0][0] + m[2][1]*a.m[1][0] + m[2][2]*a.m[2][0] + m[2][3]*a.m[3][0],
     m[2][0]*a.m[0][1] + m[2][1]*a.m[1][1] + m[2][2]*a.m[2][1] + m[2][3]*a.m[3][1],
     m[2][0]*a.m[0][2] + m[2][1]*a.m[1][2] + m[2][2]*a.m[2][2] + m[2][3]*a.m[3][2],
     m[2][0]*a.m[0][3] + m[2][1]*a.m[1][3] + m[2][2]*a.m[2][3] + m[2][3]*a.m[3][3],

     m[3][0]*a.m[0][0] + m[3][1]*a.m[1][0] + m[3][2]*a.m[2][0] + m[3][3]*a.m[3][0],
     m[3][0]*a.m[0][1] + m[3][1]*a.m[1][1] + m[3][2]*a.m[2][1] + m[3][3]*a.m[3][1],
     m[3][0]*a.m[0][2] + m[3][1]*a.m[1][2] + m[3][2]*a.m[2][2] + m[3][3]*a.m[3][2],
     m[3][0]*a.m[0][3] + m[3][1]*a.m[1][3] + m[3][2]*a.m[2][3] + m[3][3]*a.m[3][3] );
}

template <class REAL>
inline Matrix4<REAL> Matrix4<REAL>::operator/ (const Matrix4<REAL>& a) const
{
   return Matrix4<REAL>
   ( m[0][0]/a.m[0][0] , m[0][1]/a.m[0][1] , m[0][2]/a.m[0][2] , m[0][3]/a.m[0][3],
     m[1][0]/a.m[1][0] , m[1][1]/a.m[1][1] , m[1][2]/a.m[1][2] , m[1][3]/a.m[1][3],
     m[2][0]/a.m[2][0] , m[2][1]/a.m[2][1] , m[2][2]/a.m[2][2] , m[2][3]/a.m[2][3],
     m[3][0]/a.m[3][0] , m[3][1]/a.m[3][1] , m[3][2]/a.m[3][2] , m[3][3]/a.m[3][3] );
}

template <class REAL>
inline Matrix4<REAL> Matrix4<REAL>::operator* (REAL a) const
{
   return Matrix4<REAL>
   ( m[0][0]*a , m[0][1]*a , m[0][2]*a , m[0][3]*a ,
     m[1][0]*a , m[1][1]*a , m[1][2]*a , m[1][3]*a ,
     m[2][0]*a , m[2][1]*a , m[2][2]*a , m[2][3]*a ,
     m[3][0]*a , m[3][1]*a , m[3][2]*a , m[3][3]*a );
}



template <class REAL>
inline Matrix4<REAL>& Matrix4<REAL>::operator+= (const Matrix4<REAL>& a)
{
   m[0][0]+=a.m[0][0] ; m[0][1]+=a.m[0][1] ; m[0][2]+=a.m[0][2] ; m[0][3]+=a.m[0][3] ;
   m[1][0]+=a.m[1][0] ; m[1][1]+=a.m[1][1] ; m[1][2]+=a.m[1][2] ; m[1][3]+=a.m[1][3] ;
   m[2][0]+=a.m[2][0] ; m[2][1]+=a.m[2][1] ; m[2][2]+=a.m[2][2] ; m[2][3]+=a.m[2][3] ;
   m[3][0]+=a.m[3][0] ; m[3][1]+=a.m[3][1] ; m[3][2]+=a.m[3][2] ; m[3][3]+=a.m[3][3] ;
   return *this;
}

template <class REAL>
inline Matrix4<REAL>& Matrix4<REAL>::operator-= (const Matrix4<REAL>& a)
{
   m[0][0]-=a.m[0][0] ; m[0][1]-=a.m[0][1] ; m[0][2]-=a.m[0][2] ; m[0][3]-=a.m[0][3] ;
   m[1][0]-=a.m[1][0] ; m[1][1]-=a.m[1][1] ; m[1][2]-=a.m[1][2] ; m[1][3]-=a.m[1][3] ;
   m[2][0]-=a.m[2][0] ; m[2][1]-=a.m[2][1] ; m[2][2]-=a.m[2][2] ; m[2][3]-=a.m[2][3] ;
   m[3][0]-=a.m[3][0] ; m[3][1]-=a.m[3][1] ; m[3][2]-=a.m[3][2] ; m[3][3]-=a.m[3][3] ;
   return *this;
}

template <class REAL>
inline Matrix4<REAL>& Matrix4<REAL>::operator*= (const Matrix4<REAL>& a)
{
   Matrix4<REAL> tmp
   ( m[0][0]*a.m[0][0] + m[0][1]*a.m[1][0] + m[0][2]*a.m[2][0] + m[0][3]*a.m[3][0],
     m[0][0]*a.m[0][1] + m[0][1]*a.m[1][1] + m[0][2]*a.m[2][1] + m[0][3]*a.m[3][1],
     m[0][0]*a.m[0][2] + m[0][1]*a.m[1][2] + m[0][2]*a.m[2][2] + m[0][3]*a.m[3][2],
     m[0][0]*a.m[0][3] + m[0][1]*a.m[1][3] + m[0][2]*a.m[2][3] + m[0][3]*a.m[3][3],

     m[1][0]*a.m[0][0] + m[1][1]*a.m[1][0] + m[1][2]*a.m[2][0] + m[1][3]*a.m[3][0],
     m[1][0]*a.m[0][1] + m[1][1]*a.m[1][1] + m[1][2]*a.m[2][1] + m[1][3]*a.m[3][1],
     m[1][0]*a.m[0][2] + m[1][1]*a.m[1][2] + m[1][2]*a.m[2][2] + m[1][3]*a.m[3][2],
     m[1][0]*a.m[0][3] + m[1][1]*a.m[1][3] + m[1][2]*a.m[2][3] + m[1][3]*a.m[3][3],

     m[2][0]*a.m[0][0] + m[2][1]*a.m[1][0] + m[2][2]*a.m[2][0] + m[2][3]*a.m[3][0],
     m[2][0]*a.m[0][1] + m[2][1]*a.m[1][1] + m[2][2]*a.m[2][1] + m[2][3]*a.m[3][1],
     m[2][0]*a.m[0][2] + m[2][1]*a.m[1][2] + m[2][2]*a.m[2][2] + m[2][3]*a.m[3][2],
     m[2][0]*a.m[0][3] + m[2][1]*a.m[1][3] + m[2][2]*a.m[2][3] + m[2][3]*a.m[3][3],

     m[3][0]*a.m[0][0] + m[3][1]*a.m[1][0] + m[3][2]*a.m[2][0] + m[3][3]*a.m[3][0],
     m[3][0]*a.m[0][1] + m[3][1]*a.m[1][1] + m[3][2]*a.m[2][1] + m[3][3]*a.m[3][1],
     m[3][0]*a.m[0][2] + m[3][1]*a.m[1][2] + m[3][2]*a.m[2][2] + m[3][3]*a.m[3][2],
     m[3][0]*a.m[0][3] + m[3][1]*a.m[1][3] + m[3][2]*a.m[2][3] + m[3][3]*a.m[3][3] );

   return ((*this)=tmp);
}

template <class REAL>
inline Matrix4<REAL>& Matrix4<REAL>::operator/= (const Matrix4& a)
{
   m[0][0]/=a.m[0][0] ; m[0][1]/=a.m[0][1] ; m[0][2]/=a.m[0][2] ; m[0][3]/=a.m[0][3] ;
   m[1][0]/=a.m[1][0] ; m[1][1]/=a.m[1][1] ; m[1][2]/=a.m[1][2] ; m[1][3]/=a.m[1][3] ;
   m[2][0]/=a.m[2][0] ; m[2][1]/=a.m[2][1] ; m[2][2]/=a.m[2][2] ; m[2][3]/=a.m[2][3] ;
   m[3][0]/=a.m[3][0] ; m[3][1]/=a.m[3][1] ; m[3][2]/=a.m[3][2] ; m[3][3]/=a.m[3][3] ;
   return *this;
}

template <class REAL>
inline Matrix4<REAL>& Matrix4<REAL>::operator*= (REAL a)
{
   m[0][0]*=a ; m[0][1]*=a ; m[0][2]*=a ; m[0][3]*=a;
   m[1][0]*=a ; m[1][1]*=a ; m[1][2]*=a ; m[1][3]*=a;
   m[2][0]*=a ; m[2][1]*=a ; m[2][2]*=a ; m[2][3]*=a;
   m[3][0]*=a ; m[3][1]*=a ; m[3][2]*=a ; m[3][3]*=a;

   return *this;
}

template <class REAL>
inline Matrix4<REAL> Matrix4<REAL>::operator- () const
{
   return Matrix4<REAL>
   ( -m[0][0] , -m[0][1] , -m[0][2] , -m[0][3] ,
     -m[1][0] , -m[1][1] , -m[1][2] , -m[1][3] ,
     -m[2][0] , -m[2][1] , -m[2][2] , -m[2][3] ,
     -m[3][0] , -m[3][1] , -m[3][2] , -m[3][3] );
}



template <class REAL>
inline bool Matrix4<REAL>::operator== (const Matrix4& a) const
{
   return ( COMPARE(m[0][0], a.m[0][0], EPSILON) &&
	        COMPARE(m[0][1], a.m[0][1], EPSILON) &&
			COMPARE(m[0][2], a.m[0][2], EPSILON) &&
			COMPARE(m[0][3], a.m[0][3], EPSILON) &&

            COMPARE(m[1][0], a.m[1][0], EPSILON) &&
			COMPARE(m[1][1], a.m[1][1], EPSILON) &&
			COMPARE(m[1][2], a.m[1][2], EPSILON) &&
			COMPARE(m[1][3], a.m[1][3], EPSILON) &&

            COMPARE(m[2][0], a.m[2][0], EPSILON) &&
			COMPARE(m[2][1], a.m[2][1], EPSILON) &&
			COMPARE(m[2][2], a.m[2][2], EPSILON) &&
			COMPARE(m[2][3], a.m[2][3], EPSILON) &&

            COMPARE(m[3][0], a.m[3][0], EPSILON) &&
			COMPARE(m[3][1], a.m[3][1], EPSILON) &&
			COMPARE(m[3][2], a.m[3][2], EPSILON) &&
			COMPARE(m[3][3], a.m[3][3], EPSILON) );
}

template <class REAL>
inline bool Matrix4<REAL>::operator!= (const Matrix4& a) const
{
   return ( !COMPARE(m[0][0], a.m[0][0], EPSILON) ||
	        !COMPARE(m[0][1], a.m[0][1], EPSILON) ||
			!COMPARE(m[0][2], a.m[0][2], EPSILON) ||
			!COMPARE(m[0][3], a.m[0][3], EPSILON) ||

            !COMPARE(m[1][0], a.m[1][0], EPSILON) ||
			!COMPARE(m[1][1], a.m[1][1], EPSILON) ||
			!COMPARE(m[1][2], a.m[1][2], EPSILON) ||
			!COMPARE(m[1][3], a.m[1][3], EPSILON) ||

            !COMPARE(m[2][0], a.m[2][0], EPSILON) ||
			!COMPARE(m[2][1], a.m[2][1], EPSILON) ||
			!COMPARE(m[2][2], a.m[2][2], EPSILON) ||
			!COMPARE(m[2][3], a.m[2][3], EPSILON) ||

            !COMPARE(m[3][0], a.m[3][0], EPSILON) ||
			!COMPARE(m[3][1], a.m[3][1], EPSILON) ||
			!COMPARE(m[3][2], a.m[3][2], EPSILON) ||
			!COMPARE(m[3][3], a.m[3][3], EPSILON) );
}



template <class REAL>
inline REAL* Matrix4<REAL>::operator[] (int i)
{
   return (REAL*)(m[i]);
}



template <class REAL>
inline Matrix4<REAL>::operator REAL* ()
{
   return &(m[0][0]);
}


//-- Member functions ---------------------------------------------------------
template <class REAL>
inline void Matrix4<REAL>::add(const Matrix4<REAL>& a, const Matrix4<REAL>& b)
{
   m[0][0] = a.m[0][0] + b.m[0][0];
   m[0][1] = a.m[0][1] + b.m[0][1];
   m[0][2] = a.m[0][2] + b.m[0][2];
   m[0][3] = a.m[0][3] + b.m[0][3];

   m[1][0] = a.m[1][0] + b.m[1][0];
   m[1][1] = a.m[1][1] + b.m[1][1];
   m[1][2] = a.m[1][2] + b.m[1][2];
   m[1][3] = a.m[1][3] + b.m[1][3];

   m[2][0] = a.m[2][0] + b.m[2][0];
   m[2][1] = a.m[2][1] + b.m[2][1];
   m[2][2] = a.m[2][2] + b.m[2][2];
   m[2][3] = a.m[2][3] + b.m[2][3];

   m[3][0] = a.m[3][0] + b.m[3][0];
   m[3][1] = a.m[3][1] + b.m[3][1];
   m[3][2] = a.m[3][2] + b.m[3][2];
   m[3][3] = a.m[3][3] + b.m[3][3];
}

template <class REAL>
inline void Matrix4<REAL>::sub(const Matrix4<REAL>& a, const Matrix4<REAL>& b)
{
   m[0][0] = a.m[0][0] - b.m[0][0];
   m[0][1] = a.m[0][1] - b.m[0][1];
   m[0][2] = a.m[0][2] - b.m[0][2];
   m[0][3] = a.m[0][3] - b.m[0][3];

   m[1][0] = a.m[1][0] - b.m[1][0];
   m[1][1] = a.m[1][1] - b.m[1][1];
   m[1][2] = a.m[1][2] - b.m[1][2];
   m[1][3] = a.m[1][3] - b.m[1][3];

   m[2][0] = a.m[2][0] - b.m[2][0];
   m[2][1] = a.m[2][1] - b.m[2][1];
   m[2][2] = a.m[2][2] - b.m[2][2];
   m[2][3] = a.m[2][3] - b.m[2][3];

   m[3][0] = a.m[3][0] - b.m[3][0];
   m[3][1] = a.m[3][1] - b.m[3][1];
   m[3][2] = a.m[3][2] - b.m[3][2];
   m[3][3] = a.m[3][3] - b.m[3][3];
}

template <class REAL>
inline void Matrix4<REAL>::div(const Matrix4<REAL>& a, const Matrix4<REAL>& b)
{
   m[0][0] = a.m[0][0] / b.m[0][0];
   m[0][1] = a.m[0][1] / b.m[0][1];
   m[0][2] = a.m[0][2] / b.m[0][2];
   m[0][3] = a.m[0][3] / b.m[0][3];

   m[1][0] = a.m[1][0] / b.m[1][0];
   m[1][1] = a.m[1][1] / b.m[1][1];
   m[1][2] = a.m[1][2] / b.m[1][2];
   m[1][3] = a.m[1][3] / b.m[1][3];

   m[2][0] = a.m[2][0] / b.m[2][0];
   m[2][1] = a.m[2][1] / b.m[2][1];
   m[2][2] = a.m[2][2] / b.m[2][2];
   m[2][3] = a.m[2][3] / b.m[2][3];

   m[3][0] = a.m[3][0] / b.m[3][0];
   m[3][1] = a.m[3][1] / b.m[3][1];
   m[3][2] = a.m[3][2] / b.m[3][2];
   m[3][3] = a.m[3][3] / b.m[3][3];
}

template <class REAL>
inline void Matrix4<REAL>::mul(const Matrix4<REAL>& a, const Matrix4<REAL>& b)
{
   m[0][0] = a.m[0][0]*b.m[0][0] + a.m[0][1]*b.m[1][0] + a.m[0][2]*b.m[2][0] + a.m[0][3]*b.m[3][0];
   m[0][1] = a.m[0][0]*b.m[0][1] + a.m[0][1]*b.m[1][1] + a.m[0][2]*b.m[2][1] + a.m[0][3]*b.m[3][1];
   m[0][2] = a.m[0][0]*b.m[0][2] + a.m[0][1]*b.m[1][2] + a.m[0][2]*b.m[2][2] + a.m[0][3]*b.m[3][2];
   m[0][3] = a.m[0][0]*b.m[0][3] + a.m[0][1]*b.m[1][3] + a.m[0][2]*b.m[2][3] + a.m[0][3]*b.m[3][3];

   m[1][0] = a.m[1][0]*b.m[0][0] + a.m[1][1]*b.m[1][0] + a.m[1][2]*b.m[2][0] + a.m[1][3]*b.m[3][0];
   m[1][1] = a.m[1][0]*b.m[0][1] + a.m[1][1]*b.m[1][1] + a.m[1][2]*b.m[2][1] + a.m[1][3]*b.m[3][1];
   m[1][2] = a.m[1][0]*b.m[0][2] + a.m[1][1]*b.m[1][2] + a.m[1][2]*b.m[2][2] + a.m[1][3]*b.m[3][2];
   m[1][3] = a.m[1][0]*b.m[0][3] + a.m[1][1]*b.m[1][3] + a.m[1][2]*b.m[2][3] + a.m[1][3]*b.m[3][3];

   m[2][0] = a.m[2][0]*b.m[0][0] + a.m[2][1]*b.m[1][0] + a.m[2][2]*b.m[2][0] + a.m[2][3]*b.m[3][0];
   m[2][1] = a.m[2][0]*b.m[0][1] + a.m[2][1]*b.m[1][1] + a.m[2][2]*b.m[2][1] + a.m[2][3]*b.m[3][1];
   m[2][2] = a.m[2][0]*b.m[0][2] + a.m[2][1]*b.m[1][2] + a.m[2][2]*b.m[2][2] + a.m[2][3]*b.m[3][2];
   m[2][3] = a.m[2][0]*b.m[0][3] + a.m[2][1]*b.m[1][3] + a.m[2][2]*b.m[2][3] + a.m[2][3]*b.m[3][3];

   m[3][0] = a.m[3][0]*b.m[0][0] + a.m[3][1]*b.m[1][0] + a.m[3][2]*b.m[2][0] + a.m[3][3]*b.m[3][0];
   m[3][1] = a.m[3][0]*b.m[0][1] + a.m[3][1]*b.m[1][1] + a.m[3][2]*b.m[2][1] + a.m[3][3]*b.m[3][1];
   m[3][2] = a.m[3][0]*b.m[0][2] + a.m[3][1]*b.m[1][2] + a.m[3][2]*b.m[2][2] + a.m[3][3]*b.m[3][2];
   m[3][3] = a.m[3][0]*b.m[0][3] + a.m[3][1]*b.m[1][3] + a.m[3][2]*b.m[2][3] + a.m[3][3]*b.m[3][3];
}


template <class REAL>
inline void Matrix4<REAL>::mul(REAL a, const Matrix4& M)
{
   m[0][0] = a*M.m[0][0]  ;  m[0][1] = a*M.m[0][1]  ;  m[0][2] = a*M.m[0][2]  ;  m[0][3] = a*M.m[0][3];
   m[1][0] = a*M.m[1][0]  ;  m[1][1] = a*M.m[1][1]  ;  m[1][2] = a*M.m[1][2]  ;  m[1][3] = a*M.m[1][3];
   m[2][0] = a*M.m[2][0]  ;  m[2][1] = a*M.m[2][1]  ;  m[2][2] = a*M.m[2][2]  ;  m[2][3] = a*M.m[2][3];
   m[3][0] = a*M.m[3][0]  ;  m[3][1] = a*M.m[3][1]  ;  m[3][2] = a*M.m[2][2]  ;  m[3][3] = a*M.m[3][3];
}

template <class REAL>
inline void Matrix4<REAL>::mul(const Matrix4& M, REAL a)
{
   m[0][0] = a*M.m[0][0]  ;  m[0][1] = a*M.m[0][1]  ;  m[0][2] = a*M.m[0][2]  ;  m[0][3] = a*M.m[0][3];
   m[1][0] = a*M.m[1][0]  ;  m[1][1] = a*M.m[1][1]  ;  m[1][2] = a*M.m[1][2]  ;  m[1][3] = a*M.m[1][3];
   m[2][0] = a*M.m[2][0]  ;  m[2][1] = a*M.m[2][1]  ;  m[2][2] = a*M.m[2][2]  ;  m[2][3] = a*M.m[2][3];
   m[3][0] = a*M.m[3][0]  ;  m[3][1] = a*M.m[3][1]  ;  m[3][2] = a*M.m[2][2]  ;  m[3][3] = a*M.m[3][3];
}

template <class REAL>
inline void Matrix4<REAL>::compMul(const Matrix4& a, const Matrix4& b)
{
   m[0][0] = a.m[0][0]*b.m[0][0]  ;  m[0][1] = a.m[0][1]*b.m[0][1]  ;  m[0][2] = a.m[0][2]*b.m[0][2]  ;  m[0][3] = a.m[0][3]*b.m[0][3];
   m[1][0] = a.m[1][0]*b.m[1][0]  ;  m[1][1] = a.m[1][1]*b.m[1][1]  ;  m[1][2] = a.m[1][2]*b.m[1][2]  ;  m[1][3] = a.m[1][3]*b.m[1][3];
   m[2][0] = a.m[2][0]*b.m[2][0]  ;  m[2][1] = a.m[2][1]*b.m[2][1]  ;  m[2][2] = a.m[2][2]*b.m[2][2]  ;  m[2][3] = a.m[2][3]*b.m[2][3];
   m[3][0] = a.m[3][0]*b.m[3][0]  ;  m[3][1] = a.m[3][1]*b.m[3][1]  ;  m[3][2] = a.m[3][2]*b.m[3][2]  ;  m[3][3] = a.m[3][3]*b.m[3][3];
}

template <class REAL>
inline void Matrix4<REAL>::transpose()
{
	REAL t = m[0][1]  ;  m[0][1] = m[1][0]  ;  m[1][0] = t;
	     t = m[0][2]  ;  m[0][2] = m[2][0]  ;  m[2][0] = t;
	     t = m[0][3]  ;  m[0][3] = m[3][0]  ;  m[3][0] = t;
	     t = m[1][2]  ;  m[1][2] = m[2][1]  ;  m[2][1] = t;
	     t = m[1][3]  ;  m[1][3] = m[3][1]  ;  m[3][1] = t;
	     t = m[2][3]  ;  m[2][3] = m[3][2]  ;  m[3][2] = t;

//    return Matrix4<REAL>( m[0][0] , m[1][0] , m[2][0] ,
//                          m[0][1] , m[1][1] , m[2][1] ,
//                          m[0][2] , m[1][2] , m[2][2] );
}

template <class REAL>
inline void Matrix4<REAL>::inverse()
{
	//TODO//
}

template <class REAL>
inline void Matrix4<REAL>::orthonormalize()
{
	//TODO//
}



//-- Non-member operators ---------------------------------------------------------
template <class REAL>
inline Matrix4<REAL> operator* (REAL a, const Matrix4<REAL>& m)
{
   return Matrix4<REAL>
   ( m.m[0][0]*a , m.m[0][1]*a , m.m[0][2]*a , m.m[0][3]*a ,
     m.m[1][0]*a , m.m[1][1]*a , m.m[1][2]*a , m.m[1][3]*a ,
     m.m[2][0]*a , m.m[2][1]*a , m.m[2][2]*a , m.m[2][3]*a ,
     m.m[3][0]*a , m.m[3][1]*a , m.m[3][2]*a , m.m[3][3]*a );
}

template <class REAL>
inline std::ostream& operator<< (std::ostream& s, const Matrix4<REAL>& m)
{
   return s
   << '[' << m.m[0][0] << " , " << m.m[0][1] << " , "  << m.m[0][2] << " , "  << m.m[0][3] << "]\n"
   << '[' << m.m[1][0] << " , " << m.m[1][1] << " , "  << m.m[1][2] << " , "  << m.m[1][3] << "]\n"
   << '[' << m.m[2][0] << " , " << m.m[2][1] << " , "  << m.m[2][2] << " , "  << m.m[2][3] << "]\n"
   << '[' << m.m[3][0] << " , " << m.m[3][1] << " , "  << m.m[3][2] << " , "  << m.m[3][3] << "]\n";
}



//-- Non-member functions ---------------------------------------------------------
template <class REAL>
inline REAL determinant(const Matrix4<REAL>& M)
{
   //TODO//
	return 1.0;
}

template <class REAL>
inline Matrix4<REAL> transpose(const Matrix4<REAL>& m)
{
   return Matrix4<REAL>( m.m[0][0] , m.m[1][0] , m.m[2][0] , m.m[3][0] ,
                         m.m[0][1] , m.m[1][1] , m.m[2][1] , m.m[3][1] ,
                         m.m[0][2] , m.m[1][2] , m.m[2][2] , m.m[3][2] ,
                         m.m[0][3] , m.m[1][3] , m.m[2][3] , m.m[3][3] );
}

template <class REAL>
inline Matrix4<REAL> inverse(const Matrix4<REAL>& M)
{
   //TODO//
	return Matrix4<REAL>::IDENTITY;
}

template <class REAL>
inline Matrix4<REAL> orthonormalize(const Matrix4<REAL>& M)
{
   //TODO//
	return Matrix4<REAL>::IDENTITY;
}




















/*
template <class REAL>
inline void Matrix4<REAL>::eulerTransform(REAL h, REAL p, REAL r)
{
   //
   //          | cos(r)cos(h)-sin(r)sin(p)sin(h)  -sin(r)cos(p)  cos(r)sin(h)+sin(r)sin(p)cos(h) |
   // E(h,p,r)=| sin(r)cos(h)+cos(r)sin(p)sin(h)   cos(r)cos(p)  sin(r)sin(h)-cos(r)sin(p)cos(h) |
   //          |-cos(p)sin(h),                     sin(p),       cos(p)cos(h)                    |
   //

   m[0][0]=cos(r)*cos(h) - sin(r)*sin(p)*sin(h);
   m[0][1]=-sin(r)*cos(p);
   m[0][2]=cos(r)*sin(h) + sin(r)*sin(p)*cos(h);

   m[1][0]=sin(r)*cos(h) + cos(r)*sin(p)*sin(h);
   m[1][1]=cos(r)*cos(p);
   m[1][2]=sin(r)*sin(h) - cos(r)*sin(p)*cos(h);

   m[2][0]=-cos(p)*sin(h);
   m[2][1]=sin(p);
   m[2][2]=cos(p)*cos(h);
}
//--------------------------------------------------------------------------//
*/
