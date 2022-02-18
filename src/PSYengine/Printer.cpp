
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

#include "PSYGEN/PSYengine/Printer.hpp"
#include "PSYGEN/PSYengine/Attribute.hpp"
#include "PSYGEN/PSYengine/Geometry.hpp"
#include "PSYGEN/PSYengine/Node.hpp"
#include "PSYGEN/PSYmath/Vector4.hpp"

#define IDENT(id) for (int i=0; i<(id)*4; i++) putchar(' ');

namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{

void Printer::inspect(Node* opNode)
{
    IDENT(ident); printf("node: \"%s\" - type: %s - state: %s\n", opNode->get_name(), opNode->get_type(), opNode->get_state_name());
    IDENT(ident); printf("{\n");
    ident++;
    IDENT(ident); printf("local position = (%f , %f , %f)\n", opNode->local.getTranslate().x, opNode->local.getTranslate().y, opNode->local.getTranslate().z );
    IDENT(ident); printf("world position = (%f , %f , %f)\n", opNode->world.getTranslate().x, opNode->world.getTranslate().y, opNode->world.getTranslate().z );
    IDENT(ident); printf("bound.pos = (%f , %f , %f) bound.rad = %f\n", opNode->world_bound.pos.x, opNode->world_bound.pos.y, opNode->world_bound.pos.z, opNode->world_bound.rad );

    if ( opNode->get_parent() )
    {
        IDENT(ident); printf("parent: %s\n", opNode->get_parent()->get_name());
    }

    for (std::list<Attribute*>::iterator attr=opNode->get_attribute_list().begin(); attr != opNode->get_attribute_list().end(); ++attr)
    {
        IDENT(ident); printf("attr: %s - type: %s - state: %s\n", (*attr)->get_name(), (*attr)->get_type(), (*attr)->get_state_name());
        IDENT(ident); printf("{\n");
        bool next = (*attr)->begin_parameter();
        while ( next )
        {
            IDENT(ident+1); printf("parameter: %s %s = ", (*attr)->get_current_parameter_typename(),
                                                          (*attr)->get_current_parameter_name() );
            switch ( (*attr)->get_current_parameter_type() )
            {
                case Parameter::INT:    std::cout << *(static_cast<int*>   ( (*attr)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::FLOAT:  std::cout << *(static_cast<float*> ( (*attr)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::VEC3:   std::cout << *(static_cast<vec3*>  ( (*attr)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::VEC4:   std::cout << *(static_cast<vec4*>  ( (*attr)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::MAT3:   std::cout << *(static_cast<mat3*>  ( (*attr)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::STRING: std::cout << *(static_cast<std::string*>  ( (*attr)->get_current_parameter_value() )) << std::endl; break;
            }
            next = (*attr)->next_parameter();
        }
        IDENT(ident); printf("}\n");
    }

    for (std::list<Geometry*>::iterator geom=opNode->get_geometry_list().begin(); geom != opNode->get_geometry_list().end(); ++geom)
    {
        IDENT(ident); printf("geom: %s - type: %s - state: %s\n", (*geom)->get_name(), (*geom)->get_type(), (*geom)->get_state_name());
        IDENT(ident); printf("{\n");
        bool next = (*geom)->begin_parameter();
        while ( next )
        {
            IDENT(ident+1); printf("parameter: %s %s = ", (*geom)->get_current_parameter_typename(),
                                                          (*geom)->get_current_parameter_name() );
            switch ( (*geom)->get_current_parameter_type() )
            {
                case Parameter::INT:    std::cout << *(static_cast<int*>   ( (*geom)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::FLOAT:  std::cout << *(static_cast<float*> ( (*geom)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::VEC3:   std::cout << *(static_cast<vec3*>  ( (*geom)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::VEC4:   std::cout << *(static_cast<vec4*>  ( (*geom)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::MAT3:   std::cout << *(static_cast<mat3*>  ( (*geom)->get_current_parameter_value() )) << std::endl; break;
                case Parameter::STRING: std::cout << *(static_cast<std::string*>  ( (*geom)->get_current_parameter_value() )) << std::endl; break;
            }
            next = (*geom)->next_parameter();
        }
        IDENT(ident); printf("}\n");
    }

    opNode->accept(this);
    ident--;
    IDENT(ident); printf("}\n");
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
