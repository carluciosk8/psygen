
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
    *  \brief
    *  \ingroup PSYengine
    *
    *//*******************************************************************************************/

#include <GL/gl.h>

#include "PSYGEN/PSYengine/Renderer.hpp"
#include "PSYGEN/PSYengine/Attribute.hpp"
#include "PSYGEN/PSYengine/Geometry.hpp"
#include "PSYGEN/PSYengine/Node.hpp"
#include "PSYGEN/PSYengine/Main_Window.hpp"

#define IDENT(id) for (int i=0; i<id; i++) putchar(' ');

namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{

void Renderer::inspect(Node* opNode)
{
    if ( (opNode->get_state() == Object::AMPLIFIED) && m_npCamera->bound_is_visible(opNode->world_bound) )
    {
        glLoadMatrixf(m_mGLview);
        opNode->world.makeGLmodel(m_mGLmodel);
        glMultMatrixf(m_mGLmodel);

        for ( std::list<Attribute*>::iterator
        attr  = opNode->get_attribute_list().begin();
        attr != opNode->get_attribute_list().end();
        ++attr)
            if ( (*attr)->get_state() == Object::AMPLIFIED )
                (*attr)->enable();

        for ( std::list<Geometry*>::iterator
        geom  = opNode->get_geometry_list().begin();
        geom != opNode->get_geometry_list().end();
        ++geom)
            if ( ((*geom)->get_state() == Object::AMPLIFIED) /*&& m_npCamera->bound_is_visible((*geom)->world_bound)*/ )
                (*geom)->draw();

        opNode->accept(this);

        for ( std::list<Attribute*>::iterator
        attr  = opNode->get_attribute_list().begin();
        attr != opNode->get_attribute_list().end();
        ++attr)
            if ( (*attr)->get_state() == Object::AMPLIFIED )
                (*attr)->disable();
    }
}


void Bound_Renderer::inspect(Node* opNode)
{
    if ( m_npCamera->bound_is_visible(opNode->world_bound) )
    {
        glLoadMatrixf(m_mGLview);
        opNode->world_bound.draw();

    //     for (std::list<Geometry*>::iterator i=opNode->get_geometry_list().begin(); i != opNode->get_geometry_list().end(); ++i)
    //     {
    //         Bound geom_world_bound = (*i)->local_bound;
    //         geom_world_bound.transform_by(opNode->world);
    //         geom_world_bound.draw();
    //     }

        opNode->accept(this);
    }
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
