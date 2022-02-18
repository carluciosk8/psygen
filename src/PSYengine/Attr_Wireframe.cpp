/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2008 by Carlucio Santos Cordeiro
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
    *  \ingroup $GROUP$
    *
    *//***********************************************************************/

#include <GL/gl.h>

#include "PSYGEN/PSYengine/Attr_Wireframe.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Attr_Wireframe, Attribute)
{
    m_sys_memory_use = sizeof(*this);
}



void Attr_Wireframe::amplify(Mutex*)
{
    if (m_eState == SHRINKED)
    {
        //std::cout << "amplify Attr_Wireframe: name = \"" << get_name() << "\"" << std::endl;

        //empty

        m_eState = AMPLIFIED;
    }
}



void Attr_Wireframe::shrink(Mutex*)
{
    if (m_eState == AMPLIFIED)
    {
        //std::cout << "shrink Attr_Wireframe: name = \"" << get_name() << "\"" << std::endl;

        //empty

        m_eState = SHRINKED;
    }
}



float Attr_Wireframe::estimate_mem_usage()
{
    return 0.0f;
}



float Attr_Wireframe::estimate_time_usage()
{
    return 0.0f;
}



void Attr_Wireframe::enable()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}



void Attr_Wireframe::disable()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


}//////////////////////////////////////////////////////////////////////////////
