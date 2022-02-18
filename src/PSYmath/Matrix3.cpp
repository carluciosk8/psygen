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
#include "PSYGEN/PSYmath/Matrix3.hpp"


namespace psy
{



template <> const mat3 mat3::ZERO( 0.0f , 0.0f , 0.0f ,
                                   0.0f , 0.0f , 0.0f ,
                                   0.0f , 0.0f , 0.0f );

template <> const dmat3 dmat3::ZERO( 0.0 , 0.0 , 0.0 ,
                                     0.0 , 0.0 , 0.0 ,
                                     0.0 , 0.0 , 0.0 );



template <> const mat3 mat3::IDENTITY( 1.0f , 0.0f , 0.0f ,
                                       0.0f , 1.0f , 0.0f ,
                                       0.0f , 0.0f , 1.0f );

template <> const dmat3 dmat3::IDENTITY( 1.0 , 0.0 , 0.0 ,
                                         0.0 , 1.0 , 0.0 ,
                                         0.0 , 0.0 , 1.0 );



}
