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
#ifndef __PSYGEN_NODE_GROUP_H__
#define __PSYGEN_NODE_GROUP_H__

#include "PSYGEN/PSYengine/Node.hpp"


namespace psy {////////////////////////////////////////////////////////////////////////////////////


class Node_Group : public Node
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

    /// Scene graph operations
    ///
    virtual void destroy();
    virtual void insert_child (Node*);
    virtual void remove_child (Node*);
    virtual bool update_bound ();

    /// Scene graph traverse
    ///
    virtual void accept(Visitor*);

//private:
    /// Children node list
    ///
    std::list<Node*>   m_Children_List;

PSYGEN_DECLARE_PARAMETERS(Node_Group):
};


}//////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__PSYGEN_NODE_GROUP_H__
