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

#include "PSYGEN/PSYengine/Updater.hpp"
#include "PSYGEN/PSYengine/Attribute.hpp"
#include "PSYGEN/PSYengine/Geometry.hpp"
#include "PSYGEN/PSYengine/Node.hpp"

namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{


void Updater::update(Node* node)
{
    found_first_bound = false;
    inspect(node);
    node->propagate_bound_to_root();
}



void Updater::inspect(Node* node)
{
    found_first_bound = false;
    if (node->get_parent())
        node->world.product(node->get_parent()->world, node->local);
    else
        node->world = node->local;

    node->accept(this);

    node->update_geometry_list();
    node->update_bound();

    for (std::list<Geometry*>::iterator geom = node->get_geometry_list().begin(); geom != node->get_geometry_list().end(); ++geom)
    {
        if (found_first_bound)
        {
            node->world_bound.merge((*geom)->world_bound);
        }
        else
        {
            node->world_bound = (*geom)->world_bound;
            found_first_bound = true;
        }
    }
}





void Memory_Predictor::predict(Node* node)
{
    sys_memory = 0;
    gpu_memory = 0;
    inspect(node);
}



void Memory_Predictor::inspect(Node* node)
{
    gpu_memory += node->estimate_mem_usage();

    for ( std::list<Geometry*>::iterator
    i_geom  = node->get_geometry_list().begin();
    i_geom != node->get_geometry_list().end();
    ++i_geom )
        gpu_memory += (*i_geom)->estimate_mem_usage();

    for ( std::list<Attribute*>::iterator
    i_attr  = node->get_attribute_list().begin();
    i_attr != node->get_attribute_list().end();
    ++i_attr )
        gpu_memory += (*i_attr)->estimate_mem_usage();

    //std::cout << "Predicted GPU memory: " << gpu_memory << " bytes" << std::endl;

    node->accept(this);
}



}//////////////////////////////////////////////////////////////////////////////////////////////////
