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

#include "PSYGEN/PSYengine/Attr_Fog.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Attr_Fog, Attribute)
{
    m_sys_memory_use = sizeof(*this);

    bind_parameter2(Parameter::INT,   "mode",    &mode,    GL_EXP);
    bind_parameter2(Parameter::VEC4,  "color",   &color,   vec4(0.5, 0.5, 0.5, 1.0));
    bind_parameter2(Parameter::FLOAT, "density", &density, 0.0f);
    bind_parameter2(Parameter::FLOAT, "start",   &start,   0.0f);
    bind_parameter2(Parameter::FLOAT, "end",     &end,     0.0f);
}



void Attr_Fog::amplify(Mutex* mutex)
{
    //if (m_eState == SHRINKED)
    //{
    //std::cout << "amplify Attr_Directional_Light: name = \"" << get_name() << "\"" << std::endl;
    if (mutex) mutex->lock();
    m_eState = AMPLIFIED;
    if (mutex) mutex->unlock();
    //}
}



void Attr_Fog::shrink(Mutex* mutex)
{
    //if (m_eState == AMPLIFIED)
    //{
    //std::cout << "shrink Attr_Directional_Light: name = \"" << get_name() << "\"" << std::endl;
    if (mutex) mutex->lock();
    m_eState = SHRINKED;
    if (mutex) mutex->unlock();
    //}
}



float Attr_Fog::estimate_mem_usage()
{
    return 0.0f;
}



float Attr_Fog::estimate_time_usage()
{
    return 0.0f;
}



void Attr_Fog::enable()
{
    glFogi(GL_FOG_MODE, mode);
    glFogfv(GL_FOG_COLOR, color);
    glFogf(GL_FOG_DENSITY, density);
    glFogf(GL_FOG_START, start);
    glFogf(GL_FOG_END, end);
    glHint(GL_FOG_HINT, GL_DONT_CARE);

    glEnable(GL_FOG);
}



void Attr_Fog::disable()
{
    glDisable(GL_FOG);
}


}//////////////////////////////////////////////////////////////////////////////
