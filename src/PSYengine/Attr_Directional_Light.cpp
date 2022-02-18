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

#include "PSYGEN/PSYengine/Attr_Directional_Light.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Attr_Directional_Light, Attribute)
{
    m_sys_memory_use = sizeof(*this);

    bind_parameter2(Parameter::VEC4, "specular", &specular, vec4::ZERO);
    bind_parameter2(Parameter::VEC4, "ambient", &ambient, vec4::ZERO);
    bind_parameter2(Parameter::VEC4, "diffuse", &diffuse, vec4::ZERO);
    bind_parameter2(Parameter::VEC4, "direction", &direction, vec4::ZERO);
}



void Attr_Directional_Light::amplify(Mutex* mutex)
{
    //if (m_eState == SHRINKED)
    //{
        //std::cout << "amplify Attr_Directional_Light: name = \"" << get_name() << "\"" << std::endl;
        if (mutex) mutex->lock();
        m_eState = AMPLIFIED;
        if (mutex) mutex->unlock();
    //}
}



void Attr_Directional_Light::shrink(Mutex* mutex)
{
    //if (m_eState == AMPLIFIED)
    //{
        //std::cout << "shrink Attr_Directional_Light: name = \"" << get_name() << "\"" << std::endl;
        if (mutex) mutex->lock();
        m_eState = SHRINKED;
        if (mutex) mutex->unlock();
    //}
}



float Attr_Directional_Light::estimate_mem_usage()
{
    return 0.0f;
}



float Attr_Directional_Light::estimate_time_usage()
{
    return 0.0f;
}



void Attr_Directional_Light::enable()
{
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, direction);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}



void Attr_Directional_Light::disable()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}


}//////////////////////////////////////////////////////////////////////////////
