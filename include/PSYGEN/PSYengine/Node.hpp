
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
    *  \ingroup  __________
    *
    *//*******************************************************************************************/
#ifndef __PSYGEN_NODE_H__
#define __PSYGEN_NODE_H__

#include <list>

#include "PSYGEN/PSYengine/Object.hpp"
#include "PSYGEN/PSYengine/Visitor.hpp"
#include "PSYGEN/PSYengine/Geometry.hpp"
#include "PSYGEN/PSYengine/Attribute.hpp"
#include "PSYGEN/PSYengine/Transform.hpp"
#include "PSYGEN/PSYengine/Bound.hpp"


namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{

//class Attribute;
//class Geometry;

class Node : public Object
{
public:
    /// Procedural generation and collapse
    ///
    virtual void amplify(Mutex*)=0;
    virtual void shrink(Mutex*)=0;

    /// Generation time and memory usage estimation
    ///
    virtual float estimate_mem_usage()=0;
    virtual float        estimate_time_usage()=0;

    /// Scene graph traverse
    ///
    virtual void accept(Visitor*)=0;

    /// Scene graph management
    ///
    virtual void destroy()=0;
    virtual void insert_child(Node*)=0;
    virtual void remove_child(Node*)=0;
    virtual bool update_bound()=0;

    Node* get_parent  ()           { return parent; }
    void  reparent_to (Node* node) { parent = node; node->insert_child(this); }
    void  dettach     ()           { parent->remove_child(this); parent = NULL; }
    void  propagate_bound_to_root()
    {
        if (parent)
        {
            parent->update_bound();
            parent->propagate_bound_to_root();
        }
    }

    void update_geometry_list()
    {
        for (std::list<Geometry*>::iterator i=m_Geometry_List.begin(); i != m_Geometry_List.end(); ++i)
        {
            (*i)->calc_bound_volume();
            (*i)->world_bound = (*i)->local_bound;
            (*i)->world_bound.transform_by(world);
        }
    }

    /// Bound volume
    ///
    Bound  world_bound;

//
    /// World and local transforms
    ///
    Transform  local;
    Transform  world;

    /// Geometries and attributes list insertion and remotion
    ///
    void  insert_attribute(Attribute* attr) { m_Attribute_List.push_back(attr); }
    void  remove_attribute(Attribute* attr) { m_Attribute_List.remove(attr); }

    void  insert_geometry(Geometry* geom) { m_Geometry_List.push_back(geom); }
    void  remove_geometry(Geometry* geom) { m_Geometry_List.remove(geom); }

    /// Geometries and attributes list
    ///
    std::list<Geometry*>&   get_geometry_list()  { return m_Geometry_List; }
    std::list<Attribute*>&  get_attribute_list() { return m_Attribute_List; }

protected:
    Node* parent;
    std::list<Geometry*>   m_Geometry_List;
    std::list<Attribute*>  m_Attribute_List;

PSYGEN_DECLARE_PARAMETERS(Node):
};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_NODE_H__
