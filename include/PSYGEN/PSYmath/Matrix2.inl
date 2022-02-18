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
inline Matrix2<REAL>::Matrix2()
{}

template <class REAL>
inline Matrix2<REAL>::Matrix2(REAL m00, REAL m01,
                              REAL m10, REAL m11)
{
   m[0][0]=m00  ;  m[0][1]=m01;
   m[1][0]=m10  ;  m[1][1]=m11;
}

template <class REAL>
inline Matrix2<REAL>::Matrix2(REAL* a)
{
   memcpy(this, a, 4*sizeof(REAL));
}



//-- operators ------------------------------------------------------------//
template <class REAL>
inline Matrix2<REAL> Matrix2<REAL>::operator+(const Matrix2<REAL>& M) const
{
   return Matrix2<REAL>(m[0][0] + M.m[0][0]  ,  m[0][1] + M.m[0][1] ,
                        m[1][0] + M.m[1][0]  ,  m[1][1] + M.m[1][1] );
}

template <class REAL>
inline Matrix2<REAL> Matrix2<REAL>::operator-(const Matrix2<REAL>& M) const
{
   return Matrix2<REAL>(m[0][0] - M.m[0][0]  ,  m[0][1] - M.m[0][1] ,
                        m[1][0] - M.m[1][0]  ,  m[1][1] - M.m[1][1] );
}

template <class REAL>
inline Matrix2<REAL> Matrix2<REAL>::operator*(const Matrix2<REAL>& M) const
{
   return Matrix2(m[0][0]*M.m[0][0] + m[0][1]*M.m[1][0]  ,  m[0][0]*M.m[0][1] + m[0][1]*M.m[1][1],
                  m[1][0]*M.m[0][0] + m[1][1]*M.m[1][0]  ,  m[1][0]*M.m[0][1] + m[1][1]*M.m[1][1]);
}

template <class REAL>
inline Matrix2<REAL> Matrix2<REAL>::operator/(const Matrix2<REAL>& M) const
{
   return Matrix2<REAL>(m[0][0] / M.m[0][0]  ,  m[0][1] / M.m[0][1] ,
                        m[1][0] / M.m[1][0]  ,  m[1][1] / M.m[1][1] );
}

template <class REAL>
inline Matrix2<REAL> Matrix2<REAL>::operator* (REAL a) const
{
   return Matrix2<REAL>(m[0][0]*a  ,  m[0][1]*a,
                        m[1][0]*a  ,  m[1][1]*a);
}



template <class REAL>
inline Matrix2<REAL>& Matrix2<REAL>::operator+= (const Matrix2<REAL>& M)
{
   m[0][0]+=M.m[0][0] ; m[0][1]+=M.m[0][1] ;
   m[1][0]+=M.m[1][0] ; m[1][1]+=M.m[1][1] ;
   return *this;
}

template <class REAL>
inline Matrix2<REAL>& Matrix2<REAL>::operator-= (const Matrix2<REAL>& M)
{
   m[0][0]-=M.m[0][0];   m[0][1]-=M.m[0][1];
   m[1][0]-=M.m[1][0];   m[1][1]-=M.m[1][1];
   return *this;
}

template <class REAL>
inline Matrix2<REAL>& Matrix2<REAL>::operator*=(const Matrix2<REAL>& M)
{
   Matrix2 tmp(m[0][0]*M.m[0][0] + m[0][1]*M.m[1][0]  ,  m[0][0]*M.m[0][1] + m[0][1]*M.m[1][1],
               m[1][0]*M.m[0][0] + m[1][1]*M.m[1][0]  ,  m[1][0]*M.m[0][1] + m[1][1]*M.m[1][1]);

   return ((*this)=tmp);
}

template <class REAL>
inline Matrix2<REAL>& Matrix2<REAL>::operator/=(const Matrix2<REAL>& M)
{
   m[0][0]/=M.m[0][0]  ;  m[0][1]/=M.m[0][1];
   m[1][0]/=M.m[1][0]  ;  m[1][1]/=M.m[1][1];
   return *this;
}

template <class REAL>
inline Matrix2<REAL>& Matrix2<REAL>::operator*=(REAL a)
{
   m[0][0]*=a  ;  m[0][1]*=a;
   m[1][0]*=a  ;  m[1][1]*=a;
   return *this;
}



template <class REAL>
inline Matrix2<REAL> Matrix2<REAL>::operator-() const
{
   return Matrix2<REAL>(-m[0][0]  ,  -m[0][1]
                        -m[1][0]  ,  -m[1][1]);
}



template <class REAL>
inline bool Matrix2<REAL>::operator== (const Matrix2<REAL>& a) const
{
    return (
        fuzzy_eq(m[0][0], a.m[0][0] ) && fuzzy_eq(m[0][1], a.m[0][1] ) &&
        fuzzy_eq(m[1][0], a.m[1][0] ) && fuzzy_eq(m[1][1], a.m[1][1] ) );
}

template <class REAL>
inline bool Matrix2<REAL>::operator!= (const Matrix2<REAL>& a) const
{
    return (
        !fuzzy_eq(m[0][0], a.m[0][0] ) || !fuzzy_eq(m[0][1], a.m[0][1] ) ||
        !fuzzy_eq(m[1][0], a.m[1][0] ) || !fuzzy_eq(m[1][1], a.m[1][1] ) );
}



template <class REAL>
inline REAL* Matrix2<REAL>::operator[] (int i)
{
   return (REAL*)(m[i]);
}



//-- Member functions ---------------------------------------------------------
template <class REAL>
inline void Matrix2<REAL>::add(const Matrix2<REAL>& a, const Matrix2<REAL>& b)
{
   m[0][0] = a.m[0][0]+b.m[0][0]  ;  m[0][1]=a.m[0][1]+b.m[0][1];
   m[1][0] = a.m[1][0]+b.m[1][0]  ;  m[1][1]=a.m[1][1]+b.m[1][1];
}



template <class REAL>
inline void Matrix2<REAL>::sub(const Matrix2<REAL>& a, const Matrix2<REAL>& b)
{
   m[0][0] = a.m[0][0]-b.m[0][0]  ;  m[0][1] = a.m[0][1]-b.m[0][1];
   m[1][0] = a.m[1][0]-b.m[1][0]  ;  m[1][1] = a.m[1][1]-b.m[1][1];
}

template <class REAL>
inline void Matrix2<REAL>::div(const Matrix2<REAL>& a, const Matrix2<REAL>& b)
{
   m[0][0] = a.m[0][0]/b.m[0][0]  ;  m[0][1] = a.m[0][1]/b.m[0][1];
   m[1][0] = a.m[1][0]/b.m[1][0]  ;  m[1][1] = a.m[1][1]/b.m[1][1];
}

template <class REAL>
inline void Matrix2<REAL>::mul(const Matrix2<REAL>& a, const Matrix2<REAL>& b)
{
   m[0][0] = a.m[0][0]*b.m[0][0] + a.m[0][1]*b.m[1][0];
   m[0][1] = a.m[0][0]*b.m[0][1] + a.m[0][1]*b.m[1][1];

   m[1][0] = a.m[1][0]*b.m[0][0] + a.m[1][1]*b.m[1][0];
   m[1][1] = a.m[1][0]*b.m[0][1] + a.m[1][1]*b.m[1][1];
}

template <class REAL>
inline void Matrix2<REAL>::mul(REAL a, const Matrix2& M)
{
   m[0][0] = a*M.m[0][0]  ;  m[0][1] = a*M.m[0][1];
   m[1][0] = a*M.m[1][0]  ;  m[1][1] = a*M.m[1][1];
}

template <class REAL>
inline void Matrix2<REAL>::mul(const Matrix2& M, REAL a)
{
   m[0][0] = a*M.m[0][0]  ;  m[0][1] = a*M.m[0][1];
   m[1][0] = a*M.m[1][0]  ;  m[1][1] = a*M.m[1][1];
}

template <class REAL>
inline void Matrix2<REAL>::compMul(const Matrix2<REAL>& a, const Matrix2<REAL>& b)
{
   m[0][0] = a.m[0][0]*b.m[0][0]  ;  m[0][1] = a.m[0][1]/b.m[0][1];
   m[1][0] = a.m[1][0]*b.m[1][0]  ;  m[1][1] = a.m[1][1]/b.m[1][1];
}

template <class REAL>
inline void Matrix2<REAL>::transpose()
{
   REAL t = m[0][1]  ;  m[0][1] = m[1][0]  ;  m[1][0] = t;
}

template <class REAL>
inline void Matrix2<REAL>::inverse()
{
	//TODO//
	m[0][1] = -m[0][1];
	m[1][0] = -m[1][0];
    REAL t = m[0][0]  ;  m[0][0] = m[1][1]  ;  m[1][1] = t;
}

template <class REAL>
inline void Matrix2<REAL>::orthonormalize()
{
	//TODO//
}



//-- Non-member operators ---------------------------------------------------------
template <class REAL>
inline Matrix2<REAL> operator* (REAL a, const Matrix2<REAL>& m)
{
   return Matrix2<REAL>(a*m.m[0][0]  ,  a*m.m[0][1],
                        a*m.m[1][0]  ,  a*m.m[1][1]);
}

template <class REAL>
inline std::ostream& operator<< (std::ostream& s, const Matrix2<REAL>& m)
{
   return s << '[' << m.m[0][0] << " , " << m.m[0][1] << "]\n"
            << '[' << m.m[1][0] << " , " << m.m[1][1] << "]\n";
}



//-- Non-member functions ---------------------------------------------------------
template <class REAL>
inline REAL determinant(const Matrix2<REAL>& M)
{
   return ( M.m[0][0]*M.m[1][1] - M.m[0][1]*M.m[1][0] );
}

template <class REAL>
inline Matrix2<REAL> transpose(const Matrix2<REAL>& M)
{
   return Matrix2<REAL>(M.m[0][0] , M.m[1][0],
	                    M.m[0][1] , M.m[1][1]);
}

template <class REAL>
inline Matrix2<REAL> inverse(const Matrix2<REAL>& M)
{
   float d = 1.0/(M.m[0][0]*M.m[1][1] - M.m[0][1]*M.m[1][0]);
   return Matrix2<REAL>(d*M.m[1][1] , d*M.m[1][0],
	                    d*M.m[1][0] , d*M.m[1][1]);
}

template <class REAL>
inline Matrix2<REAL> orthonormalize(const Matrix2<REAL>& M)
{
   //TODO//
	return Matrix2<REAL>::IDENTITY;
}
