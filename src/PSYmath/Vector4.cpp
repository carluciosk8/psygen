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
#include "PSYGEN/PSYmath/Vector4.hpp"


namespace psy {



template <> const vec4 vec4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
template <> const vec4 vec4::UX(1.0f, 0.0f, 0.0f, 0.0f);
template <> const vec4 vec4::UY(0.0f, 1.0f, 0.0f, 0.0f);
template <> const vec4 vec4::UZ(0.0f, 0.0f, 1.0f, 0.0f);
template <> const vec4 vec4::UW(0.0f, 0.0f, 0.0f, 1.0f);

template <> const dvec4 dvec4::ZERO(0.0, 0.0, 0.0, 0.0);
template <> const dvec4 dvec4::UX(1.0, 0.0, 0.0, 0.0);
template <> const dvec4 dvec4::UY(0.0, 1.0, 0.0, 0.0);
template <> const dvec4 dvec4::UZ(0.0, 0.0, 1.0, 0.0);
template <> const dvec4 dvec4::UW(0.0, 0.0, 0.0, 1.0);

template <> const ivec4 ivec4::ZERO(0, 0, 0, 0);
template <> const ivec4 ivec4::UX(1, 0, 0, 0);
template <> const ivec4 ivec4::UY(0, 1, 0, 0);
template <> const ivec4 ivec4::UZ(0, 0, 1, 0);
template <> const ivec4 ivec4::UW(0, 0, 0, 1);



}
