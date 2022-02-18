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

#include "PSYGEN/PSYengine/Shrinker.hpp"
#include "PSYGEN/PSYengine/Attribute.hpp"
#include "PSYGEN/PSYengine/Geometry.hpp"
#include "PSYGEN/PSYengine/Node.hpp"

namespace psy  ////////////////////////////////////////////////////////////////////////////////////
{

void Shrinker::inspect(Node* opNode)
{
    opNode->shrink(NULL);

    for (std::list<Geometry*>::iterator i=opNode->get_geometry_list().begin(); i != opNode->get_geometry_list().end(); ++i)
        (*i)->shrink(NULL);

    for (std::list<Attribute*>::iterator i=opNode->get_attribute_list().begin(); i != opNode->get_attribute_list().end(); ++i)
        (*i)->shrink(NULL);

    opNode->accept(this);
}



void DataAmplificator::inspect(Node* opNode)
{
    opNode->amplify(NULL);

    for (std::list<Geometry*>::iterator i=opNode->get_geometry_list().begin(); i != opNode->get_geometry_list().end(); ++i)
        (*i)->amplify(NULL);

    for (std::list<Attribute*>::iterator i=opNode->get_attribute_list().begin(); i != opNode->get_attribute_list().end(); ++i)
        (*i)->amplify(NULL);

    opNode->accept(this);
}


}//////////////////////////////////////////////////////////////////////////////////////////////////
