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
    *  \brief  __________
    *  \ingroup  PSYengine
    *
    *//*******************************************************************************************/
#ifndef __PSYGEN_NODE_WORLD_H__
#define __PSYGEN_NODE_WORLD_H__

#include "PSYGEN/PSYengine/Node_Group.hpp"
#include "PSYGEN/PSYengine/Geom_Terrain_Patch.hpp"


namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Node_World : public Node_Group
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

    virtual bool update_bound();

    float terrain_heigth(float x, float z) { return terrain->height(x + pos_x,z + pos_z); }

private:
    Node*  trees_node;
    Node*  rocks_node;
    Node*  terrain_node;
    Geom_Terrain_Patch* terrain;

    bool created;
    void create();


PSYGEN_DECLARE_PARAMETERS(Node_World):
    int    num_trees;
    int    num_rocks;
    float  size_x;
    float  size_z;
    float  pos_x;
    float  pos_z;
};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_NODE_WORLD_H__
