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
#include "PSYGEN/PSYengine/Node_Group.hpp"
#include "PSYGEN/PSYengine/Mutex.hpp"

namespace psy /////////////////////////////////////////////////////////////////
{


PSYGEN_BIND_PARAMETERS(Node_Group, Node)
{
    m_sys_memory_use = sizeof(*this);

}



void Node_Group::amplify(Mutex* mutex)
{
    //if (m_eState == SHRINKED)
    //{
//         std::cout << "amplify Node_Group: name = \"" << get_name() << "\"" << std::endl;

        //empty

        if (mutex) mutex->lock();
        m_eState = AMPLIFIED;
        if (mutex) mutex->unlock();
    //}
}



void Node_Group::shrink(Mutex* mutex)
{
    //if (m_eState == AMPLIFIED)
    //{
//         std::cout << "shrink Node_Group: name = \"" << get_name() << "\"" << std::endl;

        //empty

        if (mutex) mutex->lock();
        m_eState = SHRINKED;
        if (mutex) mutex->unlock();
    //}
}



float Node_Group::estimate_mem_usage()
{
    return 0.0f;
}



float Node_Group::estimate_time_usage()
{
    return 0.0f;
}



void Node_Group::destroy()
{
    for (std::list<Geometry*>::iterator  geom=m_Geometry_List.begin(); geom != m_Geometry_List.end(); ++geom)
        psy::Object::Manager.destroy(*geom);
    m_Geometry_List.clear();

    for (std::list<Attribute*>::iterator  attr=m_Attribute_List.begin(); attr != m_Attribute_List.end(); ++attr)
        psy::Object::Manager.destroy(*attr);
    m_Attribute_List.clear();

    for (std::list<Node*>::iterator  node=m_Children_List.begin(); node != m_Children_List.end(); ++node)
        (*node)->destroy();

    for (std::list<Node*>::iterator  node=m_Children_List.begin(); node != m_Children_List.end(); ++node)
        psy::Object::Manager.destroy(*node);

    m_Children_List.clear();
}



void Node_Group::insert_child(Node* child)
{
    m_Children_List.push_back(child);
}



void Node_Group::remove_child(Node* node)
{
    m_Children_List.remove(node);
}



void Node_Group::accept(Visitor* visitor)
{
    for (std::list<Node*>::iterator i=m_Children_List.begin(); i != m_Children_List.end(); ++i)
        if (i != m_Children_List.end())
            visitor->inspect(*i);
}



bool Node_Group::update_bound()
{
    std::list<Node*>::iterator node=m_Children_List.begin();
    if ( node != m_Children_List.end() )
    {
        world_bound = (*node)->world_bound;
        for (++node; node != m_Children_List.end(); ++node)
            world_bound.merge( (*node)->world_bound );
        return true;
    }
    else
        world_bound.pos = world.getTranslate();
    return false;
}


}//////////////////////////////////////////////////////////////////////////////
