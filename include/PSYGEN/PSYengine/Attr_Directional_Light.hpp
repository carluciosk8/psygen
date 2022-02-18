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
#ifndef __PSYGEN_ATTR_DIRECTIONAL_LIGHT_H__
#define __PSYGEN_ATTR_DIRECTIONAL_LIGHT_H__

#include "PSYGEN/PSYengine/Attribute.hpp"
#include "PSYGEN/PSYmath/Vector4.hpp"
#include "PSYGEN/PSYmath/Vector3.hpp"

namespace psy{/////////////////////////////////////////////////////////////////


class Attr_Directional_Light : public Attribute
{
public:
    /// Procedural generation and collapse
    ///
    virtual void amplify (Mutex*);
    virtual void shrink  (Mutex*);

    /// Generation time and memory usage estimation
    ///
    virtual float estimate_mem_usage  ();
    virtual float        estimate_time_usage ();

    /// OpenGL rendering commands here
    virtual void enable  ();
    virtual void disable ();

PSYGEN_DECLARE_PARAMETERS(Attr_Directional_Light):
    vec4  specular;
    vec4  ambient;
    vec4  diffuse;
    vec4  direction;
};


}//////////////////////////////////////////////////////////////////////////////

#endif //__PSYGEN_ATTR_DIRECTIONAL_LIGHT_H__
