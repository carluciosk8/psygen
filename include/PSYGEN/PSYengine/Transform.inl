/**************************************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
    email:      carlucio@gmail.com

    This file is part of PSYGEN

    PSYGEN is free software: you can redistribute it and/or modify it under the terms of the GNU
    Lesser General Public License as published by the Free Software Foundation, either version 3
    of the License, or (at your option) any later version.

    PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
    even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with PSYGEN.
    If not, see <http://www.gnu.org/licenses/>

---------------------------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief  __________
    *  \ingroup  PSYengine
    *
    *//*******************************************************************************************/
#ifndef __PSYGEN_TRANSFORM_INL__
#define __PSYGEN_TRANSFORM_INL__


namespace psy {////////////////////////////////////////////////////////////////////////////////////

inline mat3& Transform::getRotate()
{
	return m_mRotate;
}

inline const vec3& Transform::getTranslate() const
{
	return m_vTranslate;
}

inline float Transform::getScale() const
{
	return m_fScale;
}

inline void Transform::setPos(const vec3& p)
{
	m_vTranslate = p;
}

inline void Transform::setPos(float x, float y, float z)
{
	m_vTranslate.x = x  ;  m_vTranslate.y = y  ;  m_vTranslate.z = z  ;
}

inline void Transform::setScale(float s)
{
	m_fScale = s;
}

}//////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_TRANSFORM_INL__
