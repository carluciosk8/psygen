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
    *  \ingroup PSYmath
    *
    *//***********************************************************************/
#include "PSYGEN/PSYmath/Vector3.hpp"


namespace psy {



template <> PSYAPI const vec3 vec3::ZERO(0.0f,0.0f,0.0f);
template <> PSYAPI const vec3 vec3::UX(1.0f,0.0f,0.0f);
template <> PSYAPI const vec3 vec3::UY(0.0f,1.0f,0.0f);
template <> PSYAPI const vec3 vec3::UZ(0.0f,0.0f,1.0f);

template <> PSYAPI const dvec3 dvec3::ZERO(0.0, 0.0, 0.0);
template <> PSYAPI const dvec3 dvec3::UX(1.0, 0.0, 0.0);
template <> PSYAPI const dvec3 dvec3::UY(0.0, 1.0, 0.0);
template <> PSYAPI const dvec3 dvec3::UZ(0.0, 0.0, 1.0);

template <> PSYAPI const ivec3 ivec3::ZERO(0, 0, 0);
template <> PSYAPI const ivec3 ivec3::UX(1, 0, 0);
template <> PSYAPI const ivec3 ivec3::UY(0, 1, 0);
template <> PSYAPI const ivec3 ivec3::UZ(0, 0, 1);

// template <> PSYAPI const color32 color32::BLACK(0, 0, 0);
// template <> PSYAPI const color32 color32::RED(1, 0, 0);
// template <> PSYAPI const color32 color32::GREEN(0, 1, 0);
// template <> PSYAPI const color32 color32::BLUE(0, 0, 1);
// template <> PSYAPI const color32 color32::WHITE(0, 0, 1);



}
